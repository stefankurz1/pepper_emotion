/*
 * TriskarPlanner.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: julian
 */

#include "TriskarPlanner.h"

TriskarPlanner::TriskarPlanner() {
	this->yaw_error = 0.0;
	this->desire_yaw = 0.0;
	this->velocity_rotate = 0.0;
	this->linear_velocity = 0.0;
	this->last_position_x = 0.0;
	this->last_position_y = 0.0;
	this->reduce_linear_velocity = 0.0;
	this->reduce_angular_velocity = 0.0;
	this->x_error = 0.0;
	this->y_error = 0.0;
	this->has_arrived_linear = false;
	this->has_arrived_angular = false;
	this->has_angle = false;
	type_position = Unknown;
	this->current_distance = 0.0;
	first_iteration = true;
	desire_x = 0.0;
	desire_y = 0.0;
	is_reducing_velocity = false;
}

TriskarPlanner::~TriskarPlanner() {
	// TODO Auto-generated destructor stub
}

void TriskarPlanner::setLinearVelocity(float linear_velocity){
	this->linear_velocity = linear_velocity;
}


void TriskarPlanner::setVelocities(float linear_velocity, float angular_velocity){
	this->reduce_linear_velocity = static_cast<float>(linear_velocity/5.0);
	this->reduce_angular_velocity = static_cast<float>(angular_velocity/16);
	//This avoid the division by 0
	if(this->reduce_angular_velocity<this->yaw_error)
		this->reduce_angular_velocity = this->yaw_error;
	this->linear_velocity = linear_velocity;
	this->velocity_rotate = angular_velocity;
}

bool TriskarPlanner::getHasAngle(){
	return has_angle;
}

void TriskarPlanner::setVariables(float yaw_error,float velocity_rotate, float linear_velocity, float reduce_linear_velocity,float reduce_angular_velocity,float x_error,float y_error){
	this->yaw_error = yaw_error;
	this->velocity_rotate = velocity_rotate;
	this->linear_velocity = linear_velocity;
	this->reduce_linear_velocity = reduce_linear_velocity;
	this->reduce_angular_velocity = reduce_angular_velocity;
	this->x_error = x_error;
	this->y_error = y_error;
	is_reducing_velocity = false;
}

void TriskarPlanner::setPoint(boost::shared_ptr<Point> parameter){
	clearPointers();
	this->type_position = PointPosition;
	this->parameter_point = parameter;
	desire_x = this->parameter_point->getX();
	desire_y = this->parameter_point->getY();
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}
void TriskarPlanner::setLandmark(boost::shared_ptr<Landmark>  parameter){
	clearPointers();
	this->type_position = LandmarkPosition;
	this->parameter_landmark = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}
void TriskarPlanner::setSquare(boost::shared_ptr<Square> parameter){
	clearPointers();
	this->type_position = SquarePosition;
	this->parameter_square = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}
void TriskarPlanner::setCircle(boost::shared_ptr<Circle> parameter){
	clearPointers();
	this->type_position = CirclePosition;
	this->parameter_circle = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}

void TriskarPlanner::setLastPosition(float last_position_x, float last_position_y){
	this->last_position_x = last_position_x;
	this->last_position_y = last_position_y;
}

bool TriskarPlanner::updateLinearVelocity(float x_position, float y_position,float yaw_position, theatre_bot::TriskarVelocity *message, TheatrePlaces theatre_place){
	//std::cout<<"Type "<<this->type_position<<std::endl;
	if(this->type_position == PointPosition){
		return this->updateLinearVelocityPointParameter(x_position,y_position,yaw_position,message);
	}else if(this->type_position == LandmarkPosition){
		//The current place landmark just work in the case of theatre in a simplified way
		if(this->parameter_landmark->getTypeLandmark() == Place_Landmark){
			//Verify that the id exist in the data base
			float pos_x, pos_y;
			bool exist = theatre_place.getPoinDestination(this->parameter_landmark->getIdLandmakr(),&pos_x,&pos_y);
			//TODO change the point depending on the objects localization
			if(exist){
				this->desire_x = pos_x;
				this->desire_y = pos_y;
				return this->updateLinearVelocityPointParameter(x_position,y_position,yaw_position,message);
			}
		}
		//TODO implement object and person recognition, this should be done using the markers
	}
	return false;
}

bool TriskarPlanner::updateAngularVelocity(float yaw_position, theatre_bot::TriskarVelocity *message){
	if(!has_angle){
		has_arrived_angular = true;
		return true;
	}
	float distance_theta = desire_yaw - yaw_position;
	distance_theta = correctAngle(distance_theta);
	if(fabs(distance_theta)<reduce_angular_velocity){
		message->angular = velocity_rotate*distance_theta/reduce_angular_velocity;
	}else{
		message->angular = velocity_rotate*signum(distance_theta);
	}
	if(fabs(distance_theta)<yaw_error){
		message->angular = 0.0;
		has_arrived_angular = true;
		return true;
	}
	return false;
}

bool TriskarPlanner::updateLinearVelocityPointParameter(float x_position, float y_position,float yaw_position, theatre_bot::TriskarVelocity *message){
	//Calculate the distance to the desire position
	if(first_iteration){
		first_iteration = false;
		current_distance = 0.0;
	}else{
		current_distance = current_distance+ sqrt(pow(x_position-last_position_x,2.0)+pow(y_position-last_position_y,2.0));
	}
	last_position_x = x_position;
	last_position_y = y_position;
	//Change the reference frame
	float x_temp = this->desire_x-x_position;
	float y_temp = this->desire_y-y_position;
	//std::cout<<"Planner distance x "<<x_temp<<" y "<<y_temp<<std::endl;
	float distance_x = cos(yaw_position)*x_temp+sin(yaw_position)*y_temp;
	float distance_y = cos(yaw_position)*y_temp-sin(yaw_position)*x_temp;
	float temp_angle_to_desire_position =atan2f(distance_y,distance_x);
	bool temp_is_reducing_x, temp_is_reducing_y;
	//Verification if it should stop the x velocity
	if(fabs(distance_x)<reduce_linear_velocity){
		temp_is_reducing_x = true;
		message->linear.x = (linear_velocity*distance_x)/reduce_linear_velocity;
	}else{
		temp_is_reducing_x = false;
		message->linear.x = linear_velocity*signum(distance_x);
	}
	//Verification if it should stop the y velocity
	if(fabs(distance_y)<reduce_linear_velocity){
		temp_is_reducing_y = true;
		message->linear.y = (linear_velocity*distance_y)/reduce_linear_velocity;
	}else{
		temp_is_reducing_y = false;
		message->linear.y = linear_velocity*signum(distance_y);
	}
	is_reducing_velocity = temp_is_reducing_x && temp_is_reducing_y;
	if(fabs(distance_x)<x_error&&fabs(distance_y)<y_error){
		has_arrived_linear = true;
		message->linear.x = 0.0;
		message->linear.y = 0.0;
		return true;
	}
	return false;
}

bool TriskarPlanner::hasArrived(){
	return has_arrived_linear;
}

float TriskarPlanner::fabs(float num){
	if(num<0)
		return -1*num;
	return num;
}

float TriskarPlanner::signum(float num){
	if(num<0)
		return -1;
	return 1;
}

float TriskarPlanner::getCurrentDistance(){
	return current_distance;
}

void TriskarPlanner::resetCurrentDistance(){
	current_distance = 0.0;
}

void TriskarPlanner::calculateDesireAngle(Quaternion parameter){
	tf::Quaternion q(parameter.getX(),parameter.getY(),parameter.getZ(),parameter.getW());
	tf::Matrix3x3 m(q);
	has_angle = true;
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	this->desire_yaw = yaw;
}


bool TriskarPlanner::isReducingVelocity(){
	return is_reducing_velocity;
}

float TriskarPlanner::correctAngle(float distance_theta){
	if(distance_theta>M_PI){
		distance_theta= distance_theta-2.0*M_PI;
	}else if(distance_theta<-M_PI){
		distance_theta = distance_theta+2.0*M_PI;
	}
	return distance_theta;
}

void TriskarPlanner::clearPointers(){
	has_angle = false;
	parameter_point.reset();
	parameter_landmark.reset();
	parameter_square.reset();
	parameter_circle.reset();
	desire_x = last_position_x;
	desire_y = last_position_y;
	type_position = Unknown;
}

float TriskarPlanner::getDesireYaw(){
	return this->desire_yaw;
}

void TriskarPlanner::setTypeParameter(TypePosition type_position){
	this->type_position = type_position;
}
