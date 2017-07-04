/*
 * ActionExecution.h
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 */

#ifndef ACTIONEXECUTION_H_
#define ACTIONEXECUTION_H_

#include <typeinfo>

#include "MessageType.h"

#include "../ContextDescription/CompositeContextDescription.h"
#include "../ContextDescription/SimpleContextDescription.h"

class ActionExecution {
public:
	ActionExecution();
	virtual ~ActionExecution();
	void changeInEmotion(AbstractContextDescription * context);
	void changeInIntensity(AbstractContextDescription * context);
	void changeInAction(AbstractContextDescription * context);
	void stopAction();
	void stopEmotionalActions();
	//Action synchronization
	void actionSynchronization(std::string action_name);
	//Emotion synchronization
	void emotionSynchronization(std::string action_name);

	void lock();
	void unlock();

	std::vector<std::string> getListActionsToStop();
	void cleanListActionsToStop();
	std::vector<std::string> getListEmotionalActionToSynch();
	void cleanListEmotionalActionToSynch();

	std::map<std::string,std::string> generateParameterMessage();
	std::map<std::string,std::string> generateEmotionalParameterMessage();

	void clearListNewAction();
	std::map<std::string,std::string> getListNewAction();
	std::map<std::string,std::string> getListNewActionEmotional();
	void printQueue();

private:
	void propagateActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context,bool has_be_in_predecessor);
	void propagateEmotionalActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context,bool has_be_in_predecessor);
	//this cleans the emotions and current action queue
	void deleteActionsQueue();
	void sendEmotionalMessages();
	void sendActionMessages();
	void addEmotionalAction(SimpleContextDescription * temp_context);
	std::map<std::string,SimpleContextDescription *> current_actions;
	std::map<std::string,SimpleContextDescription *> current_emotional_actions;
	std::vector<std::string> list_actions_to_stop;
	std::vector<std::string> list_actions_to_emotional_synch;
	std::map<std::string,std::string> list_new_actions;
	std::map<std::string,std::string> list_new_actions_emotional;

	bool updating_data;
};

#endif /* ACTIONEXECUTION_H_ */
