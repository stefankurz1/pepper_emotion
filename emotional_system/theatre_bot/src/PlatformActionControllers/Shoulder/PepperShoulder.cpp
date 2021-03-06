/*
 * PepperShoulder.cpp
 *
 *  Created on: May 19, 2017
 *      Author: Stefan Kurz
 */

#include "PepperShoulder.h"

PepperShoulder::PepperShoulder() {
	desire_angle_to_move = 0;

	// define angle range
	max_angle = static_cast<float>(25.0/180.0*M_PI);
	min_angle = static_cast<float>(-1*25.0/180.0*M_PI);
	max_angle_move = static_cast<float>(50.0/180.0*M_PI);
	min_angle_move = static_cast<float>(-1*10.0/180.0*M_PI);	

	is_oscillating = false;	
	velocity_base = 1.0;
	velocity_rotate = 0.5;
	velocity_move = velocity_base;
	velocity_oscillate = velocity_rotate;

	fin_move_flag = false;
	
	//Emotional variables
	pos_move_x = 0;
	pos_oscillate_x = 0;
}

PepperShoulder::~PepperShoulder() {
}

void PepperShoulder::setPublisherAction(ros::NodeHandle *node){
	pub_action_pepper = node->advertise<theatre_bot::PepperUpper>("pepper_shoulder", 2);	
}

void PepperShoulder::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("pepper_platform", 1, &PepperShoulder::callbackUpdatePepper, this);
}


void PepperShoulder::MoveShoulderAction(Amplitude parameter){
	std::cout<<"executing move"<<std::endl;
	is_moving_emotional = false;
	desire_angle_to_move = parameter.getDistanceX();
	verifyRange(&desire_angle_to_move,min_angle_move,max_angle_move);
	if(!is_oscillating && !is_oscillating_emotional){
		is_moving = true;
	}
	if(is_moving || is_moving_emotional){
		this->sendMessage(false , desire_angle_to_move, velocity_move); // send move update
	}
}

void PepperShoulder::OscillateShoulderAction(Amplitude parameter){
	std::cout<<"executing oscillate"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	verifyRange(&desire_angle_to_oscillate,min_angle,max_angle);
	if(!is_oscillating_emotional){
		is_oscillating = true;
	}
	if(is_oscillating || is_oscillating_emotional){
		this->sendMessage(true, desire_angle_to_oscillate, velocity_oscillate); // send oscillate update
	}
}

void PepperShoulder::stopMoveShoulderAction(){
	ROS_INFO("stop move shoulder");
	is_moving = false;
	is_moving_emotional = false;
	repeat_move = false;
	pos_move_x = 0;
	desire_angle_to_move = 0;
	velocity_move = velocity_base;
	if(!fin_move_flag){ // fin_move_flag is set when a movement complete message is received from pepper_platform
		this->sendMessage(false , desire_angle_to_move, velocity_move); // stop move
	}else{
		fin_move_flag = false;
	}
}

void PepperShoulder::stopOscillateShoulderAction(){
	ROS_INFO("stop oscillating shoulder");
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	pos_oscillate_x = 0;
	desire_angle_to_oscillate = 0;
	velocity_oscillate = velocity_rotate;
	this->sendMessage(true, desire_angle_to_oscillate, velocity_oscillate); // stop oscillate
}

void PepperShoulder::synchEmotionMove(){
	if(pos_move_x < (move_x.size() - 1)){
		pos_move_x++;
	}
	if(pos_move_x >= (move_x.size() - 1) && repeat_move){
		pos_move_x = 0;
	}
	std::cout<<"synch move "<<pos_move_x<<std::endl;
	this->generateEmotionalActionMove();
}

void PepperShoulder::synchEmotionOscillate(){
	if(pos_oscillate_x < (oscillate_x.size() - 1)){
		pos_oscillate_x++;
	}
	if(pos_oscillate_x >= (oscillate_x.size() - 1) && repeat_oscillation){
		pos_oscillate_x = 0;
	}
	std::cout<<"synch oscillate "<<pos_oscillate_x<<std::endl;
	this->generateEmotionalActionOscillate();

}

void PepperShoulder::setEmotionalMoveShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_move = repet;	
	move_x = vector_x;
	move_y = vector_y;
	move_z = vector_z;
	if(!is_moving){
		is_moving_emotional = true;
		generateEmotionalActionMove();
	}
	std::cout<<"setting move emotional parameters"<<std::endl;
}

void PepperShoulder::setEmotionalOscillateShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_oscillation = repet;
	oscillate_x = vector_x;
	oscillate_y = vector_y;
	oscillate_z = vector_z;
	if(!is_oscillating){
		is_oscillating_emotional = true;
		generateEmotionalActionOscillate();
	}
	if(is_moving_emotional){
		is_moving_emotional = false;
	}
	generateEmotionalVelocityOscillate();
	std::cout<<"setting oscillate emotional parameters"<<std::endl;
}

void PepperShoulder::generateEmotionalActionMove(){
	Amplitude parameter;
	if(move_x.size()>0){
		parameter.setDistanceX(move_x.at(pos_move_x).getEmotionParameterSpacing()); 
	}else{
		parameter.setDistanceX(0);
	}
	std::cout<<"move emotion "<<parameter.getDistanceX()<<std::endl;
	generateEmotionalVelocityMove();
	this->MoveShoulderAction(parameter);
}

void PepperShoulder::generateEmotionalActionOscillate(){
	Amplitude parameter;
	if(oscillate_x.size()>0){
		parameter.setDistanceX(oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	if(is_oscillating||is_oscillating_emotional){
		std::cout<<"oscillate emotion "<<parameter.getDistanceX()<<std::endl;
		this->OscillateShoulderAction(parameter);
	}
	generateEmotionalVelocityOscillate();
}

void PepperShoulder::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_oscillate = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
		if(velocity_oscillate == 0){
			velocity_oscillate = velocity_base;
		}
	}else{
		velocity_oscillate = velocity_base;
	}
	std::cout<<"oscillate velocity "<<velocity_oscillate<<std::endl;
}


void PepperShoulder::generateEmotionalVelocityMove(){
	if(move_x.size()>0){
		velocity_move = (move_x.at(pos_move_x).getEmotionParameterTime());
		if(velocity_move == 0){
			velocity_move = velocity_base;
		}
	}else{
		velocity_move = velocity_base;
	}
	std::cout<<"move velocity "<<velocity_move<<std::endl;
}

void PepperShoulder::callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg){
	if(msg->fin_move_shoulder == true){
		fin_move_flag = true;
		stopMoveShoulderAction();	
	}
}

void PepperShoulder::sendMessage(bool mode, float desire_angle, float velocity){
	theatre_bot::PepperUpper message;
	message.x = true;
	message.mode = mode;
	message.angle = desire_angle;
	message.velocity = velocity;

	pub_action_pepper.publish(message); // publish the message to Pepper Platform
}
