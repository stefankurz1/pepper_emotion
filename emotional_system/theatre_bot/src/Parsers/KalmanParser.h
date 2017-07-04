/*
 * KalmanParser.h
 *
 *  Created on: Aug 8, 2015
 *      Author: julian
 */

#ifndef KALMANPARSER_H_
#define KALMANPARSER_H_

#include <iostream>
#include <fstream>
#include "../json/json/json.h"
#include "../Eigen/Dense"

/**
 * This class loads the following parameters for a the Kalman Filter:
 * 	Sigma, R and Q matrices
 */
class KalmanParser {
public:
	KalmanParser();
	virtual ~KalmanParser();
	void setDirectory(std::string directory);
	bool loadInformation();
	Eigen::Matrix3f getSigmaMatrix();
	Eigen::Matrix3f getRMatrix(); //This matrix is the error from the odometry
	Eigen::Matrix3f getQMatrix(); //This matrix is the error in the sensory information
	Eigen::Matrix3f getQOdometryMatrix(); //This matrix is the error in the sensory information
	Eigen::Matrix3f getQGlobalMatrix(); //This matrix is the error in the global sensory information
private:
	std::string file;
	Eigen::Matrix3f sigma;
	Eigen::Matrix3f R;
	Eigen::Matrix3f Q;//This matrix is for the markers
	Eigen::Matrix3f Q_odometry;
	Eigen::Matrix3f Q_global;
};

#endif /* KALMANPARSER_H_ */
