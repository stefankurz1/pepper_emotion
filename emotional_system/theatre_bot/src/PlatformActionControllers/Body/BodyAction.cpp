/*
 * BodyAction.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: julian
 */

#include "BodyAction.h"

BodyAction::BodyAction() {
	//Move
	x = 0.0;
	y = 0.0;
	z = 0.0;
	x_error = 0.0;
	y_error = 0.0;
	z_error = 0.0;
	desire_x = 0.0;
	desire_y = 0.0;
	desire_z = 0.0;
	yaw = 0.0;
	pitch = 0.0;
	roll = 0.0;
	yaw_error = 0.0;
	pitch_error = 0.0;
	roll_error = 0.0;
	desire_yaw = 0.0;
	desire_pitch = 0.0;
	desire_roll = 0.0;
	is_moving = false;
	velocity_rotate = 1.0;//rad/sec
	velocity_emotional_rotate = velocity_rotate;
	//Oscillate
	desire_angle_to_oscillate_yaw = 0.0;
	desire_angle_to_oscillate_pitch = 0.0;
	desire_angle_to_oscillate_roll = 0.0;
	forward_direction_yaw = false;
	forward_direction_pitch = false;
	forward_direction_roll = false;
	is_oscillating = false;
	velocity_oscillate_pitch = velocity_rotate;
	velocity_oscillate_roll = velocity_rotate;
	velocity_oscillate_yaw = velocity_rotate;
	//Emotional
	//Emotion variable
	is_moving_emotional = false;
	is_oscillating_emotional = false;
	//Emotional parameters
	robot_initial_position_x = 0.0;
	robot_initial_position_y = 0.0;
	robot_initial_position_z = 0.0;
	robot_initial_angle = 0.0;
	repeat_move = false;
	repeat_oscillation = false;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	pos_oscillate_z = 0;
	delta_time = 100;//mms

}

BodyAction::~BodyAction() {
	// TODO Auto-generated destructor stub
}


float BodyAction::updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction){
	float distance_theta = current_angle - desire_angle_to_move;
	float temp_velocity = velocity_emotional_rotate;
	verifyAngle(&distance_theta);
	if(*forward_direction){
		if(distance_theta>=desire_angle_to_oscillate){
			*forward_direction = !*forward_direction;
			return -1.0*temp_velocity;
		}
	} else{
		temp_velocity = -1.0*temp_velocity;
		if(distance_theta<=(-1.0*desire_angle_to_oscillate)){
			*forward_direction = !*forward_direction;
			return -1.0*temp_velocity;
		}
	}
	return temp_velocity;
}

void BodyAction::setLinearVelocity(float linear_velocity){
	if(linear_velocity>maximum_linear_velocity){
		this->linear_velocity = maximum_linear_velocity;
	}else{
		this->linear_velocity = linear_velocity;
	}
}

void BodyAction::setAngularVelocity(float angular_velocity){
	if(angular_velocity>maximum_angular_velocity){
		this->velocity_rotate = maximum_angular_velocity;
	}else{
		this->velocity_rotate = angular_velocity;
	}
}
void BodyAction::setActionMoveName(std::string name){
	this->action_move_name = name;
}

void BodyAction::setActionOscillateName(std::string name){
	this->action_oscillation_name = name;
}

void BodyAction::setPublisherActionSynch(ros::Publisher *pub_action_synch){
	this->pub_action_synch = pub_action_synch;
}

void BodyAction::verifyAngle(float *angle){
	if(*angle>M_PI){
		*angle= *angle-2.0*M_PI;
	}else if(*angle<-M_PI){
		*angle = *angle+2.0*M_PI;
	}
}

/*
 * This method sets the robot respect the frame, this allows having the frame of reference of the robot in a different position.
 */
void BodyAction::setRobotInTheScene(float robot_initial_x, float robot_initial_y, float robot_initial_z, float robot_initial_angle){
	this->robot_initial_position_x = robot_initial_x;
	this->robot_initial_position_y = robot_initial_y;
	this->robot_initial_position_z = robot_initial_z;
	this->robot_initial_angle = robot_initial_angle;
	verifyAngle(&this->robot_initial_angle);
}

void BodyAction::setTheatrePlaceInformation(TheatrePlaces theatre_place){
	this->theatre_place = theatre_place;
}
