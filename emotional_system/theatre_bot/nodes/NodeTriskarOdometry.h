/*
 * NodeTriskarOdometry.h
 *
 *  Created on: Jun 30, 2015
 *      Author: julian
 */

#ifndef NODETRISKARODOMETRY_H_
#define NODETRISKARODOMETRY_H_

#include "ros/ros.h"
#include "theatre_bot/OdometryTriskar.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_broadcaster.h"

class NodeTriskarOdometry {
public:
	NodeTriskarOdometry();
	virtual ~NodeTriskarOdometry();
	void callbackNewOdometry(const theatre_bot::OdometryTriskar::ConstPtr& msg);
	void setPublisherOdometry(ros::Publisher * pub);
private:
	ros::Publisher *pub_odometry_cov;
	ros::Time current_time;
};

#endif /* NODETRISKARODOMETRY_H_ */
