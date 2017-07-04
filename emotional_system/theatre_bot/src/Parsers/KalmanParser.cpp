/*
 * KalmanParser.cpp
 *
 *  Created on: Aug 8, 2015
 *      Author: julian
 */

#include "KalmanParser.h"

KalmanParser::KalmanParser() {
	//By default all the matrices are initialized to zero
	sigma<<	0.0,	0.0,	0.0,
			0.0,	0.0,	0.0,
			0.0,	0.0,	0.0;
	R<<		0.0,	0.0,	0.0,
			0.0,	0.0,	0.0,
			0.0,	0.0,	0.0;
	Q<<		0.0,	0.0,	0.0,
			0.0,	0.0,	0.0,
			0.0,	0.0,	0.0;
	Q_odometry<< 0.0,	0.0,	0.0,
			0.0,	0.0,	0.0,
			0.0,	0.0,	0.0;
	Q_global <<0.0,	0.0,	0.0,
			0.0,	0.0,	0.0,
			0.0,	0.0,	0.0;
}

KalmanParser::~KalmanParser() {
	// TODO Auto-generated destructor stub
}


void KalmanParser::setDirectory(std::string directory){
	this->file = directory + "/robot_configuration_files/kalman_parameters.json";
}

bool KalmanParser::loadInformation(){
	//Read the file and make the parser
	Json::Reader reader;
	Json::Value root, temp;
	std::ifstream test(file.c_str(), std::ifstream::binary);
	bool parsing_successful = reader.parse(test, root, false);
	if(!parsing_successful){
		return false;
	}
	//Get sigma matrix
	Json::Value temp_info = root.get("sigma","UTF-8");
	if(temp_info.isArray() && temp_info.size() == 9){
		int i = 0;
		int j = 0;
		for(int k = 0; k< temp_info.size(); ++k){
			sigma(i,j) = temp_info.get(k,"UTF-8").asFloat();
			++j;
			if(j % 3 == 0){
				j = 0;
				i++;
			}
		}
	}
	//Get R matrix
	temp_info = root.get("R","UTF-8");
	if(temp_info.isArray() && temp_info.size() == 9){
		int i = 0;
		int j = 0;
		for(int k = 0; k< temp_info.size(); ++k){
			R(i,j) = temp_info.get(k,"UTF-8").asFloat();
			++j;
			if(j % 3 == 0){
				j = 0;
				i++;
			}
		}
	}
	//Get Q matrix
	temp_info = root.get("Q","UTF-8");
	if(temp_info.isArray() && temp_info.size() == 9){
		int i = 0;
		int j = 0;
		for(int k = 0; k< temp_info.size(); ++k){
			Q(i,j) = temp_info.get(k,"UTF-8").asFloat();
			++j;
			if(j % 3 == 0){
				j = 0;
				i++;
			}
		}
	}
	//Get Q odometry matrix
	temp_info = root.get("Q_odometry","UTF-8");
	if(temp_info.isArray() && temp_info.size() == 9){
		int i = 0;
		int j = 0;
		for(int k = 0; k< temp_info.size(); ++k){
			Q_odometry(i,j) = temp_info.get(k,"UTF-8").asFloat();
			++j;
			if(j % 3 == 0){
				j = 0;
				i++;
			}
		}
	}
	//Get Q Kalman matrix
	temp_info = root.get("Q_global","UTF-8");
	if(temp_info.isArray() && temp_info.size() == 9){
		int i = 0;
		int j = 0;
		for(int k = 0; k< temp_info.size(); ++k){
			Q_global(i,j) = temp_info.get(k,"UTF-8").asFloat();
			++j;
			if(j % 3 == 0){
				j = 0;
				i++;
			}
		}
	}
	return true;
}

Eigen::Matrix3f KalmanParser::getQGlobalMatrix(){
	return Q_global;
}

Eigen::Matrix3f KalmanParser::getSigmaMatrix(){
	return sigma;
}

Eigen::Matrix3f KalmanParser::getRMatrix(){
	return R;
}

Eigen::Matrix3f KalmanParser::getQMatrix(){
	return Q;
}

Eigen::Matrix3f KalmanParser::getQOdometryMatrix(){ //This matrix is the error in the sensory information
	return Q_odometry;
}
