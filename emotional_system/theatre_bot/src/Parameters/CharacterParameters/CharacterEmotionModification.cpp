/*
 * CharacterEmotionModification.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: julian
 */

#include "CharacterEmotionModification.h"

CharacterEmotionModification::CharacterEmotionModification() {
	// TODO Auto-generated constructor stub

}

CharacterEmotionModification::~CharacterEmotionModification() {
	for(std::map<std::string,CharacterMovementModification *>::iterator it = character_emotion_modification.begin();
			it != character_emotion_modification.end(); ++it){
		delete it->second;
	}
}

std::map<std::string,CharacterMovementModification *> * CharacterEmotionModification::getEmotionModification(){
	return &this->character_emotion_modification;
}

void CharacterEmotionModification::setEmotionModification(std::vector<CharacterMovementModification *> character_emotion_modification){
	for(std::vector<CharacterMovementModification *>::iterator it = character_emotion_modification.begin();
			it != character_emotion_modification.end(); ++it){
		this->character_emotion_modification[(*it)->getActionName()]=*it;
	}
}

std::string CharacterEmotionModification::getEmotionName(){
	return this->emotion_name;
}

void CharacterEmotionModification::setEmotionName(std::string emotion_name){
	this->emotion_name = emotion_name;
}

void CharacterEmotionModification::addParameter(CharacterMovementModification * action_parameter){
	this->character_emotion_modification[action_parameter->getActionName()] = action_parameter;
}

void CharacterEmotionModification::cleanParameters(){
	for(std::map<std::string, CharacterMovementModification *>::iterator it = character_emotion_modification.begin();
			it != character_emotion_modification.end(); ++it){
		delete it->second;
	}
}
