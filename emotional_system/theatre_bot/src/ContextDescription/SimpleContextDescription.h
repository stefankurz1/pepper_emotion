///////////////////////////////////////////////////////////
//  SimpleContextDescription.h
//  Implementation of the Class SimpleContextDescription
//  Created on:      04-dic-2014 04:41:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(SIMPLECONTEXTDESCRIPTION_H_)
#define SIMPLECONTEXTDESCRIPTION_H_

#include "AbstractContextDescription.h"
#include <iostream>
#include <vector>
#include "../Parameters/EmotionalParameters/EmotionParameter.h"
#include "../EmotionDescription/ActionChanges.h"

#include <iostream>
class SimpleContextDescription : public AbstractContextDescription
{

public:
	SimpleContextDescription();
	virtual ~SimpleContextDescription();

	void setActionName(std::string action_name);
	void setActionParameters(std::string action_parameters);
	void setEmotionChanges(ActionChanges *  emotion_changes);
	std::string getActionName();
	std::string getActionParameters();
	ActionChanges getEmotionChanges();
	std::string getEmotionalParameterMessage();
	void setEmotionalParameterMessage(std::string emotion_message);
	void cleanEmotionParameters();
private:
	std::string action_name;
	/**
	 * This should be written in JSON, they should be send in a different channel that
	 * emotion parameters
	 */
	std::string action_parameters;
	/**
	 * This should be written in JSON, they should be send in a different channel that
	 * emotion parameters
	 */
	ActionChanges emotion_changes;

	std::string emotion_modify_parameters;

};
#endif // !defined(SIMPLECONTEXTDESCRIPTION_H_)
