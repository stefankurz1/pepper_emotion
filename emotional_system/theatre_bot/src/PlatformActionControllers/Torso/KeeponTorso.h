/*
 * KeeponTorso.h
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#ifndef KEEPONTORSO_H_
#define KEEPONTORSO_H_

#include "TorsoAction.h"
#include "../TypePlatform.h"
#include "theatre_bot/KeeponMessage.h"

class KeeponTorso: public TorsoAction {
public:
	KeeponTorso();
	virtual ~KeeponTorso();
	void MoveTorsoAction(Amplitude parameter);
	void OscillateTorsoAction(Amplitude parameter);
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);
	void callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg);
	void stopMoveTorsoAction();
	void stopOscillateTorsoAction();
	void setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void synchEmotionMove();
	void synchEmotionOscillate();
private:
	ros::Publisher pub_action_keepon;

	ros::Subscriber sub;

	float tilt;
	float min_tilt;
	float max_tilt;

	float side;
	float min_side;
	float max_side;

	float pon;
	float min_pon;
	float max_pon;

	//Errors
	float tilt_error;
	float side_error;
	float pon_error;
	//Variables to control velocity
	float last_angle_tilt;
	float last_angle_side;
	float temp_angle_tilt;
	float temp_angle_side;
	float minimum_change_angle;
	//Variables to detect end of movement
	bool has_finish_tilt;
	bool has_finish_side;

	void initMessageKeepon(theatre_bot::KeeponMessage *message);
	void generateEmotionalActionMove();
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();

};

#endif /* KEEPONTORSO_H_ */
