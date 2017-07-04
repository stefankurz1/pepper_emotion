///////////////////////////////////////////////////////////
//  CompositeActionDescription.cpp
//  Implementation of the Class CompositeActionDescription
//  Created on:      04-dic-2014 04:40:56 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "CompositeActionDescription.h"


CompositeActionDescription::CompositeActionDescription(){
	this->emotion_synch = false;
	this->actions_synch = false;
	this->context_type = UnknownContext;
}


CompositeActionDescription::~CompositeActionDescription(){
}


AbstractContextDescription * CompositeActionDescription::analyze(){
	CompositeContextDescription * temp_context = new CompositeContextDescription;
	AbstractContextDescription *temp_simple_context;
	temp_context->setActionsSynch(this->actions_synch);
	temp_context->setEmotionalSynch(this->emotion_synch);
	temp_context->setContextType(this->context_type);
	temp_context->setIsPrimaryContext(this->is_primary);
	for(std::map<std::string,AbstractActionDescription *>::iterator it = actions.begin();
			it != actions.end(); ++it){
		temp_simple_context = it->second->analyze();
		temp_simple_context->setPredecessor(temp_context);
		temp_context->addNextContext(temp_simple_context);
	}
	return temp_context;
}

void CompositeActionDescription::setEmotionSynch(bool emotion_synch){
	this->emotion_synch = emotion_synch;
}
bool CompositeActionDescription::getEmotionSynch(){
	return this->emotion_synch;
}
void CompositeActionDescription::setActionsSynch(bool actions_synch){
	this->actions_synch = actions_synch;
}
bool CompositeActionDescription::getActionsSynch(){
	return this->actions_synch;
}
