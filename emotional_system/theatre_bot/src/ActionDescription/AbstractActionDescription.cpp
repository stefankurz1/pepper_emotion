///////////////////////////////////////////////////////////
//  AbstractActionDescription.cpp
//  Implementation of the Class AbstractActionDescription
//  Created on:      04-dic-2014 04:40:56 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "AbstractActionDescription.h"


AbstractActionDescription::AbstractActionDescription(){
	this->is_primary = false;
}

AbstractActionDescription::~AbstractActionDescription(){

}

std::string AbstractActionDescription::getActionName(){
	return action_name;
}

void AbstractActionDescription::setIsPrimary(bool is_primary){
	this->is_primary = is_primary;
}

bool AbstractActionDescription::ParametersVerification(Json::Value parameters){
	if(!parameters.isNull()){
		Json::Value parameter, type_parameter;
		std::string temp_info;
		bool result = true;
		//Gets all the parameters that are in the action
		for(unsigned int i=0; i<parameters.size();i++){
			parameter = parameters.get(i,"UTF-8");
			if(!parameter.isNull()&&parameter.isObject()){
				temp_info = parameter.get("type","UTF-8").asString();
				if(temp_info.compare("mandatory_parameter")==0){
					result = result & this->MandatoryParameterVerification(parameter);
				} else if(temp_info.compare("optional_parameter")==0){
					result = result & this->OptionalParameterVerification(parameter);
				} else{
					return false;
				}
			}
		}
		return result;
	}
	return false;
}

