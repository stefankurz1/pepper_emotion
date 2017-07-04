/*
 * ReactiveModel.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#include "ReactiveModel.h"

ReactiveModel::ReactiveModel() {
	this->social_bias = 0;
	this->last_stimulus = 0;
	this->decrease_factor = -0.6;
	this->base_increase = 30.0;
	this->image_width = 0;
	this->image_height = 0;
	this->first_execution = true;
	this->factor_increase = 10.0;
	this->max_stimuli_level = 100.0;
	this->increase_coefficient = 0.3;
	this->minimum_time_to_image = 0.1;//this is the interval to get a new image
	this->time_factor_coefficient = 9.4;
	this->time_factor_slope=this->time_factor_coefficient*this->minimum_time_to_image;
	this->debug = false;
	this->threshold = static_cast<int>(5.0*255.0/100.0);
}

ReactiveModel::~ReactiveModel() {
	// TODO Auto-generated destructor stub
	if(debug){
		myfile.close();
		myfile_slope.close();
	}
}

void ReactiveModel::initParameters(){
	last_image = cv::Mat(image_width,image_height,CV_8UC1);
}

void ReactiveModel::activateDebug(std::string folder){
	this->debug = true;
	this->folder_debug = folder;
	std::string temp_file = folder +"/slope_reactive_model.txt";
	myfile_slope.open(temp_file.c_str());
	temp_file = folder + "/data_reactive_model.txt";
	myfile.open(temp_file.c_str());
}

void ReactiveModel::setCameraParameters(int image_width, int image_height){
	this->image_width = image_width;
	this->image_height = image_height;
}

TypeOfSlope ReactiveModel::newImage(cv::Mat image, float diff_time){
	TypeOfSlope slope_type = zero_slope;
	if(!first_execution){
		float percentage = this->detectChangeGray(image);
		float temp_stimulus = imageChangeStimulus(percentage,diff_time);
	//std::cout<<temp_arousal<<" "<<diff_time<<std::endl;
		float decrease_stimulus = decreaseStimulus(temp_stimulus,diff_time);
		float result_stimulus = temp_stimulus + decrease_stimulus +last_stimulus;
		//calculates the slope in the change
		float slope = calculateSlope(diff_time,result_stimulus);
		//The events are the difference in the slope
		slope_type = obtainEvent(slope);
		if(debug){
			myfile <<diff_time<<";"<<percentage<<";"<<temp_stimulus<<";"<<decrease_stimulus<<";"<<result_stimulus<<"\n";
			myfile_slope<<slope<<";"<<slope_type<<"\n";
		}
		last_stimulus = result_stimulus;
	}else{
		first_execution = false;
	}
	last_image = image;
	return slope_type;
}

TypeOfSlope ReactiveModel::obtainEvent(float slope){
	if(slope == 0){
		return zero_slope;
	}else if(slope<0){
		if(slope>-2.5*time_factor_slope){
			return small_negative_slope;
		}else if(slope>-15*time_factor_slope){
			return medium_negative_slope;
		}else if(slope>-40*time_factor_slope){
			return large_negative_slope;
		}else{
			return huge_negative_slope;
		}
	}else{
		if(slope<2.5*time_factor_slope){
			return small_positive_slope;
		}else if(slope<15*time_factor_slope){
			return medium_positive_slope;
		}else if(slope<40*time_factor_slope){
			return large_positive_slope;
		}else{
			return huge_positive_slope;
		}
	}
}

float ReactiveModel::calculateSlope(float diff_time, float result_stimulus){
	return (result_stimulus - last_stimulus)/diff_time;
}

void ReactiveModel::setMaxStimuliLevel(float max_stimuli_level){
	this->max_stimuli_level = max_stimuli_level;
}

float ReactiveModel::decreaseStimulus(float temp_stimulus,float diff_time){
	return (last_stimulus+temp_stimulus-social_bias)*decrease_factor*diff_time;
}

float ReactiveModel::imageChangeStimulus(float diff_percentage, float diff_time){
	return static_cast<float>((powf(base_increase,diff_percentage-increase_coefficient)-powf(base_increase,-increase_coefficient))*diff_time*factor_increase);
}

float ReactiveModel::detectChangeGray(cv::Mat new_image){
	int change_pixel = 0;
	cv::Size size = last_image.size();
	int row = size.height;
	int cols = size.width;
	int pixel;
	cv::Size size2 = new_image.size();
	int t = new_image.channels();
	if(last_image.channels() == 1 && new_image.channels()==1){
		for(int i = 0; i<row; i++){
			for(int j = 0; j<cols; j++){
				pixel = abs(static_cast<int>(new_image.at<uchar>(i,j))-static_cast<int>(last_image.at<uchar>(i,j)));
				//std::cout<<"Info "<<new_image.at<uchar>(i,j)<<" - "<<last_image.at<uchar>(i,j)<<" - "<<pixel<<";"<<std::endl;
				if(pixel>threshold){
					change_pixel++;
				}
			}
		}
	}else{
		throw std::runtime_error("the images should be in gray scale");
	}
	return static_cast<float>(change_pixel)/static_cast<float>(row*cols);
}

void ReactiveModel::setMinimumTimeToImage(float minimum_time_to_image){
	this->minimum_time_to_image = minimum_time_to_image;
	this->time_factor_slope=this->time_factor_coefficient*this->minimum_time_to_image;
}

float ReactiveModel::getBaseIncrease(){
	return base_increase;
}

void ReactiveModel::setBaseIncrease(float baseIncrease) {
	base_increase = baseIncrease;
}

float ReactiveModel::getDecreaseFactor(){
	return decrease_factor;
}

void ReactiveModel::setDecreaseFactor(float decreaseFactor) {
	decrease_factor = decreaseFactor;
}

float ReactiveModel::getFactorIncrease(){
	return factor_increase;
}

void ReactiveModel::setFactorIncrease(float factorIncrease) {
	factor_increase = factorIncrease;
}

float ReactiveModel::getIncreaseCoefficient(){
	return increase_coefficient;
}

void ReactiveModel::setIncreaseCoefficient(float increaseCoefficient) {
	increase_coefficient = increaseCoefficient;
}

float ReactiveModel::getMinimumTimeToImage(){
	return minimum_time_to_image;
}

float ReactiveModel::getSocialBias(){
	return social_bias;
}

void ReactiveModel::setSocialBias(float socialBias) {
	social_bias = socialBias;
}

int ReactiveModel::getThreshold(){
	return threshold;
}

void ReactiveModel::setThreshold(int threshold) {
	this->threshold = threshold;
}

float ReactiveModel::getTimeFactorCoefficient() {
	return time_factor_coefficient;
}

void ReactiveModel::setTimeFactorCoefficient(float timeFactorCoefficient) {
	time_factor_coefficient = timeFactorCoefficient;
	this->time_factor_slope=this->time_factor_coefficient*this->minimum_time_to_image;
}
