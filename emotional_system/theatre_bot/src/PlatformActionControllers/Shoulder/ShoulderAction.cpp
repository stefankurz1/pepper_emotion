/*
 * ShoulderAction.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: julian
 */

#include "ShoulderAction.h"

ShoulderAction::ShoulderAction() {
	desire_angle_to_move_left = 0;
	desire_angle_to_move_right = 0;
	//Move
	is_moving = false;
	velocity_rotate = 1.0;//rad/sec
	velocity_emotional_rotate = velocity_rotate;
	//Oscillate
	is_oscillating = false;
	//Emotional
	//Emotion variable
	is_moving_emotional = false;
	is_oscillating_emotional = false;
	//Emotional parameters
	repeat_move = false;
	repeat_oscillation = false;
	desire_angle_to_oscillate = 0;
	delta_time = 0.5;//mms
	velocity_move = 1;
}

ShoulderAction::~ShoulderAction() {
	// TODO Auto-generated destructor stub
}

float ShoulderAction::updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction){
	float max_angle_to_oscillate = desire_angle_to_move + desire_angle_to_oscillate;
	float min_angle_to_oscillate = desire_angle_to_move - desire_angle_to_oscillate;
	if(max_angle_to_oscillate>max_angle){
		max_angle_to_oscillate = max_angle;
	}
	if(min_angle_to_oscillate<min_angle){
		min_angle_to_oscillate = min_angle;
	}
	//std::cout<<"max angle "<<max_angle_to_oscillate<<" min angle"<<min_angle_to_oscillate<<" desire angle "<<desire_angle_to_oscillate<<" desire to move "<<desire_angle_to_move<<" current "<<current_angle<<std::endl;
	//float distance_theta = current_angle - desire_angle_to_move;
	//distance_theta = angleCorrection(distance_theta);
	if(*forward_direction){
		//std::cout<<"Forward: "<<current_angle<<" "<<max_angle_to_oscillate<<" - "<<desire_angle_to_move<<std::endl;
		if(current_angle >= (max_angle_to_oscillate-error)){
			*forward_direction = !*forward_direction;
			return desire_velocity * -1.0;
		}
	}else{
		//std::cout<<"Backward: "<<current_angle<<" "<<min_angle_to_oscillate<<" - "<<desire_angle_to_move<<std::endl;
		desire_velocity = -1.0*desire_velocity;
		if(current_angle <= (min_angle_to_oscillate+error)){
			*forward_direction = !*forward_direction;
			return desire_velocity * -1.0;
		}
	}
	//std::cout<<"Returning "<<desire_velocity<<std::endl;
	return desire_velocity;
}

void ShoulderAction::setActionMoveName(std::string name){
	this->action_move_name = name;
}

void ShoulderAction::setActionOscillateName(std::string name){
	this->action_oscillation_name = name;
}

void ShoulderAction::setPublisherActionSynch(ros::Publisher *pub_action_synch){
	this->pub_action_synch = pub_action_synch;
}

void ShoulderAction::verifyRange(float *number, float min, float max){
	if(*number<min){
		*number = min;
	}else if(*number >max){
		*number = max;
	}
}
