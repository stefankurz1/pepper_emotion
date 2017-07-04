/*
 * NodeKeepon.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: julian
 */

#include "NodeKeepon.h"


NodeKeepon::NodeKeepon() {
	device = "/dev/ttyUSB0";
	port = 31337;
	last_pan = 0;
	last_pon = 0;
	last_side = 0;
	last_tilt = 0;
}

NodeKeepon::~NodeKeepon() {
	// TODO Auto-generated destructor stub
}


void NodeKeepon::setDevice(char * device){
	this->device = device;
}

void NodeKeepon::setPort(int port){
	this->port = port;
}

void NodeKeepon::init(){
	bbInitComm(device);
	bbInitMotors(KEEPON);
}

void NodeKeepon::sendKeeponInformation(){
	theatre_bot::KeeponMessage message;
	message.pan.data = bbGetPos(KEEPON, PAN);
	message.pon.data = bbGetPos(KEEPON, PON);
	message.side.data = bbGetPos(KEEPON, SIDE);
	message.tilt.data = bbGetPos(KEEPON, TILT);
	this->pub_action_parameter->publish(message);
}

void NodeKeepon::callbackActionExecution(const theatre_bot::KeeponMessage::ConstPtr& msg){
	if(msg->pan_change){
		bbMovPos(KEEPON,PAN,static_cast<double>(msg->pan.data));
	}
	if(msg->pon_change){
		bbMovPos(KEEPON,PON,static_cast<double>(msg->pon.data));
	}
	if(msg->side_change){
		bbMovPos(KEEPON,SIDE,static_cast<double>(msg->side.data));
	}
	if(msg->tilt_change){
		bbMovPos(KEEPON,TILT,static_cast<double>(msg->tilt.data));
	}

}

void NodeKeepon::setPublisher(ros::Publisher *pub_action_parameter){
	this->pub_action_parameter = pub_action_parameter;
}

int main(int argc, char **argv){
	NodeKeepon node;
	//TODO add parameters
	node.init();
	//Init the node
	ros::init(argc, argv, "node_keepon");
	ros::NodeHandle n;
	//Topic action keepon
	ros::Subscriber sub = n.subscribe("keepon_action", 10, &NodeKeepon::callbackActionExecution, &node);
	//Topic publish keepon info
	ros::Publisher pub = n.advertise<theatre_bot::KeeponMessage>("keepon_information", 10);
	node.setPublisher(&pub);
	ros::Time time_old = ros::Time::now();
	ros::Time time_new;
	ros::Duration difference;
	while(ros::ok()){
		time_new = ros::Time::now();
		difference = time_new-time_old;
		if((difference.toSec())>0.1){
			node.sendKeeponInformation();
		}
		ros::spinOnce();
	}
	return 0;
}
