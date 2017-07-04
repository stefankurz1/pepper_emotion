/*
 * ActionAddition.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: julian
 */

#include "ActionAddition.h"

ActionAddition::ActionAddition() {
	this->loadAvailableAction();

}

ActionAddition::~ActionAddition() {
	for(std::map<std::string,AbstractActionDescription * >::iterator it = available_actions.begin();
			it != available_actions.end(); ++it){
		delete it->second;
	}
	for(std::map<string, EmotionProfile *>::iterator it = emotions_available.begin();
			it != emotions_available.end(); ++it){
		delete it->second;
	}
}


void ActionAddition::setPathName(std::string path_name){
	this->path_name = path_name;
}

void ActionAddition::loadEmotions(){
	EmotionalLoad emotion_load;
	if(emotions_available.size()!=0){
		for(std::map<string, EmotionProfile *>::iterator it = emotions_available.begin();
				it != emotions_available.end(); ++it){
			delete it->second;
		}
	}
	emotion_load.setDirectoryPath(this->path_name);
	emotion_load.LoadInformation();
	emotions_available = emotion_load.getEmotionsAvailable();
}

AbstractContextDescription * ActionAddition::addAdditionalActions(std::string action_message, std::string emotion){
	ParserAction  parserAction;
	parserAction.setActionsAvailable(&available_actions);
	//Generate the context tree of the current messate
	AbstractContextDescription *context  = parserAction.parser(action_message);
	//Add emotional actions
	if(emotion.compare("neutral")!=0  && context != 0){
		addEmotionalActions(&context,emotion);
	}
	return context;
}


std::vector<std::string> ActionAddition::getEmotions(){
	std::vector<std::string> list_name_emotions;
	for(std::map<string, EmotionProfile *>::iterator it = emotions_available.begin(); it != emotions_available.end(); ++it){
		list_name_emotions.push_back(it->first);
	}
	return list_name_emotions;
}
std::vector<std::string> ActionAddition::getActions(){
	std::vector<std::string> list_name_actions;
	for(std::map<std::string,AbstractActionDescription * >::iterator it = available_actions.begin(); it != available_actions.end(); ++it){
		list_name_actions.push_back(it->first);
	}
	return list_name_actions;
}

void ActionAddition::changeEmotionalAction(
		AbstractContextDescription ** context, std::string emotion) {
	//Search for the principal action that helps to identify the emotional context node
	if (typeid(**context).name() == typeid(CompositeContextDescription).name()) {
		CompositeContextDescription * temp_composite_action = static_cast<CompositeContextDescription *>(*context);
		std::vector<AbstractContextDescription *> * next_context = temp_composite_action->getSubContextPointer();
		if ((*context)->getIsEmotional()) {
			SimpleContextDescription * simple_context_principal, *simple_context_temp;
			//Get all the actions that are emotional and delete them
			for (unsigned int i = 0; i < next_context->size(); ++i) {
				simple_context_temp = static_cast<SimpleContextDescription *>(next_context->at(i));
				if (simple_context_temp->getIsEmotional()) {
					delete simple_context_temp;
				} else {
					simple_context_principal = simple_context_temp;
				}
			}
			next_context->clear();
			//Get the principal action and look for the principal action emotion's specification
			std::map<std::string, EmotionProfile *>::iterator emotion_profile =
					emotions_available.find(emotion + "_"+ simple_context_principal->getActionName());
			if (emotion_profile != emotions_available.end()) {
				std::vector<ActionChanges *> temp_action_changes = emotion_profile->second->getActionChanges();
				for (std::vector<ActionChanges *>::iterator it = temp_action_changes.begin();
						it != temp_action_changes.end(); ++it) {
					//if the action is the same that we want just add the emotional parameters
					if ((*it)->getActionThatModyfies().compare(
							simple_context_principal->getActionName()) == 0) {
						simple_context_principal->setEmotionChanges(
								(*it));
						next_context->push_back(simple_context_principal);
					} else {
						std::map<std::string, AbstractActionDescription *>::iterator temp_action =
								available_actions.find(
										(*it)->getActionThatModyfies());
						if (temp_action != available_actions.end()) {
							SimpleContextDescription * temp_simple_context =
									static_cast<SimpleContextDescription *>(temp_action->second->analyze());
							temp_simple_context->setPredecessor(
									temp_composite_action);
							temp_composite_action->addNextContext(
									temp_simple_context);
							temp_simple_context->setIsEmotional(true);
							temp_simple_context->setIsPrimaryContext(false);
							temp_simple_context->setEmotionChanges(
									(*it));
						}
					}
				}
			} else {
				simple_context_principal->cleanEmotionParameters();
				next_context->push_back(simple_context_principal);
			}
		} else {
			for (unsigned int i = 0; i < next_context->size(); ++i) {
				this->changeEmotionalAction(&(next_context->at(i)), emotion);
			}
		}
	} else if (typeid(**context).name()
			== typeid(SimpleContextDescription).name()
			/*&& (*context)->getPredecessor() == 0*/) {
		addEmotionalActions(context, emotion);
	}
}

/*
 * Case action different even if the emotion is same or different
 */
void ActionAddition::addEmotionalActions(AbstractContextDescription ** context, std::string emotion){
	if(typeid(**context).name()==typeid(SimpleContextDescription).name()){
		//search the action in the emotion data base
		SimpleContextDescription *simple = static_cast<SimpleContextDescription *>(*context);
		std::map<std::string,EmotionProfile * >::iterator emotion_profile = emotions_available.find(emotion+"_"+simple->getActionName());
		if(emotion_profile != emotions_available.end()){
			//Create Composite context
			CompositeContextDescription * temp_composite_context = new CompositeContextDescription;
			//Add context information parallel and if the action is principal, this become principal
			temp_composite_context->setEmotionalSynch(true);
			temp_composite_context->setActionsSynch(simple->getIsPrimaryContext());
			temp_composite_context->setContextType(ParallelContext);
			temp_composite_context->setPredecessor(simple->getPredecessor());
			temp_composite_context->addNextContext(simple);
			temp_composite_context->setIsPrimaryContext(simple->getIsPrimaryContext());
			temp_composite_context->setIsEmotional(true);
			*context = temp_composite_context;
			//The action become principal
			simple->setIsPrimaryContext(true);
			simple->setPredecessor(temp_composite_context);
			std::vector<ActionChanges *> temp_action_changes = emotion_profile->second->getActionChanges();
			for(std::vector<ActionChanges *>::iterator it = temp_action_changes.begin();
					it != temp_action_changes.end(); ++it){
				//if the action is the same that we want just add the emotional parameters
				if((*it)->getActionThatModyfies().compare(simple->getActionName())==0){
					simple->setEmotionChanges((*it));
				}
				//if this action is not the one that we want, we have to instance the class and work on it
				else{
					std::map<std::string,AbstractActionDescription *>::iterator temp_action = available_actions.find((*it)->getActionThatModyfies());
					if(temp_action != available_actions.end()){
						SimpleContextDescription * temp_simple_context = static_cast<SimpleContextDescription *>(temp_action->second->analyze());
						temp_simple_context->setPredecessor(temp_composite_context);
						temp_composite_context->addNextContext(temp_simple_context);
						temp_simple_context->setIsEmotional(true);
						temp_simple_context->setIsPrimaryContext(false);
						temp_simple_context->setEmotionChanges((*it));
					}
				}
			}
		}else{
			//TODO show error message
			std::cout<<"I have a problem with "<<emotion<<" and "<<simple->getActionName()<<std::endl;
		}
	}else if(typeid(**context).name() == typeid(CompositeContextDescription).name()){
		CompositeContextDescription * temp_composite_action = static_cast<CompositeContextDescription *>(*context);
		std::vector<AbstractContextDescription *> * next_context = temp_composite_action->getSubContextPointer();
		for(unsigned int i = 0; i < next_context->size(); ++i){
			this->addEmotionalActions(&(next_context->at(i)),emotion);
		}
	}else{
		//TODO send error message
	}
}

void ActionAddition::loadAvailableAction(){
	SimpleActionDoNothing *action_do_nothing = new SimpleActionDoNothing;
	available_actions[action_do_nothing->getActionName()] = action_do_nothing;
	SimpleActionMoveBody *action_move_body = new SimpleActionMoveBody;
	available_actions[action_move_body->getActionName()] = action_move_body;
	SimpleActionMoveShoulder *action_move_shoulder = new SimpleActionMoveShoulder;
	available_actions[action_move_shoulder->getActionName()] = action_move_shoulder;
	SimpleActionMoveTorso *action_move_torso = new SimpleActionMoveTorso;
	available_actions[action_move_torso->getActionName()] = action_move_torso;
	SimpleActionOscillateBody *action_oscillate_body = new SimpleActionOscillateBody;
	available_actions[action_oscillate_body->getActionName()] = action_oscillate_body;
	SimpleActionOscillateShoulder *action_oscillate_shoulder = new SimpleActionOscillateShoulder;
	available_actions[action_oscillate_shoulder->getActionName()] = action_oscillate_shoulder;
	SimpleActionOscillateTorso *action_oscillate_torso = new SimpleActionOscillateTorso;
	available_actions[action_oscillate_torso->getActionName()] = action_oscillate_torso;
	SimpleActionSpeak *action_speak = new SimpleActionSpeak;
	available_actions[action_speak->getActionName()] = action_speak;
	CompositeActionWalk *action_walk = new CompositeActionWalk;
	available_actions[action_walk->getActionName()] = action_walk;
}
