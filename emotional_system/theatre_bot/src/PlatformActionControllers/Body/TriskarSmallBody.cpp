/*
 * TriskarSmallBody.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#include "TriskarSmallBody.h"

TriskarSmallBody::TriskarSmallBody() {
	this->desire_yaw = 0.0;
}

TriskarSmallBody::~TriskarSmallBody() {
	// TODO Auto-generated destructor stub
}


void TriskarSmallBody::setPublisherAction(ros::NodeHandle *node){
	pub_action_triskar = node->advertise<theatre_bot::TriskarMessage>("action_triskar",10);
	pub_emotion_triskar = node->advertise<theatre_bot::TriskarMessageEmotion>("emotional_triskar",10);
	pub_command_triskar = node->advertise<std_msgs::Char>("commands_triskar",10);
}

void TriskarSmallBody::initSubscriberAction(ros::NodeHandle *node){
	sub_emotion_synch = node->subscribe("emotional_move_synch",10, &TriskarSmallBody::callBackSynchTriskar, this);
	sub_action_synch = node->subscribe("action_move_synch",10, &TriskarSmallBody::callBackSynchTriskar, this);
	sub_action = node->subscribe("odometry_triskar",1, &TriskarSmallBody::callBackUpdateTriskar, this);
}

void TriskarSmallBody::MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position){
	if(type_position == PointPosition){
		boost::shared_ptr<Point> parameter_point = boost::static_pointer_cast<Point>(parameter);
		Point temp_point;
		temp_point.setX(parameter_point->getX());
		temp_point.setY(parameter_point->getY());
		temp_point.setHasPose(true);
		calculateDesireAngle(parameter->getQuaterion());
		//temp_point.setQuaterion(parameter_point->getQuaterionX(),parameter_point->getQuaterionY(),parameter_point->getQuaterionZ(),parameter_point->getQuaterionW());
		//Set point in the planner
		this->sendtPoint(temp_point);
	}else if(type_position == LandmarkPosition){
		boost::shared_ptr<Landmark> parameter_landmark = boost::static_pointer_cast<Landmark>(parameter);
		//Set information in the planner
		this->setLandmark(parameter_landmark);
	}else if(type_position == SquarePosition){
		boost::shared_ptr<Square> parameter_square = boost::static_pointer_cast<Square>(parameter);
		//Set information in the planner
		this->setSquare(parameter_square);
	}else if(type_position == CirclePosition){
		boost::shared_ptr<Circle> parameter_circle = boost::static_pointer_cast<Circle>(parameter);
		//Set information in the planner
		this->setCircle(parameter_circle);
	}
}

void TriskarSmallBody::sendtPoint(Point parameter){
	theatre_bot::TriskarMessage message;
	//the number 0 is for move body and 1 for oscillate body this is a simplification used to do not make a string comparison
	message.coming_from = 0;
	message.x = (parameter.getX()-robot_initial_position_x)*cosf(robot_initial_angle)+(parameter.getY()-robot_initial_position_y)*sinf(robot_initial_angle);
	message.y = -(parameter.getX()-robot_initial_position_x)*sinf(robot_initial_angle)+(parameter.getY()-robot_initial_position_y)*cosf(robot_initial_angle);
	//this->calculateDesireAngle(parameter.getQuaterion());
	message.z = this->desire_yaw-robot_initial_angle;
	pub_action_triskar.publish(message);
}

void TriskarSmallBody::calculateDesireAngle(Quaternion parameter){
	tf::Quaternion q(parameter.getX(),parameter.getY(),parameter.getZ(),parameter.getW());
	tf::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	this->desire_yaw = yaw;
}

void TriskarSmallBody::OscillateBodyAction(Amplitude parameter){
	//It gets the parameters and generate the message in the correct format for the triskar
	theatre_bot::TriskarMessage message;
	message.coming_from = 1;
	message.x = parameter.getDistanceX();
	message.y = parameter.getDistanceY();
	message.z = parameter.getDistanceZ();
	pub_action_triskar.publish(message);
}

void TriskarSmallBody::stopMoveBodyAction(){
	theatre_bot::TriskarMessageEmotion t;
	t.coming_to = 0;
	t.synch = false;
	t.stop = true;
	pub_emotion_triskar.publish(t);
	ROS_INFO("action move body has finished");
}

void TriskarSmallBody::stopOscillateBodyAction(){
	theatre_bot::TriskarMessageEmotion t;
	t.coming_to = 1;
	t.synch = false;
	t.stop = true;
	pub_emotion_triskar.publish(t);
	ROS_INFO("action oscillate body has finished");
}

void TriskarSmallBody::synchEmotionMove(){
	theatre_bot::TriskarMessageEmotion message;
	message.coming_to = 0;
	message.stop = false;
	message.synch = true;
	std::cout<<"Synch emotion move"<<std::endl;
	pub_emotion_triskar.publish(message);
}

void TriskarSmallBody::synchEmotionOscillate(){
	theatre_bot::TriskarMessageEmotion message;
	message.coming_to = 1;
	message.stop = false;
	message.synch = true;
	std::cout<<"Synch emotion oscillate"<<std::endl;
	pub_emotion_triskar.publish(message);
}

void TriskarSmallBody::setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//This method gets the vectors and it converted to the proper format for the triskar
	theatre_bot::TriskarMessageEmotion message;
	message.coming_to = 0;
	message.stop = false;
	message.synch = false;
	message.repeat = repet;
	for(std::vector<EmotionMovementParameter>::iterator it = vector_x.begin(); it != vector_x.end(); ++it){
		message.distance.push_back(it->getEmotionParameterSpacing());
		message.velocity.push_back(it->getEmotionParameterTime());
	}
	std::cout<<"Sending emotional parameters move"<<std::endl;
	pub_emotion_triskar.publish(message);
}

void TriskarSmallBody::setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet){
	//This method gets the vectors and it converted to the proper format for the triskar
	theatre_bot::TriskarMessageEmotion message;
	message.coming_to = 1;
	message.stop = false;
	message.synch = false;
	message.repeat = repet;
	for(std::vector<EmotionMovementParameter>::iterator it = vector_x.begin(); it != vector_x.end(); ++it){
		message.distance.push_back(it->getEmotionParameterSpacing());
		message.velocity.push_back(it->getEmotionParameterTime());
	}
	std::cout<<"Sending emotional parameters oscillate"<<std::endl;
	pub_emotion_triskar.publish(message);
}


void TriskarSmallBody::callBackSynchTriskar(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	if(msg->message.compare("action_finished") == 0){
		theatre_bot::ActionExecutionMessage message;
		message.header.stamp = ros::Time::now();
		std::cout<<"action finished coming from "<<msg->coming_from<<std::endl;
		message.coming_from = msg->coming_from;
		message.coming_to = "";
		message.message = "action_finished";
		pub_action_synch->publish(message);
	}else if(msg->message.compare("emotion_synch") == 0){
		//synch emotional
		theatre_bot::ActionExecutionMessage message;
		message.header.stamp = ros::Time::now();
		std::cout<<"Synch emotion coming from "<<msg->coming_from<<std::endl;
		message.coming_from = msg->coming_from;
		message.coming_to = "";
		message.message = "emotion_synch";
		pub_action_synch->publish(message);
	}
}
void TriskarSmallBody::callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg){
	x =robot_initial_position_x + cosf(robot_initial_angle)*msg->pose.position.x-sinf(robot_initial_angle)*msg->pose.position.y;
	y =robot_initial_position_y +sinf(robot_initial_angle)*msg->pose.position.x + cosf(robot_initial_angle)*msg->pose.position.y;
	yaw = robot_initial_angle + msg->pose.orientation;
	//TODO update landmarks and other complex points and send back the next position
}

void TriskarSmallBody::setLandmark(boost::shared_ptr<Landmark>  parameter){
	clearPointers();
	this->type_position = LandmarkPosition;
	this->parameter_landmark = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
	if(this->parameter_landmark->getTypeLandmark() == Place_Landmark){
		float pos_x, pos_y;
		bool exist = theatre_place.getPoinDestination(this->parameter_landmark->getIdLandmakr(),&pos_x,&pos_y);
		Point temp_point;
		temp_point.setX(pos_x);
		temp_point.setY(pos_y);
		//temp_point.setQuaterion(parameter_point->getQuaterionX(),parameter_point->getQuaterionY(),parameter_point->getQuaterionZ(),parameter_point->getQuaterionW());
		//Set point in the planner
		this->sendtPoint(temp_point);
	}
}

void TriskarSmallBody::setSquare(boost::shared_ptr<Square> parameter){
	clearPointers();
	this->type_position = SquarePosition;
	this->parameter_square = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}

void TriskarSmallBody::setCircle(boost::shared_ptr<Circle> parameter){
	clearPointers();
	this->type_position = CirclePosition;
	this->parameter_circle = parameter;
	if(parameter->getHasPose()){
		this->calculateDesireAngle(parameter->getQuaterion());
	}
}

void TriskarSmallBody::clearPointers(){
	parameter_landmark.reset();
	parameter_square.reset();
	parameter_circle.reset();
	type_position = Unknown;
}
