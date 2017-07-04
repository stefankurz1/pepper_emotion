/*
 * EmotionProfile.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: julian
 */

#include "EmotionProfile.h"

EmotionProfile::EmotionProfile() {
	this->emotion_type = UnknownEmotionType;

}

EmotionProfile::~EmotionProfile() {
	for(vector<ActionChanges *>::iterator it = emotion_profile_actions.begin(); it != emotion_profile_actions.end(); it++){
		delete *it;
	}
}


vector<ActionChanges *> EmotionProfile::getActionChanges(){
	return emotion_profile_actions;
}

void EmotionProfile::setTypeActionEmotion(EmotionType type_action_emotion){
	this->emotion_type = type_action_emotion;
}

void EmotionProfile::addActionChanges(ActionChanges * action){
	this->emotion_profile_actions.push_back(action);
}

string EmotionProfile::getEmotionProfileName(){

	return  this->emotion_profile_name;
}


void EmotionProfile::setEmotionProfileName(string emotion_profile_name){

	this->emotion_profile_name = emotion_profile_name;
}


string EmotionProfile::getEmotionProfileAction(){

	return  this->emotion_profile_action;
}


void EmotionProfile::setEmotionProfileAction(string emotion_profile_action){

	this->emotion_profile_action = emotion_profile_action;
}


string EmotionProfile::getEmotionProfileDescription(){

	return  this->emotion_profile_description;
}

string EmotionProfile::getEmotionProfileEmotion(){
	return this->emotion_profile_emotion;
}

void EmotionProfile::setEmotionProfileEmotion(string emotion_profile_emotion){
	this->emotion_profile_emotion = emotion_profile_emotion;
}


void EmotionProfile::setEmotionProfileDescription(string emotion_profile_description){

	this->emotion_profile_description = emotion_profile_description;
}


EmotionType EmotionProfile::getTypeActionEmotion(){
	return this->emotion_type;
}
