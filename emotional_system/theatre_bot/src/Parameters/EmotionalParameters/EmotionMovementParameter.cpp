/*
 * EmotionMovementParameter.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#include "EmotionMovementParameter.h"

EmotionMovementParameter::EmotionMovementParameter() {
	spacing = 0.0;
	timing = 0.0;

}

EmotionMovementParameter::~EmotionMovementParameter() {
}

float EmotionMovementParameter::getEmotionParameterTime(){
	return this->timing;
}
void EmotionMovementParameter::setEmotionParameterTime(float emotion_parameter_time){
	this->timing = emotion_parameter_time;
}

float EmotionMovementParameter::getEmotionParameterSpacing(){
	return this->spacing;
}

void EmotionMovementParameter::setEmotionParameterSpacing(float emotion_parameter_spacing){
	this->spacing = emotion_parameter_spacing;
}

EmotionParameter *EmotionMovementParameter::copyEmotionParameter(){
	EmotionMovementParameter * temp = new EmotionMovementParameter;
	temp->setEmotionParameterSpacing(this->spacing);
	temp->setEmotionParameterTime(this->timing);
	return temp;
}

std::string EmotionMovementParameter::generateMessage(){
	Json::Value root;
	Json::FastWriter writer;
	root["space"] = this->spacing;
	//mm/s
	root["velocity"] = this->timing;
	return writer.write(root);
}
