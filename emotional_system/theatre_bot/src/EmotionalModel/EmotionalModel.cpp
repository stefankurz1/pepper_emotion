/*
 * EmotionalModel.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#include "EmotionalModel.h"

EmotionalModel::EmotionalModel() {
	// TODO Auto-generated constructor stub
	this->minimum_time_to_image = 0.1;
	this->event_fear_analyzer.setEventWindowSize(3);
	this->event_surprise_analyzer.setEventWindowSize(3);
	this->event_interest_analyzer.setEventWindowSize(3);
	this->event_relief_analyzer.setEventWindowSize(5);
	fear_intensity = 0;
	surprise_intensity = 0;
	relief_intensity = 0;
	interest_intensity = 0;
	this->debug = false;
}

EmotionalModel::~EmotionalModel() {
	// TODO Auto-generated destructor stub
	if(debug){
		myfile.close();
	}
}


void EmotionalModel::newImage(cv::Mat image, std::string *emotion_name, float *intensity, float diff_time){
	TypeOfSlope slope_type = reactive_model.newImage(image,diff_time);
	//Update of emotion intensities
	fear_intensity = event_fear_analyzer.analyzeEvent(slope_type,diff_time);
	surprise_intensity = event_surprise_analyzer.analyzeEvent(slope_type,diff_time);
	relief_intensity = event_relief_analyzer.analyzeEvent(slope_type,diff_time);
	interest_intensity = event_interest_analyzer.analyzeEvent(slope_type,diff_time);
	if(debug){
		myfile<<fear_intensity<<";"<<surprise_intensity<<";"<<relief_intensity<<";"<<interest_intensity<<"\n";
	}
}


void EmotionalModel::newImageDebug(cv::Mat image, std::string *emotion_name, float *intensity, float diff_time,float *fear_intensity,float *surprise_intensity,float *relief_intensity,float *interest_intensity){
	this->newImage(image,emotion_name,intensity,diff_time);
	*fear_intensity = this->fear_intensity;
	*surprise_intensity = this->surprise_intensity;
	*relief_intensity = this->relief_intensity;
	*interest_intensity = this->interest_intensity;
}

void EmotionalModel::setCameraParameters(int image_width, int image_height){
	reactive_model.setCameraParameters(image_width,image_height);
}

float EmotionalModel::getMinimumTimeToImage(){
	return reactive_model.getMinimumTimeToImage();
}

void EmotionalModel::initParameters(){
	reactive_model.initParameters();
}

void EmotionalModel::setMinimumTimeToImage(float minimum_time_to_image){
	this->minimum_time_to_image = minimum_time_to_image;
	this->reactive_model.setMinimumTimeToImage(this->minimum_time_to_image);
}


void EmotionalModel::activateDebug(std::string folder){
	this->debug = true;
	this->folder_debug = folder;
	std::string file = folder+"/emotions_intensities.txt";
	myfile.open(file.c_str());
	this->reactive_model.activateDebug(folder);
}

void EmotionalModel::readReactiveModelParameters(std::string file){
	ParserConfigurationFiles parser;
	ReactiveModelParameters reactive_parameters;
	reactive_parameters = parser.readReactiveModelParameters(file);
	reactive_model.setSocialBias(reactive_parameters.getSocialBias());
	reactive_model.setDecreaseFactor(reactive_parameters.getDecreaseFactor());
	reactive_model.setBaseIncrease(reactive_parameters.getBaseIncrease());
	reactive_model.setFactorIncrease(reactive_parameters.getFactorIncrease());
	reactive_model.setIncreaseCoefficient(reactive_parameters.getIncreaseCoefficient());
	reactive_model.setMinimumTimeToImage(reactive_parameters.getMinimumTimeToImage());
	reactive_model.setTimeFactorCoefficient(reactive_parameters.getTimeFactorCoefficient());
	reactive_model.setThreshold(reactive_parameters.getThreshold());
	this->minimum_time_to_image = reactive_model.getMinimumTimeToImage();
}

void EmotionalModel::readAnalyzerParameters(std::string file){
	ParserConfigurationFiles parser;
	std::vector<AnalyzerParameters> temp_list = parser.readAnalyzerParameters(file);
	for(std::vector<AnalyzerParameters>::iterator it = temp_list.begin(); it != temp_list.end(); ++it){
		if(it->getEmotionAnalyzer() == FearEmotionAnalyzer){
			this->event_fear_analyzer.setEventWindowSize(it->getWindowSize());
			this->event_fear_analyzer.setIncreaseFactor(it->getIncreaseFactor());
			this->event_fear_analyzer.setDecreaseFactor(it->getDecreaseFactor());
		}else if(it->getEmotionAnalyzer() == SurpriseEmotionAnalyzer){
			this->event_surprise_analyzer.setEventWindowSize(it->getWindowSize());
			this->event_surprise_analyzer.setIncreaseFactor(it->getIncreaseFactor());
			this->event_surprise_analyzer.setDecreaseFactor(it->getDecreaseFactor());
		}else if(it->getEmotionAnalyzer() == InterestEmotionAnalyzer){
			this->event_interest_analyzer.setEventWindowSize(it->getWindowSize());
			this->event_interest_analyzer.setIncreaseFactor(it->getIncreaseFactor());
			this->event_interest_analyzer.setDecreaseFactor(it->getDecreaseFactor());
		}else if(it->getEmotionAnalyzer() == ReliefEmotioAnalyzer){
			this->event_relief_analyzer.setEventWindowSize(it->getWindowSize());
			this->event_relief_analyzer.setIncreaseFactor(it->getIncreaseFactor());
			this->event_relief_analyzer.setDecreaseFactor(it->getDecreaseFactor());
		}
	}
}
