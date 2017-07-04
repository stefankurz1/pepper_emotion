/*
 * SimpleActionMoveBody.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: julian
 */

#include "SimpleActionMoveBody.h"

SimpleActionMoveBody::SimpleActionMoveBody() {
	this->action_name = "move_body";
}

SimpleActionMoveBody::~SimpleActionMoveBody() {
	// TODO Auto-generated destructor stub
}

bool SimpleActionMoveBody::MandatoryParameterVerification(Json::Value parameter){
	if(!parameter.isNull()){
			std::string parameter_name = parameter.get("name","UTF-8").asString();
			if(parameter_name.compare("parameter_circle")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				Json::FastWriter writer;
				this->parameter_message += writer.write(parameter);
				return true;
			}
			if(parameter_name.compare("parameter_landmark")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				Json::FastWriter writer;
				this->parameter_message += writer.write(parameter);
				return true;
			}
			if(parameter_name.compare("parameter_point")==0){
				if(!this->parameter_message.empty()){
					this->parameter_message +=",";
				}
				Json::FastWriter writer;
				this->parameter_message += writer.write(parameter);
				return true;
			}
			if(parameter_name.compare("parameter_square")==0){
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

bool SimpleActionMoveBody::OptionalParameterVerification(Json::Value parameter){
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
