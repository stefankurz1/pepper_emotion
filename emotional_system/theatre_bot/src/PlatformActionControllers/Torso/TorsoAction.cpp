/*
 * TorsoAction.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: julian
 */

#include "TorsoAction.h"

TorsoAction::TorsoAction() {
	desire_angle_to_oscillate = 0;
	desire_angle_to_oscillate_y = 0;
	desire_angle_to_oscillate_z = 0;
	desire_angle_to_side = 0;
	desire_angle_to_move = 0;
	desire_angle_to_z = 0;
	delta_time = 100;
	is_oscillating = false;
	forward_direction_x = true;
	forward_direction_y = true;
	forward_direction_z = true;
	velocity = 0;
	is_moving = false;
	is_moving_emotional = false;
	is_oscillating_emotional = false;
	repeat_move = false;
	repeat_oscillation = false;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	pos_oscillate_z = 0;
	velocity_move = 1;
	velocity_oscillate_x = 1;
	velocity_oscillate_y = 1;
	velocity_oscillate_z = 1;
}

TorsoAction::~TorsoAction() {
	// TODO Auto-generated destructor stub
}

void TorsoAction::setPublisherActionSynch(ros::Publisher *pub_action_synch){
	this->pub_action_synch = pub_action_synch;
}


void TorsoAction::setActionMoveName(std::string action_name){
	this->action_name_move = action_name;
}
void TorsoAction::setActionOscillateName(std::string action_name){
	this->action_name_oscillate = action_name;
}

bool TorsoAction::isMovingTorso(){
	return this->is_moving;
}

bool TorsoAction::isOscillatingTorso(){
	return this->is_oscillating;
}

float TorsoAction::angleCorrection(float distance_theta){
	if(distance_theta>M_PI){
		distance_theta= distance_theta-2.0*M_PI;
	}else if(distance_theta<-M_PI){
		distance_theta = distance_theta+2.0*M_PI;
	}
	return distance_theta;
}

float TorsoAction::updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle){
	float max_angle_to_oscillate = desire_angle_to_move + desire_angle_to_oscillate;
	float min_angle_to_oscillate = desire_angle_to_move - desire_angle_to_oscillate;
	if(max_angle_to_oscillate>max_angle){
		max_angle_to_oscillate = max_angle;
	}
	if(min_angle_to_oscillate<min_angle){
		min_angle_to_oscillate = min_angle;
	}
	//float distance_theta = current_angle - desire_angle_to_move;
	//distance_theta = angleCorrection(distance_theta);
	if(forward_direction_x){
		if(current_angle >= max_angle_to_oscillate){
			forward_direction_x = !forward_direction_x;
			return desire_velocity * -1.0;
		}
	}else{
		desire_velocity = -1.0*desire_velocity;
		if(current_angle <= min_angle_to_oscillate){
			forward_direction_x = !forward_direction_x;
			return desire_velocity * -1.0;
		}
	}
	return desire_velocity;
}

void TorsoAction::verifyRange(float *number, float min, float max){
	if(*number<min){
		*number = min;
	}else if(*number >max){
		*number = max;
	}
}



float TorsoAction::updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction){
	float max_angle_to_oscillate = desire_angle_to_move + desire_angle_to_oscillate;
	float min_angle_to_oscillate = desire_angle_to_move - desire_angle_to_oscillate;
	//std::cout<<"Checking update oscillation "<<max_angle_to_oscillate<<" min: "<<min_angle_to_oscillate<<std::endl;
	if(max_angle_to_oscillate>max_angle){
		max_angle_to_oscillate = max_angle;
	}
	if(min_angle_to_oscillate<min_angle){
		min_angle_to_oscillate = min_angle;
	}
	//std::cout<<"Checking update oscillation 2 "<<max_angle_to_oscillate<<" min: "<<min_angle_to_oscillate<<std::endl;
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
	return desire_velocity;
}
