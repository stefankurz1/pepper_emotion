/*
 * KeeponBody.h
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#ifndef KEEPONBODY_H_
#define KEEPONBODY_H_

#include "BodyAction.h"
#include "theatre_bot/KeeponMessage.h"

class KeeponBody: public BodyAction {
public:
	KeeponBody();
	virtual ~KeeponBody();

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

	void callbackUpdateKeepon(const theatre_bot::KeeponMessage::ConstPtr& msg);

private:

	ros::Publisher pub_action_keepon;

	ros::Subscriber sub;

	void generateEmotionalActionOscillate();
	void generateEmotionalVelocityOscillate();
	void initMessageKeepon(theatre_bot::KeeponMessage *message);
};

#endif /* KEEPONBODY_H_ */
