/*
 * PepperTorso.h
 *
 *  Created on: Jan 27, 2015
 *      Author: julian
 */

#ifndef PEPPERTORSO_H_
#define PEPPERTORSO_H_

#include "TorsoAction.h"

#include "theatre_bot/PepperUpper.h"
#include "theatre_bot/PepperInfo.h"
#include "theatre_bot/Vector32.h"

class PepperTorso: public TorsoAction {
public:
	PepperTorso();
	virtual ~PepperTorso();
	void MoveTorsoAction(Amplitude parameter);
	void OscillateTorsoAction(Amplitude parameter);
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);
	void stopMoveTorsoAction();
	void stopOscillateTorsoAction();
	void callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg);
	void sendMessage(float position);
	void setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void synchEmotionMove();
	void synchEmotionOscillate();
private:
	ros::Publisher pub_action_pepper;
	ros::Subscriber sub;

	float desire_angle_to_move_x;
	float desire_angle_to_move_y;
	
	float max_angle_x;
	float min_angle_x;
	float max_angle_move_x;
	float min_angle_move_x;
	float max_angle_y;
	float min_angle_y;
	float max_angle_move_y;
	float min_angle_move_y;

	float velocity_base;
	float velocity_rotate;
	bool fin_move_x_flag;
	bool fin_move_y_flag;
	
	//Emotional variables
	int pos_move_x;
	int pos_move_y;
	int pos_oscillate_x;
	int pos_oscillate_y;

	void generateEmotionalActionMove();
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void generateEmotionalVelocityMove();
	void sendMessage(bool x, bool mode, float desire_angle, float velocity);
};

#endif /* PEPPERTORSO_H_ */
