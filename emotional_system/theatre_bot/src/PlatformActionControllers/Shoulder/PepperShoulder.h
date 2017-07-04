/*
 * PepperShoulder.h
 *
 *  Created on: May 19, 2017
 *      Author: Stefan Kurz
 */

#ifndef PEPPERSHOULDER_H_
#define PEPPERSHOULDER_H_

#include "ShoulderAction.h"

#include "theatre_bot/PepperUpper.h"
#include "theatre_bot/PepperInfo.h"
#include "theatre_bot/Vector32.h"

class PepperShoulder: public ShoulderAction {
public:
	PepperShoulder();
	virtual ~PepperShoulder();
	void MoveShoulderAction(Amplitude parameter);
	void OscillateShoulderAction(Amplitude parameter);
	void stopMoveShoulderAction();
	void stopOscillateShoulderAction();
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);

	void synchEmotionMove();
	void synchEmotionOscillate();
	void setEmotionalMoveShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateShoulder(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);

	void callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg);
private:
	ros::Publisher pub_action_pepper;
	ros::Subscriber sub;

	float desire_angle_to_move;
	float max_angle;
	float min_angle;
	float max_angle_move;
	float min_angle_move;

	float velocity_base;
	float velocity_rotate;
	float velocity_oscillate;

	bool fin_move_flag;
	
	//Emotional variables
	int pos_move_x;
	int pos_oscillate_x;

	void generateEmotionalActionMove();
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void generateEmotionalVelocityMove();
	void sendMessage(bool movosc, float desire_angle, float velocity);
};

#endif /* PEPPERSHOULDER_H_ */
