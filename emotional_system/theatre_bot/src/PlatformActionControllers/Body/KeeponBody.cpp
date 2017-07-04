/*
 * KeeponBody.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#include "KeeponBody.h"

KeeponBody::KeeponBody() {
	yaw_error = static_cast<float>(5.0/180.0*M_PI);
	delta_time = 0.1;//mms
	velocity_rotate = 1; //rad/sec
}

KeeponBody::~KeeponBody() {
	// TODO Auto-generated destructor stub
}

void KeeponBody::setPublisherAction(ros::NodeHandle *node){
	pub_action_keepon = node->advertise<theatre_bot::KeeponMessage>("keepon_action", 10);
}

void KeeponBody::initSubscriberAction(ros::NodeHandle *node){
	sub = node->subscribe("keepon_information", 1, &KeeponBody::callbackUpdateKeepon, this);
}

/*
 * keepon's capabilities do not have the possibility to move the body,
 * it is going to get the position regardless the rest of the information
 */
void KeeponBody::MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position){
	is_moving = true;
	if(parameter->getHasPose()){
		tf::Quaternion q(parameter->getQuaterionX(),parameter->getQuaterionY(),parameter->getQuaterionZ(),parameter->getQuaterionW());
		tf::Matrix3x3 m(q);
		double roll, pitch, yaw;
		m.getRPY(roll, pitch, yaw);
		desire_yaw = static_cast<float>(yaw);
		//std::cout<<"It is working is going to change the body orientation"<<std::endl;
		if(!is_oscillating||!is_oscillating_emotional){
			theatre_bot::KeeponMessage message;
			this->initMessageKeepon(&message);
			verifyAngle(&desire_yaw);
			message.pan.data = static_cast<float>(desire_yaw/M_PI*180.0);
			message.pan_change = true;
			pub_action_keepon.publish(message);
		}
	}
}

void KeeponBody::OscillateBodyAction(Amplitude parameter){
	//std::cout<<"Oscillate body"<<std::endl;
	desire_angle_to_oscillate_yaw = parameter.getDistanceZ();
	desire_angle_to_oscillate_roll = parameter.getDistanceX();
	desire_angle_to_oscillate_pitch = parameter.getDistanceY();
	verifyAngle(&desire_angle_to_oscillate_pitch);
	verifyAngle(&desire_angle_to_oscillate_roll);
	verifyAngle(&desire_angle_to_oscillate_yaw);
	if(!is_oscillating_emotional){
		is_oscillating = true;
		is_oscillating_emotional = false;
	}
}

void KeeponBody::stopMoveBodyAction(){
	//std::cout<<"Stopping move"<<std::endl;
	is_moving = false;
	repeat_move = false;
	is_moving_emotional = 0;
	pos_move_x = 0;
	pos_move_y = 0;
	pos_move_z = 0;
	velocity_emotional_rotate = velocity_rotate;
}

void KeeponBody::stopOscillateBodyAction(){
	//std::cout<<"Stopping oscillate"<<std::endl;
	is_oscillating = false;
	is_oscillating_emotional = false;
	repeat_oscillation = false;
	velocity_emotional_rotate = velocity_rotate;
	//Gets the pre-define velocity
	velocity_oscillate_pitch = velocity_rotate;
	velocity_oscillate_roll = velocity_rotate;
	velocity_oscillate_yaw = velocity_rotate;
	desire_angle_to_oscillate_yaw = 0.0;
	desire_angle_to_oscillate_pitch = 0.0;
	desire_angle_to_oscillate_roll = 0.0;
	pos_oscillate_x = 0;
	pos_oscillate_y = 0;
	pos_oscillate_z = 0;
}

void KeeponBody::synchEmotionMove(){
	//At the moment there is not necessary any implementation of this
}

void KeeponBody::synchEmotionOscillate(){
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

void KeeponBody::callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg){
	yaw =  static_cast<float>(msg->pan.data/180.0*M_PI);
	if(is_moving){
		if(yaw>=(desire_yaw-yaw_error)&&yaw<=(desire_yaw+yaw_error)){
			//std::cout<<"Finishing Move"<<std::endl;
			is_moving = false;
			is_moving_emotional = false;
			theatre_bot::ActionExecutionMessage message;
			message.coming_from = this->action_move_name;
			message.coming_to = "";
			message.message = "action_finished";
			this->stopMoveBodyAction();
			pub_action_synch->publish(message);
		}
	}
	if(is_oscillating || is_oscillating_emotional){
		//std::cout<<"It is oscillating"<<std::endl;
		float desire_velocity_yaw = this->updateOscillation(velocity_oscillate_yaw,yaw,desire_yaw,desire_angle_to_oscillate_yaw,yaw_error,&forward_direction_yaw);
		float next_position_yaw = yaw + desire_velocity_yaw*delta_time;
		verifyAngle(&next_position_yaw);
		//std::cout<<"Desire angle "<<desire_yaw<<" desire velocity "<<desire_velocity_yaw<<" next position "<<next_position_yaw<<std::endl;
		theatre_bot::KeeponMessage message;
		this->initMessageKeepon(&message);
		message.pan.data =  static_cast<float>(next_position_yaw/static_cast<float>(M_PI)*180.0);
		if(desire_angle_to_oscillate_yaw != 0){
			message.pan_change = true;
		}
		pub_action_keepon.publish(message);
	}
}

void KeeponBody::initMessageKeepon(theatre_bot::KeeponMessage *message){
	message->tilt_change = false;
	message->pan_change = false;
	message->side_change = false;
	message->pon_change = false;
}


void KeeponBody::setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
		//Here i am just interested in the vector orientation, the other parameter are not relevant in this case. However from emotion's definition is not possible to get the orientation
		//TODO see if is it interesting to add orientation to emotions' definition

}

void KeeponBody::setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
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


void KeeponBody::generateEmotionalActionOscillate(){
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
	if(is_oscillating||is_oscillating_emotional)
		this->OscillateBodyAction(parameter);
}

void KeeponBody::generateEmotionalVelocityOscillate(){
	if(oscillate_x.size()>0){
		velocity_oscillate_roll = (oscillate_x.at(pos_oscillate_x).getEmotionParameterTime());
	}else{
		velocity_oscillate_roll = velocity_rotate;
	}
	if(oscillate_y.size()>0){
		velocity_oscillate_pitch = (oscillate_y.at(pos_oscillate_y).getEmotionParameterTime());
	}else{
		velocity_oscillate_pitch = velocity_rotate;
	}
	if(oscillate_z.size()>0){
		velocity_oscillate_yaw = oscillate_z.at(pos_oscillate_z).getEmotionParameterTime();
	}else{
		velocity_oscillate_yaw = velocity_rotate;
	}
}
