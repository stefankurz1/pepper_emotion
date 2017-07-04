/*
 * ActionExecution.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 */

#include "ActionExecution.h"


ActionExecution::ActionExecution() {
	this->updating_data = false;
}

ActionExecution::~ActionExecution() {

}

std::vector<std::string> ActionExecution::getListActionsToStop(){
	return this->list_actions_to_stop;
}

void ActionExecution::cleanListActionsToStop(){
	this->list_actions_to_stop.clear();
}

void ActionExecution::clearListNewAction(){
	this->list_new_actions.clear();
	this->list_new_actions_emotional.clear();
}

std::map<std::string,std::string> ActionExecution::generateEmotionalParameterMessage(){
	std::map<std::string,std::string> temp;
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		temp[it->first] = it->second->getEmotionalParameterMessage();
	}
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		temp[it->first] = it->second->getEmotionalParameterMessage();
	}
	return temp;
}

std::map<std::string,std::string> ActionExecution::generateParameterMessage(){
	std::map<std::string,std::string> temp;
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		temp[it->first] = it->second->getActionParameters();
	}
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		temp[it->first] = it->second->getActionParameters();
	}
	return temp;
}

/*
 * This method synchronized all the actions that are synchronized by action
 * 	It looks if the context is parallel, primary and action_synch
 * d	If the action is primary it goes up to the tree
 * a	If the context is parallel and it is actions_synch finish all the actions a it take it out from the queue
 * d	If the context is sequential get the current action from action queue, stop the current action and add the following
 * 	If the context is primary goes up to the tree
 */
void ActionExecution::actionSynchronization(std::string action_name){
	if(!this->updating_data){
		std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.find(action_name);
		if(it != current_actions.end()){
			SimpleContextDescription * simple_action = it->second;
			current_actions.erase(it);
			std::cout<<"Simple action "<<simple_action->getActionName()<<" is primary= "<<simple_action->getIsPrimaryContext()<<std::endl;
			if(simple_action->getIsPrimaryContext() && simple_action->getPredecessor() != 0){
				this->propagateActionSynchronization(simple_action->getPredecessor(), simple_action, false);
			}
		}
	}
}

void ActionExecution::propagateEmotionalActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context,bool has_be_in_predecessor){
	if(typeid(*composite_context).name()==typeid(SimpleContextDescription).name()){
		SimpleContextDescription *temp = static_cast<SimpleContextDescription *>(composite_context);
		std::map<std::string,SimpleContextDescription *>::iterator it;
		//std::cout<<"size "<<current_actions.size()<<" "<<std::endl;
		if(temp->getIsEmotional()){
			it = current_emotional_actions.find(temp->getActionName());
			if(it != current_emotional_actions.end()){
				this->list_actions_to_emotional_synch.push_back(temp->getActionName());
			}
		} else{
			it = current_actions.find(temp->getActionName());
			if(it != current_actions.end()){
				this->list_actions_to_emotional_synch.push_back(temp->getActionName());
			}
		}
	}else if(typeid(*composite_context).name()==typeid(CompositeContextDescription).name()){
		CompositeContextDescription * temp_composite = static_cast<CompositeContextDescription *>(composite_context);
		if(temp_composite->getEmotionalSynch() && temp_composite->getContextType()==ParallelContext){
			std::vector<AbstractContextDescription *> *temp = temp_composite->getSubContextPointer();
			for(std::vector<AbstractContextDescription *>::iterator it = temp->begin(); it != temp->end(); ++it){
				if(*it != last_context)
					this->propagateEmotionalActionSynchronization(*it,temp_composite, true);
			}
		}
		//Verify is the context is sequential, propagate
		else if(temp_composite->getContextType()==SequentialContext){
			//Got the list of actions
			std::vector<AbstractContextDescription *> *temp = temp_composite->getSubContextPointer();
			if(temp_composite->getCountActions()<(static_cast<int>(temp->size()))){
				AbstractContextDescription * context_to_propagate = temp->at(temp_composite->getCountActions());
				if(context_to_propagate != last_context){
					this->propagateEmotionalActionSynchronization(context_to_propagate,temp_composite, true);
				}
			}
		}
		//It goes up to look for more context
		if(temp_composite->getPredecessor()!= 0 && temp_composite->getIsPrimaryContext() && !has_be_in_predecessor){
			this->propagateEmotionalActionSynchronization(temp_composite->getPredecessor(),temp_composite, false);
		}
	}
}


void ActionExecution::propagateActionSynchronization(AbstractContextDescription * composite_context, AbstractContextDescription * last_context, bool has_be_in_predecessor){
	//std::cout<<"Context id "<<composite_context<<" - "<<last_context<<std::endl;
	if(typeid(*composite_context).name()==typeid(SimpleContextDescription).name()){
		SimpleContextDescription *temp = static_cast<SimpleContextDescription *>(composite_context);
		std::map<std::string,SimpleContextDescription *>::iterator it;
		//std::cout<<"Context "<<temp->getActionName()<<" size "<<current_actions.size()<<" "<<std::endl;
		if(temp->getIsEmotional()){
			it = current_emotional_actions.find(temp->getActionName());
			if(it != current_emotional_actions.end()){
				current_emotional_actions.erase(it);
				list_actions_to_stop.push_back(temp->getActionName());
			}
		} else{
			it = current_actions.find(temp->getActionName());
			if(it != current_actions.end()){
				current_actions.erase(it);
				list_actions_to_stop.push_back(temp->getActionName());
			}
		}
		//std::cout<<"size- "<<current_actions.size()<<std::endl;
	}else if(typeid(*composite_context).name()==typeid(CompositeContextDescription).name()){
		CompositeContextDescription * temp_composite = static_cast<CompositeContextDescription *>(composite_context);
		//If the context is parallel and it is actions_synch finish all the actions a it take it out from the queue
		if(temp_composite->getContextType()==ParallelContext){
			//std::cout<<"Synch parallel "<<std::endl;
			std::vector<AbstractContextDescription *> *temp = temp_composite->getSubContextPointer();
			for(std::vector<AbstractContextDescription *>::iterator it = temp->begin(); it != temp->end(); ++it){
				if(*it != last_context){
					this->propagateActionSynchronization(*it,temp_composite, true);
				}
			}
		}else if(temp_composite->getContextType()==SequentialContext){
			std::cout<<"Synch sequential "<<std::endl;
			std::vector<AbstractContextDescription *> *temp = temp_composite->getSubContextPointer();
			temp_composite->addCountActions();
			if(temp_composite->getCountActions()<(static_cast<int>(temp->size()))){
				this->changeInAction(temp->at(temp_composite->getCountActions()));
			}
		}
		if(temp_composite->getPredecessor()!= 0 && temp_composite->getIsPrimaryContext() && !has_be_in_predecessor){
			std::cout<<"Getting predecessor"<<std::endl;
			this->propagateActionSynchronization(temp_composite->getPredecessor(),temp_composite, false);
		}
	}
}


std::vector<std::string> ActionExecution::getListEmotionalActionToSynch(){
	return this->list_actions_to_emotional_synch;
}
void ActionExecution::cleanListEmotionalActionToSynch(){
	this->list_actions_to_emotional_synch.clear();
}

/*
 * This method synchronized all the actions that are synchronized by the emotions
 * If the action is primary it goes up
 * If the context is primary it goes up
 * If the context is parallel and emotion_synch it sends message to the other actions
 */
void ActionExecution::emotionSynchronization(std::string action_name){
	if(!this->updating_data){
		std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.find(action_name);
		if(it != current_actions.end()){
			SimpleContextDescription * simple_action = it->second;
			if(simple_action->getIsPrimaryContext()){
				this->propagateEmotionalActionSynchronization(simple_action->getPredecessor(),simple_action, false);
			}
		}
	}
}

void ActionExecution::sendEmotionalMessages(){
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		//TODO send messages to the emotional actions
	}

}

void ActionExecution::sendActionMessages(){
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		//TODO send messages to the actions
	}

}
/*
 * Stop the emotional actions that are in
 */
void ActionExecution::changeInEmotion(AbstractContextDescription * context){
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		if(it->second->getIsPrimaryContext()){
			//Get the context if context is emotional get
			AbstractContextDescription * temp = it->second->getPredecessor();
			if(temp != 0 && temp->getIsEmotional()){
				CompositeContextDescription * t_context = static_cast<CompositeContextDescription *>(temp);
				std::vector<AbstractContextDescription *> *t = t_context->getSubContextPointer();
				for(std::vector<AbstractContextDescription *>::iterator it = t->begin();
						it != t->end(); ++it){
					if((*it)->getIsEmotional()){
						SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(*it);
						addEmotionalAction(temp_context);
					}
				}
			}
		}
		//std::cout<<"Action: "<< it->second->getActionName()<<" - ";
	}
	//std::cout<<std::endl;
	//Send emotional parameters only
}

/*
 * It stops the emotional actions
 */
void ActionExecution::stopEmotionalActions(){
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		list_actions_to_stop.push_back(it->first);
	}
	this->current_emotional_actions.clear();
}

/*
 * Send the new messages of all the actions
 */
void ActionExecution::changeInIntensity(AbstractContextDescription * context){
	//Send emotional parameters only!
}

void ActionExecution::changeInAction(AbstractContextDescription * context){
	std::cout<<"Changing action"<<std::endl;
		if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
			//std::cout<<"Simple"<<std::endl;
			SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(context);
			std::map<std::string,SimpleContextDescription *>::iterator iterator_actions = current_actions.find(temp_context->getActionName());
			//std::cout<<"The context "<<temp_context->getActionName()<<" is primary "<<temp_context->getIsPrimaryContext()<<std::endl;
			if(iterator_actions== current_actions.end() && !temp_context->getIsEmotional()){
				current_actions[temp_context->getActionName()] = temp_context;
				list_new_actions[temp_context->getActionName()] = temp_context->getActionParameters();
				list_new_actions_emotional[temp_context->getActionName()] = temp_context->getEmotionalParameterMessage();
			}else if(temp_context->getIsEmotional()){
				addEmotionalAction(temp_context);
			}else{
				//TODO send error the action is already in execution
			}
		}else if(typeid(*context).name()==typeid(CompositeContextDescription).name()){
			//std::cout<<"Composite"<<std::endl;
			CompositeContextDescription * temp_context = static_cast<CompositeContextDescription *>(context);
			std::vector<AbstractContextDescription*> * sucessor = temp_context->getSubContextPointer();
			if(temp_context->getContextType()==ParallelContext){
				//Look in all the sons
				for(std::vector<AbstractContextDescription*>::iterator it = sucessor->begin(); it != sucessor->end(); ++it){
					this->changeInAction(*it);
				}
			}else if(temp_context->getContextType()==SequentialContext && sucessor->size()!=0){
				//Look in the first one
				this->changeInAction(sucessor->at(0));
			}
		}
}

void ActionExecution::stopAction(){
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		list_actions_to_stop.push_back(it->first);
	}
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		list_actions_to_stop.push_back(it->first);
	}
	this->deleteActionsQueue();

}


std::map<std::string,std::string> ActionExecution::getListNewAction(){
	return this->list_new_actions;
}

std::map<std::string,std::string> ActionExecution::getListNewActionEmotional(){
	return this->list_new_actions_emotional;
}
void ActionExecution::addEmotionalAction(SimpleContextDescription * temp_context){
	std::map<std::string,SimpleContextDescription *>::iterator iterator_actions = current_actions.find(temp_context->getActionName());
	std::map<std::string,SimpleContextDescription *>::iterator iterator_emotional_actions = current_emotional_actions.find(temp_context->getActionName());
	if((iterator_actions == current_actions.end())&&(iterator_emotional_actions == current_emotional_actions.end())){
		current_emotional_actions[temp_context->getActionName()] = temp_context;
		list_new_actions[temp_context->getActionName()] = temp_context->getActionParameters();
		list_new_actions_emotional[temp_context->getActionName()] = temp_context->getEmotionalParameterMessage();
	}else{
		//TODO send error the emotional actions is already in execution
	}
}

//this cleans the emotions and current action queue
void ActionExecution::deleteActionsQueue(){
	//TODO send message to stop to the whole actions that are current in execution
	this->current_actions.clear();
	this->current_emotional_actions.clear();
}

void ActionExecution::printQueue(){
	std::cout<<"Emotional Actions"<<std::endl;
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_emotional_actions.begin();
			it != current_emotional_actions.end(); ++it){
		std::cout<<"Action: "<< it->second->getActionName()<<" - ";
	}
	std::cout<<std::endl;
	std::cout<<"Mandatory Actions"<<std::endl;
	for(std::map<std::string,SimpleContextDescription *>::iterator it = current_actions.begin();
			it != current_actions.end(); ++it){
		std::cout<<"Action: "<< it->second->getActionName()<<" - ";
	}
	std::cout<<std::endl;
}

void ActionExecution::lock(){
	updating_data = true;
}

void ActionExecution::unlock(){
	updating_data = false;
}

