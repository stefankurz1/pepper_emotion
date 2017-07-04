/*
 * SimpleActionSpeak.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#include "SimpleActionSpeak.h"

SimpleActionSpeak::SimpleActionSpeak() {
	this->action_name = "speak";
}

SimpleActionSpeak::~SimpleActionSpeak() {
	// TODO Auto-generated destructor stub
}

bool SimpleActionSpeak::MandatoryParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_speech")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				Json::FastWriter writer;
				this->parameter_message += writer.write(parameter);
				return true;
			}
	}
	return false;
}

bool SimpleActionSpeak::OptionalParameterVerification(Json::Value parameter){
	return false;
}
