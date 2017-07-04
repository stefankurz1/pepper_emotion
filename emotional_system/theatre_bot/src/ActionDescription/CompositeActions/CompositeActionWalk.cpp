/*
 * CompositeActionWalk.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#include "CompositeActionWalk.h"

CompositeActionWalk::CompositeActionWalk() {
	//We add the actions that composite this actions
	SimpleActionMoveBody * temp_action_move_body = new SimpleActionMoveBody;
	temp_action_move_body->setIsPrimary(true);
	actions["body"] 		= temp_action_move_body;
	actions["torso"] 		= new SimpleActionMoveTorso;
	actions["shoulder"]		= new SimpleActionOscillateShoulder;
	//We set that the actions are emotional and action synch
	emotion_synch = true;
	actions_synch = true;
	context_type = ParallelContext;
}
CompositeActionWalk::~CompositeActionWalk() {
	for(std::map<std::string,AbstractActionDescription *>::iterator it = actions.begin();
			it != actions.end(); it++){
		delete it->second;
	}
}

std::string CompositeActionWalk::getActionName(){
	return "walk";
}


bool CompositeActionWalk::MandatoryParameterVerification(Json::Value parameter){
	std::string temp_name_parameter = parameter.get("name","UTF-8").asString();
	Json::Value temp_parameter = parameter;
	std::string short_name;
	int occurence_position = temp_name_parameter.find("_body");
	SimpleActionDescription *temp_action;
	if(occurence_position>0){
		temp_action = static_cast<SimpleActionDescription *>(actions["body"]);
		short_name = temp_name_parameter.substr(0,occurence_position);
		temp_parameter["name"] = short_name;
		return temp_action->ParametersVerification(temp_parameter,short_name,"mandatory");
	}
	occurence_position = temp_name_parameter.find("_shoulder");
	if(occurence_position>0){
		temp_action = static_cast<SimpleActionDescription *>(actions["shoulder"]);
		short_name = temp_name_parameter.substr(0,occurence_position);
		temp_parameter["name"] = short_name;
		return temp_action->ParametersVerification(temp_parameter,short_name,"mandatory");
	}
	occurence_position = temp_name_parameter.find("_torso");
	if(occurence_position>0){
		temp_action = static_cast<SimpleActionDescription *>(actions["torso"]);
		short_name = temp_name_parameter.substr(0,occurence_position);
		temp_parameter["name"] = short_name;
		return temp_action->ParametersVerification(temp_parameter,short_name,"mandatory");
	}
	return false;
}
bool CompositeActionWalk::OptionalParameterVerification(Json::Value parameter){

	return false;
}
