/*
 * SimpleActionOscillateTorso.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#include "SimpleActionOscillateTorso.h"

SimpleActionOscillateTorso::SimpleActionOscillateTorso() {
	this->action_name ="oscillate_torso";
}

SimpleActionOscillateTorso::~SimpleActionOscillateTorso() {
	// TODO Auto-generated destructor stub
}

bool SimpleActionOscillateTorso::MandatoryParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_amplitude")==0){
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

bool SimpleActionOscillateTorso::OptionalParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_time")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				this->parameter_message += "time";
				return true;
			}
			if(parameter_name.compare("parameter_velocity")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				this->parameter_message += "velocity";
				return true;
			}
	}
	return false;
}
