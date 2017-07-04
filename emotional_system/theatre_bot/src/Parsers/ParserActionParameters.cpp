/*
 * ParserActionParameters.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: julian
 */

#include "ParserActionParameters.h"

ParserActionParameters::ParserActionParameters() {
	// TODO Auto-generated constructor stub

}

ParserActionParameters::~ParserActionParameters() {
	// TODO Auto-generated destructor stub
}

/*
 * This is just to test the system, the real implementation of these should be done in each node.
 *
 * It is not necessary verify that the current action corresponds the current parameter, because it was done
 * before.
 *
 * If I leave this class it would be a bit slower and it generates a centralization of resources and a repetitive of unnecessary code
 */

bool ParserActionParameters::parser(std::string message){
	Json::Reader reader;
	Json::Value root, temp;
	bool parsing_successful = reader.parse(message, root, false);
	if(!parsing_successful){
		return false;
	}
	//TODO Think how to implement the optional parameters
	std::string name_parameter = root.get("name","UTF-8").asString();
	if(name_parameter.compare("parameter_amplitude")==0){
		Json::Value temp_info = root.get("amplitude","UTF-8");
		std::vector<float> info_amplitude  = this->parseVector(temp_info);
		if(info_amplitude.size()==3){
			//Create parameter
		}else{
			//send error message
		}
	}else if(name_parameter.compare("parameter_circle")==0){
		Json::Value temp_info = root.get("point","UTF-8");
		std::vector<float> info_point  = this->parseVector(temp_info);
		if(!(info_point.size()==3)){
			//Error message
		}
		temp_info = root.get("radio","UTF-8");
		float info_radio  = this->parseFloat(temp_info);
		temp_info = root.get("pose","UTF-8");
		std::vector<float> info_quaternion  = this->parseVector(temp_info);
		if(info_quaternion.size()>0&&!(info_quaternion.size()==4)){
			//Error message
		}
		//Create parameter without pose
		if(info_quaternion.size()!=0){
			//Add quaternion info
		}
	}else if(name_parameter.compare("parameter_landmark")==0){
		Json::Value temp_info = root.get("landmark_type","UTF-8");
		TypeLandmark info_type = this->parseLandmark(temp_info);
		if(info_type == Unknown_Landmark){
			//Send error;
		}
		temp_info = root.get("landmark_id","UTF-8");
		int info_id  = static_cast<int>(this->parseFloat(temp_info));
		temp_info = root.get("pose","UTF-8");
		std::vector<float> info_quaternion  = this->parseVector(temp_info);
		if(info_quaternion.size()>0&&!(info_quaternion.size()==4)){
			//Error message
		}
		//Create parameter without pose
		if(info_quaternion.size()!=0){
			//Add quaternion info
		}

	}else if(name_parameter.compare("parameter_point")==0){
		Json::Value temp_info = root.get("point","UTF-8");
		std::vector<float> info_point  = this->parseVector(temp_info);
		if(!(info_point.size()==3)){
			//Error message
		}
		temp_info = root.get("pose","UTF-8");
		std::vector<float> info_quaternion  = this->parseVector(temp_info);
		if(info_quaternion.size()>0&&!(info_quaternion.size()==4)){
			//Error message
		}
		//Create parameter without pose
		if(info_quaternion.size()!=0){
			//Add quaternion info
		}
	}else if(name_parameter.compare("parameter_speech")==0){
		Json::Value temp_info = root.get("text","UTF-8");
		std::string info_text  = this->parseString(temp_info);
		if(info_text.compare("")==0){
			//Error message
		}
		//Create parameter

	}else if(name_parameter.compare("parameter_square")==0){
		Json::Value temp_info = root.get("point","UTF-8");
		std::vector<float> info_point  = this->parseVector(temp_info);
		if(!(info_point.size()==3)){
			//Error message
		}
		temp_info = root.get("delta","UTF-8");
		std::vector<float> info_delta  = this->parseVector(temp_info);
		if(!(info_delta.size()==1)){
			//Error message
		}
		temp_info = root.get("pose","UTF-8");
		std::vector<float> info_quaternion  = this->parseVector(temp_info);
		if(info_quaternion.size()>0&&!(info_quaternion.size()==4)){
			//Error message
		}
		//Create parameter without pose
		if(info_quaternion.size()!=0){
			//Add quaternion info
		}
	}else if(name_parameter.compare("parameter_time")==0){
		Json::Value temp_info = root.get("time","UTF-8");
		float info_time  = this->parseFloat(temp_info);
		//Create parameter
	}
	return false;
}


TypeLandmark ParserActionParameters::parseLandmark(Json::Value temp_info){
	if(temp_info.asString().compare("Person_Landmark")==0){
		return Person_Landmark;
	}else if(temp_info.asString().compare("Object_Landmark")==0){
		return Object_Landmark;
	}else if(temp_info.asString().compare("Place_Landmark")==0){
		return Place_Landmark;
	}
	return Unknown_Landmark;
}

std::string ParserActionParameters::parseString(Json::Value temp_info){
	if(!temp_info.isNull()){
		return temp_info.asString();
	}
	return "";
}

std::vector<float> ParserActionParameters::parseVector(Json::Value temp_info){
	std::vector<float> vector;
	if(!temp_info.isNull() && temp_info.isArray()){
		Json::Value value;
		for(int i= 0; i< temp_info.size(); ++i){
			value = temp_info.get(i,"UTF-8");
			if(!value.isNull() && value.isNumeric()){
				vector.push_back(value.asFloat());
			}
		}
	}
	return vector;
}

float ParserActionParameters::parseFloat(Json::Value temp_info){
	if(!temp_info.isNull() && temp_info.isNumeric()){
		return temp_info.asFloat();
	}
	return 0;
}
