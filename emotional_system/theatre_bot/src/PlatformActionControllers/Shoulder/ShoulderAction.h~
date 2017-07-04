/*
 * ShoulderAction.h
 *
 *  Created on: Mar 1, 2015
 *      Author: julian
 */

#ifndef SHOULDERACTION_H_
#define SHOULDERACTION_H_

#include "ros/ros.h"
#include "tf/transform_datatypes.h"
#include "math.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../../Parameters/MovementParameters/Amplitude.h"
#include "../../Parameters/EmotionalParameters/EmotionMovementParameter.h"

class ShoulderAction {
public:
	ShoulderAction();
	virtual ~ShoulderAction();
	virtual void MoveShoulderAction(Amplitude parameter) = 0;
	virtual void OscillateShoulderAction(Amplitude parameter) = 0;
	virtual void stopMoveSholuderAction() = 0;
	virtual void stopOscillateShoulderAction() = 0;
	virtual void setPublisherAction(ros::NodeHandle *node) = 0;
	virtual void initSubscriberAction(ros::NodeHandle *node) = 0;

	virtual void synchEmotionMove() = 0;
	virtual void synchEmotionOscillate() = 0;
	virtual void setEmotionalMoveShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet) = 0;
	virtual void setEmotionalOscillateShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet) = 0;

	float updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle);
	float updateOscillation(float desire_velocity, float current_angle, float min_angle, float max_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	void setPublisherActionSynch(ros::Publisher *pub_action_synch);
	void setActionMoveName(std::string action_name);
	void setActionOscillateName(std::string action_name);
protected:
	//front and back
	float desire_angle_to_move_left;
	float desire_angle_to_move_right;
	std::string action_move_name;
	std::string action_oscillation_name;
	float delta_time;
	float velocity_move;
	float velocity_rotate;
	float velocity_emotional_rotate;
	float desire_angle_to_oscillate;
	bool is_moving;
	bool is_oscillating;
	bool is_moving_emotional;
	bool is_oscillating_emotional;
	bool repeat_move;
	bool repeat_oscillation;
	ros::Publisher *pub_action_synch;
	std::vector<EmotionMovementParameter> move_x;
	std::vector<EmotionMovementParameter> move_y;
	std::vector<EmotionMovementParameter> move_z;
	std::vector<EmotionMovementParameter> oscillate_x;
	std::vector<EmotionMovementParameter> oscillate_y;
	std::vector<EmotionMovementParameter> oscillate_z;
	float updateOscillation(float desire_velocity, float current_angle, float desire_angle_to_move, float desire_angle_to_oscillate, float error, bool *forward_direction);
	void verifyRange(float *number, float min, float max);
	template <typename T> T sgn(T val){
	    return (T(0) < val) - (val < T(0));
	}

};

#endif /* SHOULDERACTION_H_ */
