/*
 * EmotionParser.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: julian
 */

#include "EmotionParser.h"

EmotionParser::EmotionParser() {
	// TODO Auto-generated constructor stub

}

EmotionParser::~EmotionParser() {
	// TODO Auto-generated destructor stub
}

/**
 * The method return false if their is any problem with the parameter o just because it is empty. In both cases is the same
 */
bool EmotionParser::parse(std::string message, std::vector<EmotionMovementParameter> *parameters_x,std::vector<EmotionMovementParameter> *parameters_y,std::vector<EmotionMovementParameter> *parameters_z, bool *repetition){
	Json::Reader reader;
	Json::Value root, temp;
	bool parsing_successful = reader.parse(message, root, false);
	if(!parsing_successful){
		return false;
	}
	if(root.empty()){
		return false;
	}
	Json::Value temp_info = root.get("type","UTF-8");
	if(temp_info.asString().compare("movement_parameter") !=0){
		return false;
	}
	temp_info = root.get("repetition","UTF-8");
	if(temp_info.asString().compare("yes")==0){
		//std::cout<<"parser say yes repeat!!"<<std::endl;
		*repetition = true;
	}else{
		//std::cout<<"parser say no repeat!! "<<temp_info.asString()<<std::endl;
		*repetition = false;
	}
	temp_info = root.get("parameters","UTF-8");
	if(!temp_info.isArray()||temp_info.empty()){
		return false;
	}
	Json::Value value, parameter;
	for(int i=0; i<temp_info.size(); ++i){
		value = temp_info.get(i,"UTF-8");
		if(value.empty()){
			return false;
		}
		if(i==0){
			for(int j=0; j<value.size();++j){
				parameter = value.get(j,"UTF-8");
				EmotionMovementParameter tem_emotional_parameter;
				tem_emotional_parameter.setEmotionParameterSpacing(parameter.get("space","UTF-8").asFloat());
				tem_emotional_parameter.setEmotionParameterTime(parameter.get("velocity","UTF-8").asFloat());
				parameters_x->push_back(tem_emotional_parameter);
			}
		}
		if(i==1){
			for(int j=0; j<value.size();++j){
				parameter = value.get(j,"UTF-8");
				EmotionMovementParameter tem_emotional_parameter;
				tem_emotional_parameter.setEmotionParameterSpacing(parameter.get("space","UTF-8").asFloat());
				tem_emotional_parameter.setEmotionParameterTime(parameter.get("velocity","UTF-8").asFloat());
				parameters_y->push_back(tem_emotional_parameter);
			}
		}
		if(i==2){
			for(int j=0; j<value.size();++j){
				parameter = value.get(j,"UTF-8");
				EmotionMovementParameter tem_emotional_parameter;
				tem_emotional_parameter.setEmotionParameterSpacing(parameter.get("space","UTF-8").asFloat());
				tem_emotional_parameter.setEmotionParameterTime(parameter.get("velocity","UTF-8").asFloat());
				parameters_z->push_back(tem_emotional_parameter);
			}
		}
	}
	return true;
}
