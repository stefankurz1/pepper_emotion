/*
 * PepperTorso.cpp
 *
 *  Created on: May 20, 2017
 *      Author: Stefan Kurz
 */

#include "PepperTorso.h"

PepperTorso::PepperTorso() {
	desire_angle_to_move_x = 0;
	desire_angle_to_move_y = 0;

	// define angle range
	max_angle_x = static_cast<float>(20.0/180.0*M_PI);
	min_angle_x = static_cast<float>(-1*20.0/180.0*M_PI);
	max_angle_move_x = static_cast<float>(20.0/180.0*M_PI);
	min_angle_move_x = static_cast<float>(-1*20.0/180.0*M_PI);

	max_angle_y = static_cast<float>(12.0/180.0*M_PI);
	min_angle_y = static_cast<float>(-1*12.0/180.0*M_PI);
	max_angle_move_y = static_cast<float>(10.0/180.0*M_PI);
	min_angle_move_y = static_cast<float>(-1*10.0/180.0*M_PI);	

	is_oscillating = false;	
	velocity_base = 1.0;
	velocity_rotate = 0.5;
	velocity_move = velocity_base;
	velocity_oscillate_x = velocity_rotate;
	velocity_oscillate_y = velocity_rotate;
	
	fin_move_x_flag = false;
	fin_move_y_flag = false;	
	
	//Emotional variables
	pos_move_x = 0;
	pos_move_y = 0;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;	
}

PepperTorso::~PepperTorso() {

}

void PepperTorso::setPublisherAction(ros::NodeHandle *node){
	pub_action_pepper = node->advertise<theatre_bot::PepperUpper>("pepper_torso", 1);
}

void PepperTorso::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("pepper_platform", 1, &PepperTorso::callbackUpdatePepper, this);
}

void PepperTorso::MoveTorsoAction(Amplitude parameter){
	std::cout<<"executing move"<<std::endl;
	is_moving_emotional = false;
	desire_angle_to_move_x = parameter.getDistanceX();
	desire_angle_to_move_y = parameter.getDistanceY();
	verifyRange(&desire_angle_to_move_x,min_angle_move_x,max_angle_move_x);
	verifyRange(&desire_angle_to_move_y,min_angle_move_y,max_angle_move_y);
	if(!is_oscillating && !is_oscillating_emotional){
		is_moving = true;
	}
	if(is_moving || is_moving_emotional){
		this->sendMessage(true, false , desire_angle_to_move_x, velocity_move);  // send move x update
		this->sendMessage(false, false , desire_angle_to_move_y, velocity_move); // send move y update
	}
}

void PepperTorso::OscillateTorsoAction(Amplitude parameter){
	std::cout<<"executing oscillate"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	desire_angle_to_oscillate_y = parameter.getDistanceY();
	verifyRange(&desire_angle_to_oscillate,min_angle_x,max_angle_x);
	verifyRange(&desire_angle_to_oscillate_y,min_angle_y,max_angle_y);
	if(!is_oscillating_emotional){
		is_oscillating = true;
		is_oscillating_emotional = false;
	}
	if(is_oscillating||is_oscillating_emotional){
		this->sendMessage(true, true, desire_angle_to_oscillate, velocity_oscillate_x);    // send oscillate x update
		this->sendMessage(false, true, desire_angle_to_oscillate_y, velocity_oscillate_y); // send oscillate y update
	}
}

void PepperTorso::stopMoveTorsoAction(){
	ROS_INFO("stop move torso");
	is_moving = false;
	is_moving_emotional = false;
	repeat_move = false;
	pos_move_x = 0;
	pos_move_y = 0;
	velocity_move = velocity_base;
	desire_angle_to_move_x = 0;
	desire_angle_to_move_y = 0;
	if(!fin_move_x_flag){	// fin_move_flags set when movement complete message is received from pepper_platform
		this->sendMessage(true, false, desire_angle_to_move_x, velocity_move); // stop move
	}else{
		fin_move_x_flag = false;
	}
	if(!fin_move_y_flag){
		this->sendMessage(false, false, desire_angle_to_move_y, velocity_move); // stop move
	}else{
		fin_move_y_flag = false;
	}
}

void PepperTorso::stopOscillateTorsoAction(){
	ROS_INFO("stop oscillating torso");
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	velocity_oscillate_x = velocity_rotate;
	velocity_oscillate_y = velocity_rotate;
	desire_angle_to_oscillate = 0;
	desire_angle_to_oscillate_y = 0;
	this->sendMessage(true, true, desire_angle_to_oscillate, velocity_oscillate_x); // stop oscillate
	this->sendMessage(false, true, desire_angle_to_oscillate_y, velocity_oscillate_y); // stop oscillate
}

void PepperTorso::synchEmotionMove(){
	if(pos_move_x<(move_x.size()-1)){
		pos_move_x++;
	}
	if(pos_move_y<(move_y.size()-1)){
		pos_move_y++;
	}
	if(pos_move_x>=(move_x.size()-1)&&pos_move_y>=(move_y.size()-1)&&repeat_move){
		pos_move_x = 0;
		pos_move_y = 0;
	}
	std::cout<<"synch move "<<pos_move_x<<std::endl;
	this->generateEmotionalActionMove();
}

void PepperTorso::synchEmotionOscillate(){
	if(pos_oscillate_x<(oscillate_x.size()-1)){
		pos_oscillate_x++;
	}
	if(pos_oscillate_y<(oscillate_y.size()-1)){
		pos_oscillate_y++;
	}
	if(pos_oscillate_x>=(oscillate_x.size()-1)&&pos_oscillate_y>=(oscillate_y.size()-1)&&repeat_oscillation){
		pos_oscillate_x = 0;
		pos_oscillate_y = 0;
	}
	std::cout<<"synch oscillate "<<pos_oscillate_x<<std::endl;
	this->generateEmotionalActionOscillate();
}

void PepperTorso::setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	repeat_move = repet;	
	move_x = vector_x;
	move_y = vector_y;
	move_z = vector_z;
	if(!is_moving){
		is_moving_emotional = true;
		generateEmotionalActionMove();
	}
	std::cout<<"setting move emotional parameters"<<std::endl;
	generateEmotionalVelocityMove();
}

void PepperTorso::setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
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

void PepperTorso::generateEmotionalActionMove(){
	Amplitude parameter;
	if(move_x.size()>0){
		parameter.setDistanceX(move_x.at(pos_move_x).getEmotionParameterSpacing()); 
	}else{
		parameter.setDistanceX(0);
	}
	if(move_y.size()>0){
		parameter.setDistanceY(move_y.at(pos_move_y).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceY(0);
	}
	std::cout<<"move emotion "<<parameter.getDistanceX()<<std::endl;
	this->MoveTorsoAction(parameter);
}

void PepperTorso::generateEmotionalActionOscillate(){
	Amplitude parameter;
	if(oscillate_x.size()>0){
		parameter.setDistanceX(oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	if(oscillate_y.size()>0){
		parameter.setDistanceY(oscillate_y.at(pos_oscillate_y).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceY(0);
	}
	if(is_oscillating||is_oscillating_emotional){
		std::cout<<"oscillate emotion "<<parameter.getDistanceX()<<std::endl;
		this->OscillateTorsoAction(parameter);
	}
	generateEmotionalVelocityOscillate();
}

void PepperTorso::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_oscillate_x = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
		if(velocity_oscillate_x == 0){
			velocity_oscillate_x = velocity_rotate;
		}
	}else{
		velocity_oscillate_x = velocity_rotate;
	}
	if(oscillate_y.size()>0){
		velocity_oscillate_y = (oscillate_y.at(pos_oscillate_y).getEmotionParameterTime());
		if(velocity_oscillate_y == 0){
			velocity_oscillate_y = velocity_rotate;
		}
	}else{
		velocity_oscillate_y = velocity_rotate;
	}
	std::cout<<"oscillate velocity "<<velocity_oscillate_x<<", "<<velocity_oscillate_y<<std::endl;
}


void PepperTorso::generateEmotionalVelocityMove(){
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

void PepperTorso::callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg){
	if(msg->fin_move_torso_x == true){
		fin_move_x_flag = true;	
	} 
	if(msg->fin_move_torso_y == true){
		fin_move_y_flag = true;	
	} 
	if(fin_move_x_flag || fin_move_y_flag){
		stopMoveTorsoAction();
	}
}

void PepperTorso::sendMessage(bool x, bool mode, float desire_angle, float velocity){
	theatre_bot::PepperUpper message;
	message.x = x;
	message.mode = mode; // oscillate = true, move = false
	message.angle = desire_angle;
	message.velocity = velocity;

	pub_action_pepper.publish(message); // publish the message to Pepper Platform
}
