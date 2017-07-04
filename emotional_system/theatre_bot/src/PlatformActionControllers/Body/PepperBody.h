/*
 * PepperBody.h
 *
 *  Created on: May 30, 2017
 *      Author: Stefan Kurz
 */

#ifndef PEPPERBODY_H_
#define PEPPERBODY_H_

#include "BodyAction.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "theatre_bot/PepperMove.h"
#include "theatre_bot/PepperInfo.h"
#include "std_msgs/Char.h"

class PepperBody: public BodyAction {
public:
	PepperBody();
	virtual ~PepperBody();

	void setPublisherAction(ros::NodeHandle *node);
	void initSubscriberAction(ros::NodeHandle *node);

	void MoveBodyAction(boost::shared_ptr<Position> parameter, TypePosition type_position);
	void OscillateBodyAction(Amplitude parameter);
	void stopMoveBodyAction();
	void stopOscillateBodyAction();
	void synchEmotionMove();
	void synchEmotionOscillate();
	void setEmotionalMoveBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void setEmotionalOscillateBody(std::vector<EmotionMovementParameter> vector_x,std::vector<EmotionMovementParameter> vector_y,std::vector<EmotionMovementParameter> vector_z, bool repet);
	void sendMessage(bool mode, Point parameter, bool stop);
	void callbackUpdatePepper(const theatre_bot::PepperInfo::ConstPtr& msg);
private:
	ros::Publisher pub_action_pepper;
	ros::Subscriber sub;

	float velocity_base;
	float min_angle;
	float max_angle;

	void verifyRange(float *number, float min, float max);
	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
};

#endif /* PEPPERBODY_H_ */
