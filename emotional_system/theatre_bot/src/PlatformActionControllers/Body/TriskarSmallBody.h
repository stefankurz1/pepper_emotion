/*
 * TriskarSmallBody.h
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#ifndef TRISKARSMALLBODY_H_
#define TRISKARSMALLBODY_H_

#include "BodyAction.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "theatre_bot/TriskarMessageEmotion.h"
#include "theatre_bot/TriskarMessage.h"
#include "theatre_bot/OdometryTriskar.h"
#include "std_msgs/Char.h"
#include "../../Parameters/MovementParameters/TypePosition.h"
#include "../../Parameters/MovementParameters/TypeLandmark.h"

class TriskarSmallBody: public BodyAction {
public:
	TriskarSmallBody();
	virtual ~TriskarSmallBody();

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

	void callBackUpdateTriskar(const theatre_bot::OdometryTriskar::ConstPtr& msg);
	void callBackSynchTriskar(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
private:
	ros::Publisher pub_action_triskar;
	ros::Publisher pub_emotion_triskar;
	ros::Publisher pub_command_triskar;
	ros::Subscriber sub_emotion_synch;
	ros::Subscriber sub_action_synch;
	ros::Subscriber sub_action;

	TypePosition type_position;
	boost::shared_ptr<Landmark> parameter_landmark;
	boost::shared_ptr<Square> parameter_square;
	boost::shared_ptr<Circle> parameter_circle;

	void sendtPoint(Point parameter);
	void calculateDesireAngle(Quaternion parameter);
	void setLandmark(boost::shared_ptr<Landmark>  parameter);
	void setSquare(boost::shared_ptr<Square> parameter);
	void setCircle(boost::shared_ptr<Circle> parameter);
	void clearPointers();
};

#endif /* TRISKARSMALLBODY_H_ */
