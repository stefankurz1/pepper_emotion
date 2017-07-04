/*
 * NodeShoulderActionExecution.h
 *
 *  Created on: Mar 1, 2015
 *      Author: julian
 */

#ifndef NODESHOULDERACTIONEXECUTION_H_
#define NODESHOULDERACTIONEXECUTION_H_

#include <string>
#include <vector>

#include "ros/ros.h"
#include "../src/json/json/json.h"
#include "../src/Parsers/EmotionParser.h"
#include "../src/Parameters/MovementParameters/Amplitude.h"
#include "../src/Parameters/EmotionalParameters/EmotionMovementParameter.h"
#include "../src/PlatformActionControllers/Shoulder/TriskarSmallShoulder.h"
#include "../src/PlatformActionControllers/Shoulder/PepperShoulder.h"

class NodeShoulderActionExecution {
public:
	NodeShoulderActionExecution();
	virtual ~NodeShoulderActionExecution();

	void callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void callbackNewEmotionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void setPlatform(std::string platform, ros::NodeHandle *node);
	void setPublisherActionSynch(ros::Publisher *pub_message);
private:
	EmotionParser emotion_parser;
	ros::Publisher *pub_action_synch;
	std::string action_name_move;
	std::string action_name_oscillate;

	//CallbackFunction
	ShoulderAction *shoulder_action;
	void  callbackEmtyPlatform(Amplitude amplitude_parameter);
	bool parserJSON(std::string parameter, Amplitude *result);
};

#endif /* NODESHOULDERACTIONEXECUTION_H_ */
