/*
 * ActionChanges.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#include "ActionChanges.h"

ActionChanges::ActionChanges() {
	this->repeat = false;
	this->reference = 0.0;
}

ActionChanges::~ActionChanges() {
	for(std::vector<EmotionParameter *>::iterator it = action_emotion_parameters.begin();
			it != action_emotion_parameters.end(); ++it){
		delete *it;
	}
	for(std::vector<EmotionParameter *>::iterator it = action_emotion_parameters_y.begin();
			it != action_emotion_parameters_y.end(); ++it){
		delete *it;
	}
	for(std::vector<EmotionParameter *>::iterator it = action_emotion_parameters_z.begin();
			it != action_emotion_parameters_z.end(); ++it){
		delete *it;
	}
}


void ActionChanges::setReference(float reference){
	this->reference = reference;
}

void ActionChanges::setRepetition(bool repeat){
	this->repeat = repeat;
}

float ActionChanges::getReference(){
	return this->reference;
}

bool ActionChanges::getRepetition(){
	return this->repeat;
}

string ActionChanges::getActionThatModyfies(){
	return action_that_changes;
}

void ActionChanges::setActionThatModyfies(string action_name){
	this->action_that_changes = action_name;
}

void ActionChanges::addEmotionParameter(EmotionParameter *parameter){
	this->action_emotion_parameters.push_back(parameter);
}

void ActionChanges::addEmotionParameterY(EmotionParameter *parameter){
	this->action_emotion_parameters_y.push_back(parameter);
}

void ActionChanges::addEmotionParameterZ(EmotionParameter *parameter){
	this->action_emotion_parameters_z.push_back(parameter);
}

void ActionChanges::clearVectorsParameters(){
	this->action_emotion_parameters.clear();
	this->action_emotion_parameters_y.clear();
	this->action_emotion_parameters_z.clear();
}

void ActionChanges::clearVectorParameters(){
	this->action_emotion_parameters.clear();
}

void ActionChanges::clearVectorParametersY(){
	this->action_emotion_parameters_y.clear();
}

void ActionChanges::clearVectorParametersZ(){
	this->action_emotion_parameters_z.clear();
}

vector<EmotionParameter *> ActionChanges::getVectorParameters(){
	return action_emotion_parameters;
}

vector<EmotionParameter *> ActionChanges::getVectorParametersY(){
	return action_emotion_parameters_y;
}

vector<EmotionParameter *> ActionChanges::getVectorParametersZ(){
	return action_emotion_parameters_z;
}

void ActionChanges::setVectorParameters(vector<EmotionParameter *> parameters){
	this->action_emotion_parameters = parameters;
}

void ActionChanges::setVectorParametersY(vector<EmotionParameter *> parameters){
	this->action_emotion_parameters_y = parameters;
}

void ActionChanges::setVectorParametersZ(vector<EmotionParameter *> parameters){
	this->action_emotion_parameters_z = parameters;
}

vector<EmotionParameter *> ActionChanges::copyVectorParameters(){
	vector<EmotionParameter *> temp;
	for(vector<EmotionParameter *>::iterator it = action_emotion_parameters.begin(); it != action_emotion_parameters.end(); it++){
			temp.push_back((*it)->copyEmotionParameter());
		}
	return temp;
}

vector<EmotionParameter *> ActionChanges::copyVectorParametersY(){
	vector<EmotionParameter *> temp;
	for(vector<EmotionParameter *>::iterator it = action_emotion_parameters_y.begin(); it != action_emotion_parameters_y.end(); it++){
			temp.push_back((*it)->copyEmotionParameter());
		}
	return temp;
}

vector<EmotionParameter *> ActionChanges::copyVectorParametersZ(){
	vector<EmotionParameter *> temp;
	for(vector<EmotionParameter *>::iterator it = action_emotion_parameters_z.begin(); it != action_emotion_parameters_z.end(); it++){
			temp.push_back((*it)->copyEmotionParameter());
		}
	return temp;
}
