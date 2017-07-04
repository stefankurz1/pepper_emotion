/*
 * NodeLandmarkGlobalLocalization.h
 *
 *  Created on: Aug 18, 2015
 *      Author: julian
 */

#ifndef NODELANDMARKGLOBALLOCALIZATION_H_
#define NODELANDMARKGLOBALLOCALIZATION_H_

#include <math.h>
#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "ar_track_alvar_msgs/AlvarMarker.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "theatre_bot/OdometryTriskar.h"
#include "theatre_bot/OdometriesTriskar.h"
#include "../src/Eigen/Dense"

class NodeLandmarkGlobalLocalization {
public:
	NodeLandmarkGlobalLocalization();
	virtual ~NodeLandmarkGlobalLocalization();
	void callbackNewMarkerBlueCamera(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
	void callbackNewMarkerBlackCamera(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg);
	void setTransformListenerBlueCamera(tf::TransformListener *listener);
	void setTransformListenerBlackCamera(tf::TransformListener *listener);
	void setPublisherGlobalPosition(ros::Publisher * pub);
	void updatePosition();
private:
	tf::TransformListener *listener_blue_camera;
	tf::TransformListener *listener_black_camera;
	ros::Publisher * pub_global_position;
	float time_to_wait;
	ros::Time last_time;
	ros::Duration difference_time;
	bool first_execution;
	std::vector<ar_track_alvar_msgs::AlvarMarker> markers_info_blue_camera;
	std::vector<ar_track_alvar_msgs::AlvarMarker> markers_info_black_camera;
	//Additional variables to calculate the robot velocity
	float blue_camera_last_position_x;
	float blue_camera_last_position_y;
	float blue_camera_last_position_yaw_x;
	float blue_camera_last_position_yaw_y;
	ros::Time last_time_blue_camera;
	ros::Duration difference_time_blue_camera;
	float difference_blue_camera;
	float black_camera_last_position_x;
	float black_camera_last_position_y;
	float black_camera_last_position_yaw_x;
	float black_camera_last_position_yaw_y;
	ros::Time last_time_black_camera;
	ros::Duration difference_time_black_camera;
	float difference_black_camera;
	/*Methods*/
	//This method calculates the robot position given the position of the cameras
	bool getRobotPosition(ar_track_alvar_msgs::AlvarMarker marker, tf::TransformListener *listener, float *counter,float *positions_x,float *positions_y,float *positions_yaw_x,float *positions_yaw_y);
	//This method calculates the next possible position where the robot could be, this is done using the last and current image
	void calculatePossiblePosition(float time,float position_x,float position_y,float position_yaw_x,float position_yaw_y,float last_position_x,float last_position_y,float last_position_yaw_x,float last_position_yaw_y,
			float *possible_position_x,float *possible_position_y, float *possible_position_yaw);
	void isFirstExecution();
	void verifyAngle(float *angle);
};

#endif /* NODELANDMARKGLOBALLOCALIZATION_H_ */
