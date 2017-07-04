/*
 * TriskarPlanner.h
 *
 *  Created on: Feb 26, 2015
 *      Author: julian
 */

#ifndef TRISKARPLANNER_H_
#define TRISKARPLANNER_H_

#include "math.h"
#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include "theatre_bot/TriskarVelocity.h"
#include "../../WorldModelDescription/TheatrePlaces.h"
#include "../../Parameters/MovementParameters/Point.h"
#include "../../Parameters/MovementParameters/Circle.h"
#include "../../Parameters/MovementParameters/Square.h"
#include "../../Parameters/MovementParameters/Landmark.h"
#include "../../Parameters/MovementParameters/TypePosition.h"
#include "../../Parameters/MovementParameters/TypeLandmark.h"

class TriskarPlanner {
public:
	TriskarPlanner();
	virtual ~TriskarPlanner();
	void setVariables(float yaw_error,float velocity_rotate, float linear_velocity, float reduce_linear_velocity,float reduce_angular_velocity,float x_error,float y_error);
	void setPoint(boost::shared_ptr<Point> parameter);
	void setLandmark(boost::shared_ptr<Landmark>  parameter);
	void setSquare(boost::shared_ptr<Square> parameter);
	void setCircle(boost::shared_ptr<Circle> parameter);
	void setLastPosition(float last_position_x, float last_position_y);
	bool updateLinearVelocity(float x_position, float y_position,float yaw_position, theatre_bot::TriskarVelocity *message,TheatrePlaces theatre_place);
	bool updateAngularVelocity(float yaw_position, theatre_bot::TriskarVelocity *message);
	bool hasArrived();
	float getDesireYaw();

	void setTypeParameter(TypePosition type_position);
	void setLinearVelocity(float linear_velocity);
	void setVelocities(float linear_velocity, float angular_velocity);

	bool getHasAngle();
	float getCurrentDistance();
	void resetCurrentDistance();
	bool isReducingVelocity();

private:
	//Information used to calculate velocities
	float yaw_error; //Maximum error in the turn
	float velocity_rotate; // desire velocity when it has to turn
	float linear_velocity; // desire velocity when it has to move
	float reduce_linear_velocity; //distance in which it has to start to stop moving
	float reduce_angular_velocity; // distance in which it has to start to stop turning
	float x_error; //maximum error
	float y_error;
	bool has_arrived_linear;
	bool has_arrived_angular;
	bool first_iteration;
	float current_distance;
	//Initial position to make calculate the whole distance
	float last_position_x;
	float last_position_y;
	float desire_yaw;
	bool has_angle;
	//Desire position
	float desire_x;
	float desire_y;
	bool is_reducing_velocity;
	//Parameter
	TypePosition type_position;
	boost::shared_ptr<Point> parameter_point; //Scene's frame of reference
	boost::shared_ptr<Point> parameter_point_robots_frame; //Scene's frame of reference
	boost::shared_ptr<Landmark> parameter_landmark;
	boost::shared_ptr<Square> parameter_square;
	boost::shared_ptr<Circle> parameter_circle;

	bool updateLinearVelocityPointParameter(float x_position, float y_position,float yaw_position, theatre_bot::TriskarVelocity *message);
	void calculateDesireAngle(Quaternion parameter);
	float fabs(float num);
	float signum(float num);
	float correctAngle(float distance_theta);
	void clearPointers();
};

#endif /* TRISKARPLANNER_H_ */
