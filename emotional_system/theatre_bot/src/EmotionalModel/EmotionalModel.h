/*
 * EmotionalModel.h
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#ifndef EMOTIONALMODEL_H_
#define EMOTIONALMODEL_H_

#include "ReactiveModel.h"
#include "EmotionEventAnalyzer/EventFearAnalyzer.h"
#include "EmotionEventAnalyzer/EventInterestAnalyzer.h"
#include "EmotionEventAnalyzer/EventReliefAnalyzer.h"
#include "EmotionEventAnalyzer/EventSurpriseAnalyzer.h"

#include "../Parsers/ParserConfigurationFiles.h"

#include "opencv2/imgproc/imgproc.hpp"

class EmotionalModel {
public:
	EmotionalModel();
	virtual ~EmotionalModel();
	void newImage(cv::Mat image, std::string *emotion_name, float *intensity, float diff_time);
	void newImageDebug(cv::Mat image, std::string *emotion_name, float *intensity, float diff_time,float *fear_intensity,float *surprise_intensity,float *relief_intensity,float *interest_intensity);
	void setCameraParameters(int image_width, int image_height);
	void initParameters();
	void setMinimumTimeToImage(float minimum_time_to_image);
	float getMinimumTimeToImage();
	void activateDebug(std::string folder);
	void readAnalyzerParameters(std::string file);
	void readReactiveModelParameters(std::string file);
private:
	//This is a reactive model reacts to changes in the image
	ReactiveModel reactive_model;
	float minimum_time_to_image;
	//Analysis the information and generates an intensity
	EventFearAnalyzer event_fear_analyzer;
	EventInterestAnalyzer event_interest_analyzer;
	EventReliefAnalyzer event_relief_analyzer;
	EventSurpriseAnalyzer event_surprise_analyzer;
	float fear_intensity;
	float surprise_intensity;
	float relief_intensity;
	float interest_intensity;
	std::ofstream myfile;
	bool debug;
	std::string folder_debug;
};

#endif /* EMOTIONALMODEL_H_ */
