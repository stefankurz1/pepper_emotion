/*
 * NodeOdometryTriskar.h
 *
 *  Created on: May 19, 2015
 *      Author: julian
 */

#ifndef NODEODOMETRYTRISKAR_H_
#define NODEODOMETRYTRISKAR_H_

#include "ros/ros.h"
#include "theatre_bot/InitParamVelPos.h"
#include "theatre_bot/TriskarVelocity.h"
#include "theatre_bot/OdometryTriskar.h"

#include "FilterOdometryTriskarSmall.h"

#include "../../src/Parsers/ParserConfigurationFiles.h"

class NodeOdometryTriskar {
public:
	NodeOdometryTriskar();
	virtual ~NodeOdometryTriskar();
	void setProjectDirectory(std::string project_path);
	void loadInformation();
	void setInformation();

	void callbackNewInitParameters(const theatre_bot::InitParamVelPos::ConstPtr& msg);
	void callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg);
	void callBackCommand(const theatre_bot::TriskarVelocity::ConstPtr& msg);
private:
	std::string project_path;
	//The robot's initial position is needed to establish the position of the markers respect the robot
	float initial_robot_position_x;
	float initial_robot_position_y;
	float initial_robot_position_theta;
	FilterOdometryTriskarSmall filter;
};

#endif /* NODEODOMETRYTRISKAR_H_ */
