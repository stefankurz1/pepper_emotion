/*
 * ParserConfigurationFiles.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: julian
 */

#include "ParserConfigurationFiles.h"

ParserConfigurationFiles::ParserConfigurationFiles() {
	// TODO Auto-generated constructor stub

}

ParserConfigurationFiles::~ParserConfigurationFiles() {
	// TODO Auto-generated destructor stub
}


ReactiveModelParameters ParserConfigurationFiles::readReactiveModelParameters(std::string file){
	ReactiveModelParameters parameters;
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root, value;
	Json::Reader reader;
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		if (parsingSuccessful) {
			value = root.get("social_bias","UTF_8");
			if(value.isNumeric()){
				parameters.setSocialBias(value.asFloat());
			}
			value = root.get("decrease_factor","UTF_8");
			if(value.isNumeric()){
				parameters.setDecreaseFactor(value.asFloat());
			}
			value = root.get("base_increase","UTF_8");
			if(value.isNumeric()){
				parameters.setBaseIncrease(value.asFloat());
			}
			value = root.get("factor_increase","UTF_8");
			if(value.isNumeric()){
				parameters.setFactorIncrease(value.asFloat());
			}
			value = root.get("increase_coefficient","UTF_8");
			if(value.isNumeric()){
				parameters.setIncreaseCoefficient(value.asFloat());
			}
			value = root.get("minimum_time_to_image","UTF_8");
			if(value.isNumeric()){
				parameters.setMinimumTimeToImage(value.asFloat());
			}
			value = root.get("time_factor_coefficient","UTF_8");
			if(value.isNumeric()){
				parameters.setTimeFactorCoefficient(value.asFloat());
			}
			value = root.get("threshold","UTF_8");
			if(value.isNumeric()){
				parameters.setThreshold(value.asInt());
			}
		}
	}
	return parameters;
}

std::vector<AnalyzerParameters> ParserConfigurationFiles::readAnalyzerParameters(std::string file){
	std::vector<AnalyzerParameters> vector_parameters;
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root, emotion_parameter;
	Json::Reader reader;
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		if (parsingSuccessful) {
			if(root.isArray()){
				AnalyzerParameters temp_parameter;
				for(int i = 0; i<root.size(); ++i){
					emotion_parameter = root.get(i,"UTF_8");
					temp_parameter.setDecreaseFactor(emotion_parameter.get("decrease_factor","UTF_8").asFloat());
					temp_parameter.setIncreaseFactor(emotion_parameter.get("increase_factor","UTF_8").asFloat());
					temp_parameter.setWindowSize(emotion_parameter.get("window_size","UTF_8").asInt());
					temp_parameter.setEmotionAnalyzer(this->typeEmotionAnalyzer(emotion_parameter.get("name","UTF_8").asString()));
					vector_parameters.push_back(temp_parameter);
				}
			}
		}
	}

	return vector_parameters;
}
/**
 * Each time that is necessary to add new emotion analyzer should be added here
 */
TypeEmotionAnalyzer ParserConfigurationFiles::typeEmotionAnalyzer(std::string name){
	if(name.compare("fear")==0){
		return FearEmotionAnalyzer;
	}else if(name.compare("surprise")==0){
		return SurpriseEmotionAnalyzer;
	}else if(name.compare("interest")==0){
		return InterestEmotionAnalyzer;
	}else if(name.compare("relief")==0){
		return ReliefEmotioAnalyzer;
	}
	return UnknownEmotionAnalyzer;
}

void ParserConfigurationFiles::readRobotInitialPositionFile(std::string file, float *initial_position_x,float *initial_position_y, float *initial_position_theta){
	TheatrePlaces theatre_places;
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root;
	Json::Reader reader;
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		if (!parsingSuccessful) {
			//Include error messages
			//std::cout << "Error" << std::endl;
			return;
		}
		Json::Value position = root.get("initial_position","UTF-8");
		if(position.isArray()){
			if(position.size() == 3){
				for(int i = 0; i < position.size(); ++i){
					if(i==0){
						*initial_position_x = position.get(i,"UTF-8").asFloat();
					}else if(i==1){
						*initial_position_y = position.get(i,"UTF-8").asFloat();
					}else if(i == 2){
						*initial_position_theta = position.get(i,"UTF-8").asFloat();
					}
				}
			}
		}
	}
}



TheatrePlaces ParserConfigurationFiles::readSceneDescriptionFile(std::string file){
	TheatrePlaces theatre_places;
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root, value;
	Json::Reader reader;
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		if (parsingSuccessful) {
			//Include error messages
			//std::cout << "Error" << std::endl;

		float lenght_x = 0;
		float lenght_y = 0;
		float number_x = 0;
		float number_y = 0;
		value = root.get("maximum_lenght_x","UTF-8");
		if(value.isNumeric())
			lenght_x = value.asFloat();
		value = root.get("maximum_lenght_y","UTF-8");
		if(value.isNumeric())
			lenght_y = value.asFloat();
		value = root.get("number_rectangles_x","UTF-8");
		if(value.isNumeric())
			number_x = value.asFloat();
		value = root.get("number_rectangles_y","UTF-8");
		if(value.isNumeric())
			number_y = value.asFloat();
		theatre_places.setStageInformation(lenght_x,lenght_y,number_x,number_y);
		}
	}
	return theatre_places;
}


std::map<int, MarkerPosition> ParserConfigurationFiles::readMarkersPositionDescriptionFile(std::string file){
	//creates a hash map with the id of the marker and the information
	std::map<int, MarkerPosition> markers;
	//It opens the desire file
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root, value, marker_info, marker_position;
	Json::Reader reader;
	//It verifies that the file exist and it is possible to use it
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		//if it was possible to parser the file
		if (parsingSuccessful) {
				//gets the landmark localization
				value = root.get("landmarks_localization","UTF-8");
				if(value.isArray()){
					//Gets all the landmark position
					for(int i = 0; i< value.size(); ++i){
						marker_info = value.get(i,"UTF-8");
						if(marker_info.isObject()){
							int id = marker_info.get("marker_id","UTF-8").asInt();
							MarkerPosition marker;
							marker_position = marker_info.get("marker_position","UTF-8");
							if(marker_position.isArray()){
								if(marker_position.size() == 5){
									marker.setMarkerID(id);
									unsigned int num = 0;
									marker.setMarkerX(marker_position.get(num,"UTF-8").asFloat());
									num = 1;
									marker.setMarkerY(marker_position.get(num,"UTF-8").asFloat());
									num = 2;
									marker.setMarkerYaw(marker_position.get(num,"UTF-8").asFloat());
									num = 3;
									marker.setMarkerRoll(marker_position.get(num,"UTF-8").asFloat());
									num = 4;
									marker.setMarkerPitch(marker_position.get(num,"UTF-8").asFloat());
								}
							}
							//Add the marker
							if(marker.getMarkerID()>0){
								markers[id] = marker;
							}
						}
					}
			}
		}

	}
	return markers;
}
