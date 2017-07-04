/*
 * TriskarSmallTorso.h
 *
 *  Created on: Jan 27, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLTORSO_H_
#define TRISKARSMALLTORSO_H_

#include "TorsoAction.h"
#include "theatre_bot/TriskarSmallUpper.h"
#include "theatre_bot/Vector32.h"

class TriskarSmallTorso: public TorsoAction {
public:
	TriskarSmallTorso();
	virtual ~TriskarSmallTorso();
	void MoveTorsoAction(Amplitude parameter);
	void OscillateTorsoAction(Amplitude parameter);
	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);
	void stopMoveTorsoAction();
	void stopOscillateTorsoAction();
	void callbackUpdateTriskarUpper(const theatre_bot::Vector32::ConstPtr& msg);
	void sendMessage(float position);
	void setEmotionalMoveTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateTorso(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void synchEmotionMove();
	void synchEmotionOscillate();
private:
	ros::Publisher pub_action_triskar;
	ros::Subscriber sub;

	float max_angle;
	float min_angle;

	float current_angle;
	float angle_error;
	float temp_angle;
	float last_angle;
	float minimum_change_angle;
	float velocity_move;
	float velocity_oscillate;


	void initMessageTriskar(theatre_bot::TriskarSmallUpper *message);
	void generateEmotionalActionMove();
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void generateEmotionalVelocityMove();
};

#endif /* TRISKARSMALLTORSO_H_ */
