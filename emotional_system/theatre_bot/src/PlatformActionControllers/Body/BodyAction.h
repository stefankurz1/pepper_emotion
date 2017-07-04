#ifndef BODYACTION_H_
#define BODYACTION_H_

#include <boost/shared_ptr.hpp>
#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include <math.h>
#include "theatre_bot/ActionExecutionMessage.h"
#include "../../Parameters/MovementParameters/TypePosition.h"
#include "../../Parameters/MovementParameters/Circle.h"
#include "../../Parameters/MovementParameters/Position.h"
#include "../../Parameters/MovementParameters/Point.h"
#include "../../Parameters/MovementParameters/Square.h"
#include "../../Parameters/MovementParameters/Landmark.h"
#include "../../Parameters/MovementParameters/Amplitude.h"
#include "../../Parameters/EmotionalParameters/EmotionMovementParameter.h"
#include "../../WorldModelDescription/TheatrePlaces.h"

class BodyAction {
public:
	BodyAction();
	virtual ~BodyAction();

	virtual void MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position) = 0;
	virtual void OscillateBodyAction(Amplitude parameter) = 0;
	virtual void stopMoveBodyAction() = 0;
	virtual void stopOscillateBodyAction() = 0;
	virtual void synchEmotionMove() = 0;
	virtual void synchEmotionOscillate() = 0;
	virtual void setPublisherAction(ros::NodeHandle *node) = 0;
	virtual void initSubscriberAction(ros::NodeHandle *node) = 0;
	virtual void setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet) = 0;
	virtual void setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet) = 0;

	void setPublisherActionSynch(ros::Publisher *pub_action_synch);
	void setActionMoveName(std::string name);
	void setActionOscillateName(std::string name);
	void setLinearVelocity(float linear_velocity);
	void setAngularVelocity(float angular_velocity);
	/*
	 * This method sets the robot respect the frame, this allows having the frame of reference of the robot in a different position.
	 */
	void setRobotInTheScene(float robot_initial_x, float robot_initial_y, float robot_initial_z, float robot_initial_angle);
	void setTheatrePlaceInformation(TheatrePlaces theatre_place);
protected:
	TheatrePlaces theatre_place;
	std::string action_move_name;
	std::string action_oscillation_name;
	float delta_time;

	ros::Publisher *pub_action_synch;
	//Move
	float x; //Current x position of the platform
	float y; //Current y position of the platform
	float z; //Current z position of the platform
	float x_error; //Maximum error in x
	float y_error; //Maximum error in y
	float z_error; //Maximum error in z
	float desire_x; //Desire x
	float desire_y; //Desire y
	float desire_z; //Desire z
	float yaw; //Current yaw
	float pitch; //Current pitch
	float roll; //Current roll
	float yaw_error; //Maximum error in yaw
	float pitch_error; //Maximum error in pitch
	float roll_error; //Maximum error in roll
	float desire_yaw; //Desire yaw
	float desire_pitch;
	float desire_roll;
	bool is_moving;
	float velocity_rotate;//It is the same for oscillation
	float linear_velocity; //it is the desire velocity to move the platform
	float maximum_linear_velocity;
	float maximum_angular_velocity;
	//Oscillate
	float desire_angle_to_oscillate_yaw;
	float desire_angle_to_oscillate_pitch;
	float desire_angle_to_oscillate_roll;
	bool forward_direction_yaw;
	bool forward_direction_pitch;
	bool forward_direction_roll;
	bool is_oscillating;
	float velocity_oscillate_yaw;
	float velocity_oscillate_pitch;
	float velocity_oscillate_roll;
	//Emotion variable
	bool is_moving_emotional;
	bool is_oscillating_emotional;
	//Emotional parameters
	float velocity_emotional_rotate;
	bool repeat_move;
	bool repeat_oscillation;
	int pos_move_x;
	int pos_move_y;
	int pos_move_z;
	int pos_oscillate_x;
	int pos_oscillate_y;
	int pos_oscillate_z;
	//Initial position of the robot in the scene, if the parameters are not given, it means that is <0,0,0>
	float robot_initial_position_x;
	float robot_initial_position_y;
	float robot_initial_position_z;
	float robot_initial_angle;
	std::vector<EmotionMovementParameter> move_x;
	std::vector<EmotionMovementParameter> move_y;
	std::vector<EmotionMovementParameter> move_z;
	std::vector<EmotionMovementParameter> oscillate_x;
	std::vector<EmotionMovementParameter> oscillate_y;
	std::vector<EmotionMovementParameter> oscillate_z;
	float updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	void verifyAngle(float *number);
};

#endif /* BODYACTION_H_ */
