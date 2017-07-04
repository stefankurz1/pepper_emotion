/*
 * TriskarSmallShoulder.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: julian
 */

#include "TriskarSmallShoulder.h"

TriskarSmallShoulder::TriskarSmallShoulder() {
	is_oscillating = false;
	//TODO define correctly the values for the triskar in radians. the new version all angles have a start in 0
	max_angle = static_cast<float>(20.0/180.0*M_PI);
	min_angle = static_cast<float>(-1*20.0/180.0*M_PI);
	left_current_angle = 0;
	right_current_angle = 0;
	angle_error = static_cast<float>(1.0/180.0*M_PI);
	velocity_base =1.0;
	velocity_rotate = 0.5; //TODO read this parameter from a file
	velocity_move = velocity_base;
	velocity_emotional_rotate = velocity_rotate;
	//velocity_move = velocity;
	//velocity_oscillate = velocity;
	delta_time = 0.1; //milli seconds
	forward_direction_left = true;
	forward_direction_right = true;
	//Emotional variables
	pos_move_x = 0;
	pos_oscillate_x = 0;
	temp_angle = 0.0;
	last_angle = left_current_angle;
	minimum_change_angle = static_cast<float>(0.25/180.0*M_PI);
}

TriskarSmallShoulder::~TriskarSmallShoulder() {
	// TODO Auto-generated destructor stub
}

void TriskarSmallShoulder::MoveShoulderAction(Amplitude parameter){
	std::cout<<"it is executing move"<<std::endl;
	is_moving_emotional = false;
	desire_angle_to_move_left = parameter.getDistanceX();
	desire_angle_to_move_right = desire_angle_to_move_left*-1;
	verifyRange(&desire_angle_to_move_left,min_angle,max_angle);
	verifyRange(&desire_angle_to_move_right,min_angle,max_angle);
	if(!is_oscillating&&!is_oscillating_emotional){
		is_moving = true;
		//Send command
		//float left_temp_position = desire_angle_to_move_left;//this->sgn<float>(desire_angle_to_move)*velocity_move*delta_time;
		//float right_temp_position = desire_angle_to_move_right;//(right_current_angle + left_temp_position)*-1;
		//left_temp_position += left_current_angle;
		//verifyRange(&left_temp_position,min_angle,max_angle);
		//verifyRange(&right_temp_position,min_angle,max_angle);
		//this->sendMessage(left_temp_position,right_temp_position);
	}
}

void TriskarSmallShoulder::OscillateShoulderAction(Amplitude parameter){
	std::cout<<"Executing oscillate"<<std::endl;
	forward_direction_left = true;
	forward_direction_right = true;
	desire_angle_to_oscillate = parameter.getDistanceX();
	verifyRange(&desire_angle_to_oscillate,min_angle,max_angle);
	//std::cout<<"Desire angle "<<desire_angle_to_oscillate<<std::endl;
	if(!is_oscillating_emotional){
		is_oscillating = true;
		is_oscillating_emotional = false;
	}
}

void TriskarSmallShoulder::stopMoveSholuderAction(){
	ROS_INFO("Stopping move shoulder");
	is_moving = false;
	is_moving_emotional = false;
	repeat_move = false;
	pos_move_x = 0;
	velocity_move = velocity_base;
}

void TriskarSmallShoulder::stopOscillateShoulderAction(){
	ROS_INFO("Stopping oscillating shoulder");
	is_oscillating = false;
	is_oscillating_emotional = false;
	forward_direction_left = true;
	forward_direction_right = true;
	repeat_oscillation = false;
	pos_oscillate_x = 0;
	velocity_emotional_rotate = velocity_rotate;
	desire_angle_to_oscillate = 0;
}

void TriskarSmallShoulder::setPublisherAction(ros::NodeHandle *node){
	pub_action_triskar = node->advertise<theatre_bot::TriskarSmallUpper>("servo_triskar", 1);
}

void TriskarSmallShoulder::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("upper_triskar", 1, &TriskarSmallShoulder::callbackUpdateTriskarUpper, this);
}

void TriskarSmallShoulder::synchEmotionMove(){
	if(pos_move_x<(move_x.size()-1)){
		pos_move_x++;
	}
	if(pos_move_x>=(move_x.size()-1)&&repeat_move){
		pos_move_x = 0;
	}
	std::cout<<"Synch move "<<pos_move_x<<std::endl;
	this->generateEmotionalActionMove();
}

void TriskarSmallShoulder::synchEmotionOscillate(){
	if(pos_oscillate_x<(oscillate_x.size()-1)){
		pos_oscillate_x++;
	}
	if(pos_oscillate_x>=(oscillate_x.size()-1)&&repeat_oscillation){
		pos_oscillate_x = 0;
	}
	std::cout<<"Synch oscillate "<<pos_oscillate_x<<std::endl;
	this->generateEmotionalActionOscillate();

}

void TriskarSmallShoulder::setEmotionalMoveShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	move_x = vector_x;
	move_y = vector_y;
	move_z = vector_z;
	if(!is_moving){
		is_moving_emotional = true;
		generateEmotionalActionMove();
	}
	std::cout<<"Setting move emotional parameters"<<std::endl;
}

void TriskarSmallShoulder::setEmotionalOscillateShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
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
	std::cout<<"Setting oscillate emotional parameters"<<std::endl;
}

void TriskarSmallShoulder::initMessageTriskar(theatre_bot::TriskarSmallUpper *message){
	message->center_change = false;
	message->left_change = false;
	message->right_change = false;
}

void TriskarSmallShoulder::generateEmotionalActionMove(){
	Amplitude parameter;
	if(move_x.size()>0){
		parameter.setDistanceX(move_x.at(pos_move_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	std::cout<<"Move emotion "<<parameter.getDistanceX()<<std::endl;
	generateEmotionalVelocityMove();
	this->MoveShoulderAction(parameter);
}

void TriskarSmallShoulder::generateEmotionalActionOscillate(){
	Amplitude parameter;
	if(oscillate_x.size()>0){
		parameter.setDistanceX(oscillate_x.at(pos_oscillate_x).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceX(0);
	}
	//The other parameters are not consider here just because the robot at the moment does not have these two grades of freedom
	if(is_oscillating||is_oscillating_emotional){
		std::cout<<"Oscillate emotion "<<parameter.getDistanceX()<<std::endl;
		this->OscillateShoulderAction(parameter);
	}
	generateEmotionalVelocityOscillate();
}

void TriskarSmallShoulder::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_emotional_rotate = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
	}else{
		velocity_emotional_rotate = velocity_base;
	}
	std::cout<<"Oscillate velocity "<<velocity_emotional_rotate<<std::endl;
}


void TriskarSmallShoulder::generateEmotionalVelocityMove(){
	if(move_x.size()>0){
		velocity_move = (move_x.at(pos_move_x).getEmotionParameterTime());
		if(velocity_move == 0){
			velocity_move = velocity_base;
		}
	}else{
		velocity_move = velocity_base;
	}
}

void TriskarSmallShoulder::callbackUpdateTriskarUpper(const theatre_bot::Vector32::ConstPtr& msg){
	left_current_angle = static_cast<float>(msg->x/180.0*M_PI);
	right_current_angle = static_cast<float>(msg->z/180.0*M_PI);
	//std::cout<<"current angles "<<" "<<" - "<<left_current_angle<<" "<<right_current_angle<<std::endl;
	//std::cout<<"right "<<desire_angle_to_move_right<<" left "<<desire_angle_to_move_left<<std::endl;
	if(is_moving||is_moving_emotional){
		//std::cout<<"Executing move"<<std::endl;
		if(left_current_angle>=(desire_angle_to_move_left-angle_error)&&left_current_angle<=(desire_angle_to_move_left+angle_error)){
			//std::cout<<"It has finish"<<std::endl;
			is_moving = false;
			is_moving_emotional = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_move_name;
			message.coming_to = "";
			message.message = "action_finished";
			this->stopMoveSholuderAction();
			pub_action_synch->publish(message);
		}else if(!(is_oscillating||is_oscillating_emotional)){
			if(fabsf(last_angle - left_current_angle) < minimum_change_angle){
				//std::cout<<"It is less than the minimum angle"<<std::endl;
				temp_angle = temp_angle + delta_time*velocity_move*sgn<float>(desire_angle_to_move_left-left_current_angle);
			}else{
				//std::cout<<"It si more than the minimum angle"<<std::endl;
				temp_angle = delta_time*velocity_move*sgn<float>(desire_angle_to_move_left-left_current_angle);
				last_angle = left_current_angle;
			}
			float temp_desire_angle_left = left_current_angle + temp_angle;
			if((desire_angle_to_move_left>0&&temp_desire_angle_left>desire_angle_to_move_left)||(temp_desire_angle_left<desire_angle_to_move_left&&desire_angle_to_move_left<=0)){
				temp_desire_angle_left=desire_angle_to_move_left;
			}
			float temp_desire_angle_right = temp_desire_angle_left*-1.0;
			//std::cout<<"left "<<temp_desire_angle_left<<" desire "<<desire_angle_to_move_left<<" temp "<<temp_angle<<" left_position "<<left_current_angle<<std::endl;
			verifyRange(&temp_desire_angle_left,min_angle,max_angle);
			verifyRange(&temp_desire_angle_right,min_angle,max_angle);
			this->sendMessage(temp_desire_angle_left,temp_desire_angle_right);
			//sendMessage(temp_desire_angle);
		}
	}
	if(is_oscillating||is_oscillating_emotional){
		//std::cout<<"Oscillating shoulder "<<is_oscillating<<" or "<<is_oscillating_emotional<<" "<<velocity_emotional_rotate<<" "<<left_current_angle<<" "<<min_angle<<" "<<desire_angle_to_move_left<<" "<<desire_angle_to_oscillate<<std::endl;
		float desire_velocity_left = this->updateOscillation(velocity_emotional_rotate,left_current_angle,min_angle,max_angle,desire_angle_to_move_left,desire_angle_to_oscillate,angle_error,&forward_direction_left);
		//float desire_velocity_right = this->updateOscillation(velocity_emotional_rotate,right_current_angle,min_angle,max_angle,desire_angle_to_move_right,desire_angle_to_oscillate,angle_error,&forward_direction_right);
		//std::cout<<"right "<<desire_angle_to_move_right<<" left "<<desire_angle_to_move_left<<std::endl;
		//std::cout<<"Vel "<<desire_velocity_left<<" "<<desire_velocity_right<<" "<<velocity_emotional_rotate<<std::endl;
		if(fabsf(last_angle - left_current_angle) < minimum_change_angle){
			temp_angle = temp_angle + delta_time*desire_velocity_left;
		}else{
			temp_angle = delta_time*desire_velocity_left;
			last_angle = left_current_angle;
		}
		float next_position_left = left_current_angle + temp_angle;
		if(next_position_left>desire_angle_to_move_left+desire_angle_to_oscillate){
			next_position_left=desire_angle_to_move_left+desire_angle_to_oscillate;
		}else if(next_position_left<desire_angle_to_move_left-desire_angle_to_oscillate){
			next_position_left=desire_angle_to_move_left-desire_angle_to_oscillate;
		}
		float next_position_right = right_current_angle + temp_angle;
		if(next_position_right>desire_angle_to_move_right+desire_angle_to_oscillate){
			next_position_right=desire_angle_to_move_right+desire_angle_to_oscillate;
		}else if(next_position_right<desire_angle_to_move_right-desire_angle_to_oscillate){
			next_position_right=desire_angle_to_move_right-desire_angle_to_oscillate;
		}
		verifyRange(&next_position_left,min_angle,max_angle);
		verifyRange(&next_position_right,min_angle,max_angle);
		this->sendMessage(next_position_left,next_position_right);
	}
}

void TriskarSmallShoulder::sendMessage(float position_left, float position_right){
	theatre_bot::TriskarSmallUpper message;
	this->initMessageTriskar(&message);
	message.left = static_cast<int>(position_left/static_cast<float>(M_PI)*180.0);
	message.left_change = true;
	message.right = static_cast<int>(position_right/static_cast<float>(M_PI)*180.0);
	message.right_change = true;
	pub_action_triskar.publish(message);

}
