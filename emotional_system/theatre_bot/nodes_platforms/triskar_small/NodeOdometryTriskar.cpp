/*
 * NodeOdometryTriskar.cpp
 *
 *  Created on: May 19, 2015
 *      Author: julian
 */

#include "NodeOdometryTriskar.h"

NodeOdometryTriskar::NodeOdometryTriskar() {
	this->initial_robot_position_theta = 0.0;
	this->initial_robot_position_x = 0.0;
	this->initial_robot_position_y = 0.0;
}

NodeOdometryTriskar::~NodeOdometryTriskar() {
	// TODO Auto-generated destructor stub
}


void NodeOdometryTriskar::setProjectDirectory(std::string project_path){
	this->project_path = project_path;
}

void NodeOdometryTriskar::loadInformation(){
	ParserConfigurationFiles temp_configuration;
	std::string file = project_path +"/robot_configuration_files/robot_initial_position.json";
	temp_configuration.readRobotInitialPositionFile(file,&initial_robot_position_x,&initial_robot_position_y,&initial_robot_position_theta);
}

void NodeOdometryTriskar::setInformation(){
	filter.setRobotInTheScene(this->initial_robot_position_x,this->initial_robot_position_y,0.0,this->initial_robot_position_theta);
}

void NodeOdometryTriskar::callbackNewInitParameters(const theatre_bot::InitParamVelPos::ConstPtr& msg){
	filter.setRobotInTheScene(msg->initial_x,msg->initial_y,0.0,msg->initial_theta);
}

void NodeOdometryTriskar::callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg){

}

void NodeOdometryTriskar::callBackCommand(const theatre_bot::TriskarVelocity::ConstPtr& msg){

}

int main(int argc, char **argv){
	NodeOdometryTriskar node;
	ros::init(argc, argv, "node_odometry_triskar");
	//This gets the robot's initial position, which is required to establish the markers position respect the scene
	if(n.hasParam("project_directory")){
		std::string project_path;
		n.getParam("project_directory",project_path);
		node.setProjectDirectory(project_path);
		node.loadInformation();
	}
	//TODO load the markers id files

	ros::Subscriber sub_emotion = n.subscribe("change_init_parameters_body", 10, &NodeOdometryTriskar::callbackNewInitParameters, &node);
	ros::Subscriber sub_update  = n.subscribe("odometry_triskar",1, &NodeOdometryTriskar::callBackUpdateTriskar, &node);
	ros::Subscriber sub_command  = n.subscribe("vel_triskar",1, &NodeOdometryTriskar::callBackCommand, &node);
	ros::Publisher pub_filter_odometry = n.advertise<theatre_bot::OdometryTriskar>("filter_odometry_triskar", 10);
	//TODO subscribe to the ar information
	node.setInformation();
	ROS_INFO("Node odometry triskar is ready");
}
