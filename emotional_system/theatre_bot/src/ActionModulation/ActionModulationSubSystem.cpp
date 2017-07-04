/*
 * ActionModulationSubSystem.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 */

#include "ActionModulationSubSystem.h"

ActionModulationSubSystem::ActionModulationSubSystem() {
	this->last_intensity = 0;
	this->last_emotion = "neutral";
	this->context = 0;
}

ActionModulationSubSystem::~ActionModulationSubSystem() {
	if(context != 0){
		delete context;
	}
}

void ActionModulationSubSystem::clearListNewAction(){
	this->action_execution.clearListNewAction();
}

std::map<std::string,std::string> ActionModulationSubSystem::getListNewAction(){
	return this->action_execution.getListNewAction();
}

std::map<std::string,std::string> ActionModulationSubSystem::getListNewActionEmotional(){
	return this->action_execution.getListNewActionEmotional();
}
/*
 * Returns the list of actions that should send the stop command

 */
std::vector<std::string> ActionModulationSubSystem::actionSynchronization(std::string action_name){
	//std::cout<<"Ready to synch actions"<<std::endl;
	//action_execution.printQueue();
	this->action_execution.actionSynchronization(action_name);
	std::vector<std::string> list = this->action_execution.getListActionsToStop();
	this->action_execution.cleanListActionsToStop();
	action_execution.printQueue();
	return list;
}


std::vector<std::string> ActionModulationSubSystem::getEmotions(){
	return this->action_addition.getEmotions();
}


std::vector<std::string> ActionModulationSubSystem::getActions(){
	return this->action_addition.getActions();
}

std::vector<std::string> ActionModulationSubSystem::actiosToStop(){
	std::vector<std::string> list = this->action_execution.getListActionsToStop();
	this->action_execution.cleanListActionsToStop();
	return list;
}

std::vector<std::string> ActionModulationSubSystem::emotionSynchronization(std::string action_name){
	this->action_execution.emotionSynchronization(action_name);
	//Get list of actions to update emotion
	std::vector<std::string> list = this->action_execution.getListEmotionalActionToSynch();
	this->action_execution.cleanListEmotionalActionToSynch();
	action_execution.printQueue();
	return list;
}

std::map<std::string,std::string> ActionModulationSubSystem::generateParameterMessage(){
	return this->action_execution.generateParameterMessage();
}
std::map<std::string,std::string> ActionModulationSubSystem::generateEmotionalParameterMessage(){
	return this->action_execution.generateEmotionalParameterMessage();
}

void ActionModulationSubSystem::callBackNewEmotion(std::string emotion, float intensity){
	//If the emotion is different of neutral or intensity different of 0 should changed the execution
	//this->printContext(this->context);
	if(context != 0){
		action_execution.lock();
		/*if(emotion.compare("neutral")==0 || intensity == 0){
			//Delete the emotional part
			last_emotion = emotion;
			last_intensity = intensity;
			action_addition.changeEmotionalAction(&context,"neutral");
			action_execution.changeInEmotion(this->context);
		}else{*/
			if(emotion.compare(last_emotion) !=0 ){
				action_execution.stopEmotionalActions();
				//change emotion
				action_addition.changeEmotionalAction(&context,emotion);
				last_emotion= emotion;
				//change intensity
				action_modulation.actionModulation(context,emotion,intensity);
				last_intensity = intensity;
				/*
				 * Update emotional information
				 * 	Delete the current emotional actions
				 * 	Add the new emotional actions
				 */
				action_execution.changeInEmotion(this->context);
			}else if(intensity != last_intensity){
				//change intensity
				action_modulation.actionModulation(context,emotion,intensity);
				last_intensity = intensity;
				/*
				 * Update intensity information
				 * 	Run over the current emotional actions and send the new parameters
				 */
				action_execution.changeInIntensity(this->context);
			}
			if(intensity == 0){
				last_emotion = "neutral";
			}
		//}
		action_execution.printQueue();
		action_execution.unlock();
	} else{
		last_emotion = emotion;
		last_intensity = intensity;
	}
	//this->printContext(this->context);
}

void ActionModulationSubSystem::callBackNewAction(std::string action_message){
	//If the action is different
	if(action_message.compare("stop")==0){
		action_execution.lock();
		last_action = "stop";
		//Stop current execution
		if(context != 0){
			action_execution.stopAction();
			delete context;
			context = 0;
		}
		action_execution.unlock();
	}
	else if(action_message.compare(last_action) != 0){
		action_execution.lock();
		AbstractContextDescription *context_temp = action_addition.addAdditionalActions(action_message,last_emotion);
		if(context_temp != 0){
			//Stop current execution
			if(context != 0){
				action_execution.stopAction();
				delete context;
				context = 0;
			}
			context = context_temp;
			action_modulation.actionModulation(context,last_emotion,last_intensity);
			last_action = action_message;
			action_execution.changeInAction(this->context);
		}
		action_execution.printQueue();
		action_execution.unlock();
	}
	this->printContext(this->context);
}


void ActionModulationSubSystem::setPathCharacterPace(std::string character_pace){
	this->charater_pace_path = character_pace;
	this->action_modulation.setPathCharacterModifications(this->charater_pace_path);
}

void ActionModulationSubSystem::loadInformation(){
	if(!this->emotion_path.empty())
		action_addition.loadEmotions();
	if(!this->charater_pace_path.empty()){
		action_modulation.loadCharacterModification();
	}
}

void ActionModulationSubSystem::setPathEmotion(std::string emotion_path){
	this->emotion_path = emotion_path;
	action_addition.setPathName(this->emotion_path);
}

void ActionModulationSubSystem::printContext(AbstractContextDescription *context, std::string tab){
	tab += "*";
	if(context!=0){
		//std::cout<<"context name: "<<typeid(*context).name()<<std::endl;
		if(typeid(*context).name()==typeid(CompositeContextDescription).name()){
			CompositeContextDescription * temp_context = static_cast<CompositeContextDescription *>(context);
			std::cout<<tab<<std::endl;
			std::cout<<tab<<" Context-action synch: "<<temp_context->getActionsSynch()<<", type: "<<temp_context->getContextType()
					<<", emotion synch:"<<temp_context->getEmotionalSynch()<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::cout<<tab<<temp_context<<"-"<<temp_context->getPredecessor()<<std::endl;
			std::vector<AbstractContextDescription *> temp_sub_context = temp_context->getSubContext();
			std::cout<<tab<<"<<<<<<<<<<<<<<"<<std::endl;
			for(std::vector<AbstractContextDescription *>::iterator it = temp_sub_context.begin();
					it != temp_sub_context.end(); ++it){
					printContext(*it,tab);
				std::cout<<tab<<">>>>>>>>>>>>>"<<std::endl;
			}
			std::cout<<tab<<std::endl;
		}else if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
			SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(context);
			std::cout<<tab<<" Action - name: "<<temp_context->getActionName()<<", emotional "<<temp_context->getIsEmotional()<<", parameters: "<<temp_context->getActionParameters()
					<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::cout<<tab<<temp_context<<"-"<<temp_context->getPredecessor()<<std::endl;
			std::cout<<tab<<" Emotion message "<<temp_context->getEmotionalParameterMessage()<<std::endl;
			ActionChanges temp_changes = temp_context->getEmotionChanges();
			std::vector<EmotionParameter *> temp_pameter_emotion = temp_changes.getVectorParameters();
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				EmotionMovementParameter *temp_movement = static_cast<EmotionMovementParameter *>((*it_emotion));
				std::cout<<tab<<" Parameter timing "<<temp_movement->getEmotionParameterTime()<<" parameter spacing "<<temp_movement->getEmotionParameterSpacing()<<std::endl;
			}
		}
	}

}
void ActionModulationSubSystem::printContext(AbstractContextDescription *context){
	if(context!=0){
		//std::cout<<"context name: "<<typeid(*context).name()<<std::endl;
		if(typeid(*context).name()==typeid(CompositeContextDescription).name()){
			CompositeContextDescription * temp_context = static_cast<CompositeContextDescription *>(context);
			std::cout<<"*"<<std::endl;
			std::cout<<"* Context-action synch: "<<temp_context->getActionsSynch()<<", type: "<<temp_context->getContextType()
					<<", emotion synch:"<<temp_context->getEmotionalSynch()<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::cout<<temp_context<<"-"<<temp_context->getPredecessor()<<std::endl;
			std::vector<AbstractContextDescription *> temp_sub_context = temp_context->getSubContext();
			std::cout<<"*---------------"<<std::endl;
			for(std::vector<AbstractContextDescription *>::iterator it = temp_sub_context.begin();
					it != temp_sub_context.end(); ++it){
					printContext(*it,"*");
				std::cout<<"*---------------"<<std::endl;
			}
			std::cout<<"*"<<std::endl;
		}else if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
			SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(context);
			std::cout<<"Action - name: "<<temp_context->getActionName()<<", emotional "<<temp_context->getIsEmotional()<<", parameters: "<<temp_context->getActionParameters()
					<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::cout<<"Emotion message "<<temp_context->getEmotionalParameterMessage()<<std::endl;
			ActionChanges temp_changes = temp_context->getEmotionChanges();
			std::vector<EmotionParameter *> temp_pameter_emotion = temp_changes.getVectorParameters();
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				EmotionMovementParameter *temp_movement = static_cast<EmotionMovementParameter *>((*it_emotion));
				std::cout<<"Parameter timing "<<temp_movement->getEmotionParameterTime()<<" parameter spacing "<<temp_movement->getEmotionParameterSpacing()<<std::endl;
			}
		}
	}
}
