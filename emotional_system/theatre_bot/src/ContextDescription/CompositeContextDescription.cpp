///////////////////////////////////////////////////////////
//  CompositeContextDescription.cpp
//  Implementation of the Class CompositeContextDescription
//  Created on:      04-dic-2014 04:41:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////


#include "CompositeContextDescription.h"


CompositeContextDescription::CompositeContextDescription(){
	context_type = UnknownContext;
	emotional_synch = false;
	actions_synch = false;
	current_action = 0;
}



CompositeContextDescription::~CompositeContextDescription(){
	for(std::vector<AbstractContextDescription *>::iterator it = context_list.begin();
			it != context_list.end(); ++it){
		delete *it;
	}
}


vector<AbstractContextDescription*> CompositeContextDescription::getSubContext(){
	return context_list;
}

vector<AbstractContextDescription*> * CompositeContextDescription::getSubContextPointer(){
	return &context_list;
}

int CompositeContextDescription::getNumberOfContext(){
	return context_list.size();
}

void CompositeContextDescription::setContextType(ContextType context_type){
	this->context_type = context_type;
}

ContextType CompositeContextDescription::getContextType(){
	return this->context_type;
}

void CompositeContextDescription::setEmotionalSynch(bool emotional_synch){
	this->emotional_synch = emotional_synch;
}

bool CompositeContextDescription::getEmotionalSynch(){
	return emotional_synch;
}

void CompositeContextDescription::setActionsSynch(bool actions_synch){
	this->actions_synch = actions_synch;
}

bool CompositeContextDescription::getActionsSynch(){
	return actions_synch;
}

void CompositeContextDescription::addNextContext(AbstractContextDescription * new_context){
	if(new_context != 0){
		context_list.push_back(new_context);
	}
}


int CompositeContextDescription::getCountActions(){
	return this->current_action;
}
void CompositeContextDescription::addCountActions(){
	this->current_action += 1;
}
