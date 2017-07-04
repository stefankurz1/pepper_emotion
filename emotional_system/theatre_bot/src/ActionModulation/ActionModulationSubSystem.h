/*
 * ActionModulationSubSystem.h
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 *
 *      This action controls the whole sub-system
 */

#ifndef ACTIONMODULATIONSUBSYSTEM_H_
#define ACTIONMODULATIONSUBSYSTEM_H_

#include "ActionAddition.h"
#include "ActionModulation.h"
#include "ActionExecution.h"

class ActionModulationSubSystem {
public:
	ActionModulationSubSystem();
	virtual ~ActionModulationSubSystem();

	void callBackNewEmotion(std::string emotion, float intensity);
	void callBackNewAction(std::string action_message);
	void setPathEmotion(std::string emotion_path);
	void setPathCharacterPace(std::string character_pace);
	void loadInformation();
	std::vector<std::string> actionSynchronization(std::string action_name);
	std::vector<std::string> emotionSynchronization(std::string action_name);
	std::vector<std::string> getActions();
	std::vector<std::string> getEmotions();

	std::map<std::string,std::string> generateParameterMessage();
	std::map<std::string,std::string> generateEmotionalParameterMessage();

	std::vector<std::string> actiosToStop();

	void clearListNewAction();
	std::map<std::string,std::string> getListNewAction();
	std::map<std::string,std::string> getListNewActionEmotional();
private:
	void printContext(AbstractContextDescription *context);
	void printContext(AbstractContextDescription *context, std::string tab);
	ActionAddition 		action_addition;
	ActionModulation	action_modulation;
	ActionExecution		action_execution;

	AbstractContextDescription *context;

	std::string			last_action;
	std::string			last_emotion;
	float				last_intensity;

	std::string			emotion_path;
	std::string			charater_pace_path;
};

#endif /* ACTIONMODULATIONSUBSYSTEM_H_ */
