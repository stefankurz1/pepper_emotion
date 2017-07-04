/*
 * NodeActionModulation.h
 *
 *  Created on: Dec 28, 2014
 *      Author: julian
 */

#ifndef NODEACTIONMODULATION_H_
#define NODEACTIONMODULATION_H_

#include <string>
#include <vector>

#include "ros/ros.h"

#include "theatre_bot/EmotionMessage.h"
#include "theatre_bot/ActionService.h"
#include "theatre_bot/ActionExecutionMessage.h"

#include "../src/ActionModulation/ActionModulationSubSystem.h"
#include "../src/ActionModulation/ActionModulationSubSystem.h"

class NodeActionModulation {
public:
	NodeActionModulation();
	virtual ~NodeActionModulation();
	void callbackNewEmotion(const theatre_bot::EmotionMessage::ConstPtr& msg);
	bool callbackNewAction(theatre_bot::ActionService::Request &req, theatre_bot::ActionService::Response &res);
	void callbackActionExecutionSynch(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);
	void loadInformation();
	void setPathEmotion(std::string path_emotion);
	void setPathCharacter(std::string path_character);

	void setActionsParameter(std::map<std::string,ros::Publisher *> pub_actions_parameter);
	void setEmotionParameter(std::map<std::string,ros::Publisher *> pub_emotion_parameter);
private:
	void stopActions(std::vector<std::string> list);
	void sendActionsInformation(std::map<std::string,std::string> list_message_actions);
	void sendActionsEmotionInformation(std::map<std::string,std::string> list_message_actions);
	std::map<std::string,std::string> eliminateUnStopActions(std::map<std::string,std::string> list_message_actions,std::vector<std::string> list);
	ActionModulationSubSystem action_modulation_sub_system;

	std::string path_name_emotion;
	std::string path_name_character;

	std::map<std::string,ros::Publisher *> pub_action_parameter;
	std::map<std::string,ros::Publisher *> pub_emotion_parameter;
};


#endif /* NODEACTIONMODULATION_H_ */
