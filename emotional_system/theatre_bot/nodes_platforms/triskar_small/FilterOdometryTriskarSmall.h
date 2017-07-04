/*
 * FilterOdometryTriskarSmall.h
 *
 *  Created on: May 19, 2015
 *      Author: julian
 */

#ifndef FILTERODOMETRYTRISKARSMALL_H_
#define FILTERODOMETRYTRISKARSMALL_H_

#include "math.h"
class FilterOdometryTriskarSmall {
public:
	FilterOdometryTriskarSmall();
	virtual ~FilterOdometryTriskarSmall();
	void setRobotInTheScene(float robot_initial_x, float robot_initial_y, float robot_initial_z, float robot_initial_angle);
private:
	float initial_robot_position_x;
	float initial_robot_position_y;
	float initial_robot_position_theta;
	void verifyAngle(float *angle);
};

#endif /* FILTERODOMETRYTRISKARSMALL_H_ */
