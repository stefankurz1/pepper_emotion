/*
 * ReactiveModel.h
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#ifndef REACTIVEMODEL_H_
#define REACTIVEMODEL_H_
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include "TypeOfSlope.h"
#include "opencv2/imgproc/imgproc.hpp"

class ReactiveModel {
public:
	ReactiveModel();
	virtual ~ReactiveModel();
	TypeOfSlope newImage(cv::Mat image, float diff_time);
	void setCameraParameters(int image_width, int image_height);
	void initParameters();
	void setMaxStimuliLevel(float max_stimuli_level);
	void setMinimumTimeToImage(float minimum_time_to_image);
	void activateDebug(std::string folder);
	float getBaseIncrease();
	void setBaseIncrease(float baseIncrease);
	float getDecreaseFactor();
	void setDecreaseFactor(float decreaseFactor);
	float getFactorIncrease();
	void setFactorIncrease(float factorIncrease) ;
	float getIncreaseCoefficient();
	void setIncreaseCoefficient(float increaseCoefficient);
	float getMinimumTimeToImage();
	float getSocialBias();
	void setSocialBias(float socialBias);
	int getThreshold();
	void setThreshold(int threshold);
	float getTimeFactorCoefficient();
	void setTimeFactorCoefficient(float timeFactorCoefficient);
private:
	cv::Mat last_image; //Last image that is going to be used to compare
	int image_width; //width of the image
	int image_height; //height of the image
	float social_bias;//this is a bias that could be used ... still thinking about it
	float last_stimulus; //last value of the stimulus, it could be greater than max_stimuli
	float decrease_factor;
	float base_increase;//base to be3 used in the exponential
	float factor_increase;//factor to increase the output of the exponential
	bool first_execution;
	float time_factor_slope;//this modulates the slope to different time windows
	float time_factor_coefficient;
	float increase_coefficient;
	std::ofstream myfile;
	std::ofstream myfile_slope;
	float max_stimuli_level; //Set a maximum level to use in the motion detection however the last level can grows away from this level. This is consider if a stimulus last long and is high, the time to relax it would be relative to this
	float minimum_time_to_image;//this is the interval to get a new image
	int threshold;
	bool debug;
	std::string folder_debug;
	float detectChangeGray(cv::Mat new_iamge);
	float imageChangeStimulus(float diff_percentage, float diff_time);
	float decreaseStimulus(float temp_stimulus,float diff_time);
	float calculateSlope(float diff_time, float result_stimulus);
	TypeOfSlope obtainEvent(float slope);
};

#endif /* REACTIVEMODEL_H_ */
