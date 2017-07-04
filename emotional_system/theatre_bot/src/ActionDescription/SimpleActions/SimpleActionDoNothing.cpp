/*
 * SimpleActionDoNothing.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: julian
 */

#include "SimpleActionDoNothing.h"

SimpleActionDoNothing::SimpleActionDoNothing() {
	this->action_name = "do_nothing";

}

SimpleActionDoNothing::~SimpleActionDoNothing() {
	// TODO Auto-generated destructor stub
}

bool SimpleActionDoNothing::MandatoryParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_time")==0){
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

bool SimpleActionDoNothing::OptionalParameterVerification(Json::Value parameter){
	return false;
}

