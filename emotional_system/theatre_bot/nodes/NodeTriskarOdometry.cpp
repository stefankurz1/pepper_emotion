/*
 * NodeTriskarOdometry.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: julian
 */

#include "NodeTriskarOdometry.h"

NodeTriskarOdometry::NodeTriskarOdometry() {
	this->pub_odometry_cov = 0;
}

NodeTriskarOdometry::~NodeTriskarOdometry() {
	// TODO Auto-generated destructor stub
}

void NodeTriskarOdometry::callbackNewOdometry(const theatre_bot::OdometryTriskar::ConstPtr& msg){
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(msg->pose.orientation);
	//Odometry
	current_time = ros::Time::now();
	nav_msgs::Odometry odom;
	odom.header.stamp = current_time;
	odom.header.frame_id = "/robot";
	//Set position
	odom.pose.pose.position.x = msg->pose.position.x;
	odom.pose.pose.position.y = msg->pose.position.y;
	odom.pose.pose.position.z = 0.0;
	odom.pose.pose.orientation= odom_quat;
	odom.pose.covariance = {100.0	,25.0	,0.0	,0.0	,0.0	,0.017,
							25.0	,100.0	,0.0	,0.0	,0.0	,0.017,
							0.0		,0.0	,1000000000000.0	,0.0	,0.0	,0.0,
							0.0		,0.0	,0.0	,1000000000000.0	,0.0	,0.0,
							0.0		,0.0	,0.0	,0.0	,1000000000000.0	,0.0,
							0.017	,0.017	,0.0	,0.0	,0.0	,0.0872};

	//set the velocity
	odom.child_frame_id = "base_link";
	odom.twist.twist.linear.x = msg->twist.linear.x;
	odom.twist.twist.linear.y = msg->twist.linear.y;
	odom.twist.twist.angular.z = msg->twist.angular;
	odom.twist.covariance = odom.pose.covariance;

	pub_odometry_cov->publish(odom);
}


void NodeTriskarOdometry::setPublisherOdometry(ros::Publisher * pub){
	this->pub_odometry_cov = pub;
}

int main(int argc, char **argv){
	NodeTriskarOdometry node;
	ros::init(argc, argv, "odometry_triskar_node");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("odometry_triskar", 1, &NodeTriskarOdometry::callbackNewOdometry, &node);
	ros::Publisher pub_odometry_cov = n.advertise<nav_msgs::Odometry>("odometry_triskar_cov", 1);
	node.setPublisherOdometry(&pub_odometry_cov);
	ros::spin();
}
