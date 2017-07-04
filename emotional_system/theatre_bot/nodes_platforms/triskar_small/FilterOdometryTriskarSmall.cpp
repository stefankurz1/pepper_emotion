/*
 * FilterOdometryTriskarSmall.cpp
 *
 *  Created on: May 19, 2015
 *      Author: julian
 */

#include "FilterOdometryTriskarSmall.h"

FilterOdometryTriskarSmall::FilterOdometryTriskarSmall() {
	this->initial_robot_position_theta = 0.0;
	this->initial_robot_position_x = 0.0;
	this->initial_robot_position_y = 0.0;

}

FilterOdometryTriskarSmall::~FilterOdometryTriskarSmall() {
	// TODO Auto-generated destructor stub
}

void FilterOdometryTriskarSmall::verifyAngle(float *angle){
	if(*angle>M_PI){
		*angle= *angle-2.0*M_PI;
	}else if(*angle<-M_PI){
		*angle = *angle+2.0*M_PI;
	}
}


void FilterOdometryTriskarSmall::setRobotInTheScene(float robot_initial_x, float robot_initial_y, float robot_initial_z, float robot_initial_angle){
	this->initial_robot_position_theta = robot_initial_angle;
	this->initial_robot_position_x = robot_initial_x;
	this->initial_robot_position_y = robot_initial_y;
	verifyAngle(&this->initial_robot_position_theta);
}
