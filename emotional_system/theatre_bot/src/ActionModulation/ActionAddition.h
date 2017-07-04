/*

 * ActionAddition.h
 *
 *  Created on: Dec 15, 2014
 *      Author: julian
 */

#ifndef ACTIONADDITION_H_
#define ACTIONADDITION_H_

#include <typeinfo>

#include "../EmotionDescription/EmotionProfile.h"
#include "../LoadInformation/EmotionalLoad.h"
#include "../Parsers/ParserAction.h"
#include "../ActionDescription/SimpleActions/SimpleActionDoNothing.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionSpeak.h"
#include "../ActionDescription/CompositeActions/CompositeActionWalk.h"

class ActionAddition {
public:
	ActionAddition();
	virtual ~ActionAddition();
	void setPathName(std::string path_name);
	void loadEmotions();
	AbstractContextDescription * addAdditionalActions(std::string action_message, std::string emotion);
	void changeEmotionalAction(AbstractContextDescription ** context, std::string emotion);
	std::vector<std::string> getEmotions();
	std::vector<std::string> getActions();
private:
	void loadAvailableAction();
	/*
	 * This method gets the context three and expand each action to the new actions
	 */
	void addEmotionalActions(AbstractContextDescription ** context, std::string emotion);
	std::map<string, EmotionProfile *> emotions_available;
	std::map<std::string,AbstractActionDescription * >  available_actions;
	std::string path_name;
};

#endif /* ACTIONADDITION_H_ */
