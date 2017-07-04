///////////////////////////////////////////////////////////
//  SimpleActionDescription.cpp
//  Implementation of the Class SimpleActionDescription
//  Created on:      04-dic-2014 04:40:57 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "SimpleActionDescription.h"


SimpleActionDescription::SimpleActionDescription(){
	is_primary = false;
}



SimpleActionDescription::~SimpleActionDescription(){

}

AbstractContextDescription * SimpleActionDescription::analyze(){
	SimpleContextDescription *temp_simple_context = new SimpleContextDescription;
	temp_simple_context->setActionName(this->action_name);
	temp_simple_context->setActionParameters(this->parameter_message);
	temp_simple_context->setIsPrimaryContext(this->is_primary);
	this->parameter_message.clear();
	return temp_simple_context;
}

bool SimpleActionDescription::ParametersVerification(Json::Value parameter, std::string name_parameter, std::string type_parameter){
	bool valid_parameter = false;
	if(type_parameter.compare("mandatory")==0){
		valid_parameter = this->MandatoryParameterVerification(parameter);
	}else if(type_parameter.compare("optional")==0){
		valid_parameter = this->OptionalParameterVerification(parameter);
	}
	return valid_parameter;
}

bool SimpleActionDescription::getIsPrimary(){
	return this->is_primary;
}
