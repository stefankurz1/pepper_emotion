/*
 * KeeponTorso.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#include "KeeponTorso.h"

KeeponTorso::KeeponTorso() {
	this->tilt = 0;
	this->min_tilt = static_cast<float>(-1*M_PI)/4.0;
	this->max_tilt = static_cast<float>(M_PI)/4.0;
	this->side = 0;
	this->min_side = static_cast<float>(-1*M_PI)*5.0/36.0;
	this->max_side = static_cast<float>(M_PI)*5.0/36.0;
	this->is_oscillating = false;
	this->is_moving = false;
	this->is_moving_emotional = false;
	this->is_oscillating_emotional = false;
	this->desire_angle_to_oscillate = 0;
	this->delta_time = 0.1; //s
	this->velocity = 1; //ras/sec
	this->velocity_move = this->velocity;
	velocity_side = this->velocity;
	this->velocity_oscillate_x = this->velocity;
	this->velocity_oscillate_y = this->velocity;
	this->velocity_oscillate_z = this->velocity;
	this->pon = 0;
	this->min_pon = 0;
	this->max_pon = 15;
	this->tilt_error = 0.08;
	this->side_error = 0.5;
	this->pon_error = 2;
	this->has_finish_side = false;
	this->has_finish_tilt = false;
	last_angle_tilt = tilt;
	last_angle_side = side ;
	temp_angle_tilt = 0.0;
	temp_angle_side = 0.0;
	minimum_change_angle = static_cast<float>(0.5/180.0*M_PI);
}

KeeponTorso::~KeeponTorso() {
	// TODO Auto-generated destructor stub
}

void KeeponTorso::generateEmotionalActionMove(){
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
	if(move_z.size()>0){
		parameter.setDistanceZ(move_z.at(pos_move_z).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceZ(0);
	}
	this->MoveTorsoAction(parameter);
}

void KeeponTorso::generateEmotionalActionOscillate(){
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
	if(oscillate_z.size()>0){
		parameter.setDistanceZ(oscillate_z.at(pos_oscillate_z).getEmotionParameterSpacing());
	}else{
		parameter.setDistanceZ(0);
	}
	if(is_oscillating||is_oscillating_emotional){
		this->OscillateTorsoAction(parameter);
	}
	generateEmotionalVelocityOscillate();
}


void KeeponTorso::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_oscillate_x = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
	}else{
		velocity_oscillate_x = velocity;
	}
	if(oscillate_y.size()>0){
		velocity_oscillate_y = (oscillate_y.at(pos_oscillate_y).getEmotionParameterTime());
	}else{
		velocity_oscillate_y = velocity;
	}
	if(oscillate_z.size()>0){
		velocity_oscillate_z = oscillate_z.at(pos_oscillate_z).getEmotionParameterTime();
	}else{
		velocity_oscillate_z = velocity;
	}
}

void KeeponTorso::setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repeat){
	//Start execution movement
	repeat_move = repeat;
	move_x = vector_x;
	move_y = vector_y;
	move_z = vector_z;
	if(!is_moving){
		is_moving_emotional = true;
		this->generateEmotionalActionMove();
	}
}

void KeeponTorso::setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repeat){
	//std::cout<<"Emotional oscillate torso"<<std::endl;
	//Start executing movement
	repeat_move = repeat;
	oscillate_x = vector_x;
	oscillate_y = vector_y;
	oscillate_z = vector_z;
	if(!is_oscillating){
		is_oscillating_emotional = true;
		this->generateEmotionalActionOscillate();
	}
	generateEmotionalVelocityOscillate();
}

void KeeponTorso::synchEmotionMove(){
	if(pos_move_x<(move_x.size()-1)){
		pos_move_x++;
	}
	if(pos_move_y<(move_y.size()-1)){
		pos_move_y++;
	}
	if(pos_move_z<(move_z.size()-1)){
		pos_move_z++;
	}
	if(pos_move_x>=(move_x.size()-1)&&pos_move_y>=(move_y.size()-1)&&pos_move_z>=(move_z.size()-1)&&repeat_move){
		pos_move_x = 0;
		pos_move_y = 0;
		pos_move_z = 0;
	}
	this->generateEmotionalActionMove();
}

void KeeponTorso::synchEmotionOscillate(){
	if(pos_oscillate_x<(oscillate_x.size()-1)){
		pos_oscillate_x++;
	}
	if(pos_oscillate_y<(oscillate_y.size()-1)){
		pos_oscillate_y++;
	}
	if(pos_oscillate_z<(oscillate_z.size()-1)){
		pos_oscillate_z++;
	}
	if(pos_oscillate_x>=(oscillate_x.size()-1)&&pos_oscillate_y>=(oscillate_y.size()-1)&&pos_oscillate_z>=(oscillate_z.size()-1)&&repeat_oscillation){
		pos_oscillate_x = 0;
		pos_oscillate_y = 0;
		pos_oscillate_z = 0;
	}
	this->generateEmotionalActionOscillate();
}


void KeeponTorso::MoveTorsoAction(Amplitude parameter){
	//std::cout<<"Done"<<std::endl;
	is_moving_emotional = false;
	desire_angle_to_move = parameter.getDistanceX();
	desire_angle_to_side = parameter.getDistanceY();
	desire_angle_to_z = parameter.getDistanceZ();
	if(!is_oscillating&&!is_oscillating_emotional){
		is_moving = true;
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		verifyRange(&desire_angle_to_move,min_tilt,max_tilt);
		verifyRange(&desire_angle_to_side,min_side,max_side);
		verifyRange(&desire_angle_to_z,min_pon,max_pon);
		//std::cout<<"Desire angle to execute "<<desire_angle_to_move<<std::endl;
		/*message.side.data = static_cast<float>(desire_angle_to_side/static_cast<float>(M_PI)*180.0);
		message.side_change = true;
		message.tilt.data = static_cast<float>(desire_angle_to_move/static_cast<float>(M_PI)*180.0);
		message.tilt_change = true;
		message.pon.data = desire_angle_to_z;
		message.pon_change = true;
		//std::cout<<"Sending message to move"<<std::endl;
		pub_action_keepon.publish(message);*/
	}
}

void KeeponTorso::OscillateTorsoAction(Amplitude parameter){
	//std::cout<<"Done 2"<<std::endl;
	desire_angle_to_oscillate = parameter.getDistanceX();
	desire_angle_to_oscillate_y = parameter.getDistanceY();
	desire_angle_to_oscillate_z = parameter.getDistanceZ();
	verifyRange(&desire_angle_to_oscillate,min_tilt,max_tilt);
	verifyRange(&desire_angle_to_oscillate_y,min_side,max_side);
	verifyRange(&desire_angle_to_oscillate_z,min_pon,max_pon);
	if(!is_oscillating_emotional){
		is_oscillating = true;
		is_oscillating_emotional = false;
	}
}

void KeeponTorso::setPublisherAction(ros::NodeHandle *node){
	pub_action_keepon = node->advertise<theatre_bot::KeeponMessage>("keepon_action", 10);
}


void KeeponTorso::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("keepon_information", 1, &KeeponTorso::callbackUpdateKeepon, this);
}

void KeeponTorso::initMessageKeepon(theatre_bot::KeeponMessage *message){
	message->tilt_change = false;
	message->pan_change = false;
	message->side_change = false;
	message->pon_change = false;
}


void KeeponTorso::callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg){
	this->tilt = static_cast<float>(msg->tilt.data/180.0*M_PI);
	this->side = static_cast<float>(msg->side.data/180.0*M_PI);
	this->pon = msg->pon.data;
	if(is_moving||is_moving_emotional){
		bool tilt_has_changed = false;
		bool side_has_changed = false;
		float temp_desire_angle_tilt;
		float temp_desire_angle_side;
		if(tilt>=(desire_angle_to_move-tilt_error)&&tilt<=(desire_angle_to_move+tilt_error)){
			//std::cout<<"Finishing Move"<<std::endl;
			has_finish_tilt = true;
		}else if(!(is_oscillating||is_oscillating_emotional)){
			if(fabsf(last_angle_tilt - tilt) < minimum_change_angle){
				temp_angle_tilt = temp_angle_tilt + delta_time*velocity_move*sgn<float>(desire_angle_to_move);
			}else{
				temp_angle_tilt = delta_time*velocity_move*sgn<float>(desire_angle_to_move);
				last_angle_tilt = tilt;
			}
			tilt_has_changed = true;
			temp_desire_angle_tilt = tilt + temp_angle_tilt;
			verifyRange(&temp_desire_angle_tilt,min_tilt,max_tilt);
		}
		if(side>=(desire_angle_to_side-side_error)&&tilt<=(desire_angle_to_side+side_error)){
			//std::cout<<"Finishing Move"<<std::endl;
			has_finish_tilt = true;
		}else if(!(is_oscillating||is_oscillating_emotional)){
			if(fabsf(last_angle_side - side) < minimum_change_angle){
				temp_angle_side = temp_angle_side + delta_time*velocity_side*sgn<float>(desire_angle_to_side);
			}else{
				temp_angle_side = delta_time*velocity_side*sgn<float>(desire_angle_to_side);
				last_angle_side = side;
			}
			tilt_has_changed = true;
			temp_desire_angle_side = side + temp_angle_side;
			verifyRange(&temp_desire_angle_side,min_side,max_side);
		}
		if(has_finish_side && has_finish_tilt){
			is_moving = false;
			is_moving_emotional = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_name_move;
			message.coming_to = "";
			message.message = "action_finished";
			this->stopMoveTorsoAction();
			pub_action_synch->publish(message);
		}else{
			theatre_bot::KeeponMessage message;
			message.side.data = static_cast<float>(temp_desire_angle_side/static_cast<float>(M_PI)*180.0);
			message.side_change = side_has_changed;
			message.tilt.data = static_cast<float>(temp_desire_angle_tilt/static_cast<float>(M_PI)*180.0);
			message.tilt_change = tilt_has_changed;
			message.pon_change = false;
			//std::cout<<"Sending message to move"<<std::endl;
			pub_action_keepon.publish(message);
		}
	}
	if(is_oscillating||is_oscillating_emotional){
		//std::cout<<"It is trying to oscillate x: "<<velocity_oscillate_x<<" y: "<<velocity_oscillate_y<<std::endl;
		float desire_velocity_x = this->updateOscillation(velocity_oscillate_x,tilt,min_tilt,max_tilt,desire_angle_to_move,desire_angle_to_oscillate,tilt_error,&forward_direction_x);
		float desire_velocity_y = this->updateOscillation(velocity_oscillate_y,side,min_side,max_side,desire_angle_to_side,desire_angle_to_oscillate_y,side_error,&forward_direction_y);
		float desire_velocity_z = this->updateOscillation(velocity_oscillate_z,pon,min_pon,max_pon,desire_angle_to_z,desire_angle_to_oscillate_z,pon_error,&forward_direction_z);
		//std::cout<<"X "<<desire_velocity_x<<" Y "<<desire_velocity_y<<" Z "<<desire_velocity_z<<std::endl;
		float next_position_x = tilt + desire_velocity_x *delta_time;
		float next_position_y = side + desire_velocity_y *delta_time;
		float next_position_z = pon + desire_velocity_z *delta_time;
		//Send message
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		verifyRange(&next_position_x,min_tilt,max_tilt);
		verifyRange(&next_position_y,min_side,max_side);
		verifyRange(&next_position_z,min_pon,max_pon);
		message.tilt.data = static_cast<float>(next_position_x/static_cast<float>(M_PI)*180.0);
		message.side.data = static_cast<float>(next_position_y/static_cast<float>(M_PI)*180.0);
		message.pon.data = next_position_z;
		if(desire_angle_to_oscillate!=0)
			message.tilt_change = true;
		if(desire_angle_to_oscillate_y!=0)
			message.side_change = true;
		if(desire_angle_to_oscillate_z!=0)
			message.pon_change = true;
		pub_action_keepon.publish(message);
	}
}

void KeeponTorso::stopMoveTorsoAction(){
	is_moving = false;
	is_moving_emotional = false;
	repeat_move = false;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	this->velocity_move = this->velocity;
	this->has_finish_side = false;
	this->has_finish_tilt = false;
	/*theatre_bot::KeeponMessage message;
	this->initMessageKeepon(&message);
	message.side.data = 0.0;
	message.side_change = true;
	message.tilt.data = 0.0;
	message.tilt_change = true;
	message.pon.data = 0.0;
	message.pon_change = true;
	pub_action_keepon.publish(message);*/
	ROS_INFO("Move torso finish");
}

void KeeponTorso::stopOscillateTorsoAction(){
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	pos_oscillate_z = 0;
	this->velocity_oscillate_x = this->velocity;
	this->velocity_oscillate_y = this->velocity;
	this->velocity_oscillate_z = this->velocity;
	desire_angle_to_oscillate = 0;
	desire_angle_to_oscillate_y = 0;
	desire_angle_to_oscillate_z = 0;
	ROS_INFO("Oscillate torso finish");
}
