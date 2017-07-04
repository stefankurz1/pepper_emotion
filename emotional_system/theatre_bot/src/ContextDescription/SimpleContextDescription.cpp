///////////////////////////////////////////////////////////
//  SimpleContextDescription.cpp
//  Implementation of the Class SimpleContextDescription
//  Created on:      04-dic-2014 04:41:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "SimpleContextDescription.h"


SimpleContextDescription::SimpleContextDescription(){
	is_emotional = false;
}

SimpleContextDescription::~SimpleContextDescription(){
}

void SimpleContextDescription::setActionName(std::string action_name){
	this->action_name = action_name;
}
void SimpleContextDescription::setActionParameters(std::string action_parameters){
	this->action_parameters = action_parameters;
}

void SimpleContextDescription::setEmotionChanges(ActionChanges * emotion_changes){
	this->cleanEmotionParameters();
	this->emotion_changes.setReference(emotion_changes->getReference());
	this->emotion_changes.setRepetition(emotion_changes->getRepetition());
	this->emotion_changes.setActionThatModyfies(emotion_changes->getActionThatModyfies()) ;
	this->emotion_changes.setVectorParameters(emotion_changes->copyVectorParameters());
	this->emotion_changes.setVectorParametersY(emotion_changes->copyVectorParametersY());
	this->emotion_changes.setVectorParametersZ(emotion_changes->copyVectorParametersZ());
}

void SimpleContextDescription::cleanEmotionParameters(){
	std::vector<EmotionParameter *> emotion_parameters = emotion_changes.getVectorParameters();
	for(std::vector<EmotionParameter *>::iterator it = emotion_parameters.begin();
			it != emotion_parameters.end(); ++it){
		delete *it;
	}
	emotion_parameters = emotion_changes.getVectorParametersY();
	for(std::vector<EmotionParameter *>::iterator it = emotion_parameters.begin();
			it != emotion_parameters.end(); ++it){
		delete *it;
	}
	emotion_parameters = emotion_changes.getVectorParametersZ();
	for(std::vector<EmotionParameter *>::iterator it = emotion_parameters.begin();
			it != emotion_parameters.end(); ++it){
		delete *it;
	}
	emotion_changes.clearVectorsParameters();
}

std::string SimpleContextDescription::getActionName(){
	return this->action_name;
}
std::string SimpleContextDescription::getActionParameters(){
	return this->action_parameters;
}


ActionChanges SimpleContextDescription::getEmotionChanges(){
	ActionChanges temp = this->emotion_changes;
	temp.setVectorParameters(this->emotion_changes.copyVectorParameters());
	temp.setVectorParametersY(this->emotion_changes.copyVectorParametersY());
	temp.setVectorParametersZ(this->emotion_changes.copyVectorParametersZ());
	return temp;
}

std::string SimpleContextDescription::getEmotionalParameterMessage(){
	return this->emotion_modify_parameters;
}

void SimpleContextDescription::setEmotionalParameterMessage(std::string emotion_message){
	this->emotion_modify_parameters = emotion_message;
}
