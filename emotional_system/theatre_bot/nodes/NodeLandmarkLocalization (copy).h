/*
 * NodeLandmarkLocalization.h
 *
 *  Created on: Jul 3, 2015
 *      Author: julian
 */

#ifndef NODELANDMARKLOCALIZATION_H_
#define NODELANDMARKLOCALIZATION_H_

#include <math.h>
#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "geometry_msgs/PoseStamped.h"
#include "ar_track_alvar_msgs/AlvarMarker.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "theatre_bot/OdometryTriskar.h"
#include "std_msgs/Char.h"
#include "../src/Parsers/ParserConfigurationFiles.h"
#include "../src/Eigen/Dense"

class NodeLandmarkLocalization {
public:
	NodeLandmarkLocalization();
	virtual ~NodeLandmarkLocalization();
	void callbackNewMarker(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
	void callbackNewOdometry(const theatre_bot::OdometryTriskar::ConstPtr& msg);
	void callbackSpecialCommandsTriskar(const std_msgs::Char::ConstPtr& msg);
	void setPublisherOdometry(ros::Publisher * pub);
	void setTransformListener(tf::TransformListener *listener);
	void loadInformation();
	void setProjectDirectory(std::string directory);
	void updatePosition();
private:
	//Publisher
	ros::Publisher *pub_odometry;
	//Saves the project directory, this is used to load the marker's information
	std::string project_directory;
	//hash map that has all the markers that are used as landmarks
	std::map<int, MarkerPosition> markers_position;
	tf::TransformListener *listener;
	//Position of the robot at the begining of execution respect the scene's frame
	float robot_initial_yaw;
	float robot_initial_x;
	float robot_initial_y;
	//Robot current position
	float robot_current_yaw;
	float robot_current_x;
	float robot_current_y;
	float robot_last_x;
	float robot_last_y;
	float robot_last_yaw;
	double time_to_wait;
	bool is_moving;
	ros::Time last_time;
	ros::Duration difference_time;
	std::vector<ar_track_alvar_msgs::AlvarMarker> markers_info;
	std::ofstream myfile_position;
	std::ofstream myfile_marker;
	//Kalman
	Eigen::Matrix3f sigma;
	Eigen::Matrix3f sigma_initial;
	Eigen::Matrix3f G;
	Eigen::Matrix3f Fu;//This is derived respect control
	Eigen::Matrix3f R;//This is the error in motion
	Eigen::Matrix2f Q;
	//Measure
	Eigen::Vector2f d;
	Eigen::Vector2f z_ideal;
	float q;

	void verifyAngle(float *angle);
};

#endif /* NODELANDMARKLOCALIZATION_H_ */
