/*
 * TriskarSmallShoulder.h
 *
 *  Created on: Mar 2, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLSHOULDER_H_
#define TRISKARSMALLSHOULDER_H_

#include "ShoulderAction.h"

#include "theatre_bot/TriskarSmallUpper.h"
#include "theatre_bot/Vector32.h"

class TriskarSmallShoulder: public ShoulderAction {
public:
	TriskarSmallShoulder();
	virtual ~TriskarSmallShoulder();
	void MoveShoulderAction(Amplitude parameter);
	void OscillateShoulderAction(Amplitude parameter);
	void stopMoveSholuderAction();
	void stopOscillateShoulderAction();
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);

	void synchEmotionMove();
	void synchEmotionOscillate();
	void setEmotionalMoveShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);

	void callbackUpdateTriskarUpper(const theatre_bot::Vector32::ConstPtr& msg);
private:
	ros::Publisher pub_action_triskar;
	ros::Subscriber sub;

	float max_angle;
	float min_angle;

	float angle_error;

	float left_current_angle;
	float right_current_angle;

	float velocity_base;
	bool forward_direction_left;
	bool forward_direction_right;

	//Emotional variables
	int pos_move_x;
	int pos_oscillate_x;


	float temp_angle;
	float last_angle;
	float minimum_change_angle;

	void initMessageTriskar(theatre_bot::TriskarSmallUpper *message);
	void generateEmotionalActionMove();
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void generateEmotionalVelocityMove();
	void sendMessage(float position_left, float position_right);
};

#endif /* TRISKARSMALLSHOULDER_H_ */
