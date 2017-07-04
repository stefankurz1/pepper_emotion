/*
 * PepperBody.cpp
 *
 *  Created on: May 30, 2017
 *      Author: Stefan Kurz
 */

#include "PepperBody.h"

PepperBody::PepperBody() {
	desire_angle_to_oscillate_yaw = 0.0;
	velocity_base = 1.0;
	velocity_rotate = 1.0;
	max_angle = static_cast<float>(20.0/180.0*M_PI);
	min_angle = static_cast<float>(-1*20.0/180.0*M_PI);
}

PepperBody::~PepperBody() {
}


void PepperBody::setPublisherAction(ros::NodeHandle *node){
	pub_action_pepper = node->advertise<theatre_bot::PepperMove>("pepper_body", 2);
}

void PepperBody::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("pepper_platform", 1, &PepperBody::callbackUpdatePepper, this);
}

void PepperBody::MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position){
	is_moving = true;	
	boost::shared_ptr<Point> parameter_point = boost::static_pointer_cast<Point>(parameter);
	Point temp_point;
	temp_point.setX(parameter_point->getX());
	temp_point.setY(parameter_point->getY());
	temp_point.setHasPose(true);
	if(!is_oscillating || !is_oscillating_emotional){
		this->sendMessage(false, temp_point, false); // send move message
	}
}

void PepperBody::OscillateBodyAction(Amplitude parameter){
	Point temp_point;
	temp_point.setX(0.0);
	temp_point.setY(0.0);
	temp_point.setHasPose(false);
	desire_angle_to_oscillate_yaw = parameter.getDistanceZ(); // get correct yaw angle
	verifyRange(&desire_angle_to_oscillate_yaw, min_angle, max_angle);
	if(!is_oscillating_emotional){
		is_oscillating = true;
		this->sendMessage(true, temp_point, false); // send oscillate message
	}
}

void PepperBody::stopMoveBodyAction(){
	Point temp_point;
	is_moving = false;
	repeat_move = false;
	linear_velocity = velocity_base;
	temp_point.setX(0.0);
	temp_point.setY(0.0);
	sendMessage(false, temp_point, true); // send stop move message 
	ROS_INFO("action move body has finished");
}

void PepperBody::stopOscillateBodyAction(){
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	velocity_oscillate_yaw = velocity_rotate;
	desire_angle_to_oscillate_yaw = 0.0;
	pos_oscillate_z = 0;
	Point temp_point;
	temp_point.setX(0.0);
	temp_point.setY(0.0);
	sendMessage(true, temp_point, true); // send stop oscillate message 
	ROS_INFO("action oscilalte body has finished");
}

void PepperBody::synchEmotionMove(){
	// no emotional movements
}

void PepperBody::setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	// no emotional movements
}

void PepperBody::synchEmotionOscillate(){
	if(pos_oscillate_z<(oscillate_z.size()-1)){
		pos_oscillate_z++;
	}
	if(pos_oscillate_z>=(oscillate_z.size()-1)&&repeat_oscillation){
		pos_oscillate_z = 0;
	}
	this->generateEmotionalActionOscillate();
}

void PepperBody::generateEmotionalActionOscillate(){
	Amplitude parameter;
	if(oscillate_z.size()>0){
		parameter.setDistanceZ(oscillate_z.at(pos_oscillate_z).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceZ(0);
	}
	if(is_oscillating||is_oscillating_emotional)
		this->OscillateBodyAction(parameter);
}

void PepperBody::generateEmotionalVelocityOscillate(){
	if(oscillate_z.size()>0){
		velocity_oscillate_yaw = oscillate_z.at(pos_oscillate_z).getEmotionParameterTime();
	}else{
		velocity_oscillate_yaw = velocity_rotate;
	}
}

void PepperBody::setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_oscillation = repet;
	oscillate_x = vector_x;
	oscillate_y = vector_y;
	oscillate_z = vector_z;
	if(!is_oscillating){
		is_oscillating_emotional = true;
		generateEmotionalActionOscillate();
	}
	generateEmotionalVelocityOscillate();
}

void PepperBody::callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg){
	if(msg->fin_move_body == true){ // movement finished
	}
}


void PepperBody::verifyRange(float *number, float min, float max){
	if(*number<min){
		*number = min;
	}else if(*number >max){
		*number = max;
	}
}

void PepperBody::sendMessage(bool mode, Point parameter, bool stop){
	theatre_bot::PepperMove message;
	message.mode = mode; 					// oscillate == true, move == false
	message.x = parameter.getX();
	message.y = parameter.getY();
	message.theta = this->desire_angle_to_oscillate_yaw;	// oscillation angle
	message.velocity_linear = linear_velocity;
	message.velocity_angular = velocity_oscillate_yaw;
	message.stop = stop;					// send stop
	pub_action_pepper.publish(message);
}
