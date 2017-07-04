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
#include "theatre_bot/OdometriesTriskar.h"
#include "theatre_bot/Vector32.h"
#include "std_msgs/Char.h"
#include "../src/Parsers/ParserConfigurationFiles.h"
#include "../src/Parsers/KalmanParser.h"
#include "../src/Eigen/Dense"

class NodeLandmarkLocalization {
public:
	NodeLandmarkLocalization();
	virtual ~NodeLandmarkLocalization();
	void callbackNewMarker(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
	void callbackNewGlobalPosition(const theatre_bot::OdometriesTriskar::ConstPtr& msg);
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
	//Robot current global position which is capture by the vision system on the stage
	Eigen::Vector3f robot_global;
	float new_global_information;
	ros::Time last_time_received_global;
	ros::Duration difference_time_global;
	//Variables to save the time
	float time_to_wait;
	ros::Time last_time;
	ros::Duration difference_time;
	ros::Time last_time_odometry_message;
	ros::Time last_time_webcam_message;
	ros::Duration difference_time_odometry_message;
	std::vector<ar_track_alvar_msgs::AlvarMarker> markers_info;
	std::vector<theatre_bot::OdometryTriskar> position_info;
	std::ofstream myfile_position;
	std::ofstream myfile_marker;
	/*Kalman*/
	Eigen::Matrix3f sigma;
	Eigen::Matrix3f sigma_initial;
	Eigen::Matrix3f G;
	Eigen::Matrix3f R;//This is the error in motion
	Eigen::Matrix3f R_Coefficients;//This is the error in motion coefficients
	Eigen::Matrix3f Q;//Markers
	Eigen::Matrix3f Q_global;//Global information
	Eigen::Matrix3f Q_odometry;//
	Eigen::Matrix3f Fu;//Derivate respect control variable
	//Control
	Eigen::Vector3f u;
	Eigen::Vector3f u_real;
	//Measure
	Eigen::Vector2f d;
	Eigen::Vector2f z_ideal;
	Eigen::Vector3f z_odometry;
	float q;
	bool first_execution;
	bool is_moving;
	bool new_message_odometry;
	bool new_message_sensor;
	int count_not_moving;
	//Mean
	float mean_x;
	float mean_y;
	float mean_yaw;
	float mean_x_y;
	float mean_x_yaw;
	float mean_y_yaw;
	int mean_quantity;
	//Variance
	float variance_x;
	float variance_y;
	float variance_yaw;
	float variance_x_y;
	float variance_x_yaw;
	float variance_y_yaw;
	/*Methods*/
	void robotPositionGlobal(float global_position_x,float global_position_y, float global_position_yaw, float *local_position_x, float *local_position_y,float *local_position_yaw);
	void verifyAngle(float *angle);
};

#endif /* NODELANDMARKLOCALIZATION_H_ */
