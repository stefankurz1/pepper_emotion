/*
 * ReactiveModelParameters.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: julian
 */

#include "ReactiveModelParameters.h"

ReactiveModelParameters::ReactiveModelParameters() {
	this->social_bias = 0;
	this->decrease_factor = -0.6;
	this->base_increase = 30.0;
	this->factor_increase = 10.0;
	this->increase_coefficient = 0.3;
	this->minimum_time_to_image = 0.1;//this is the interval to get a new image
	this->time_factor_coefficient = 9.4;
	this->threshold = static_cast<int>(5.0*255.0/100.0);

}

ReactiveModelParameters::~ReactiveModelParameters() {
	// TODO Auto-generated destructor stub
}



float ReactiveModelParameters::getBaseIncrease(){
	return base_increase;
}

void ReactiveModelParameters::setBaseIncrease(float baseIncrease) {
	base_increase = baseIncrease;
}

float ReactiveModelParameters::getDecreaseFactor(){
	return decrease_factor;
}

void ReactiveModelParameters::setDecreaseFactor(float decreaseFactor) {
	decrease_factor = decreaseFactor;
}

float ReactiveModelParameters::getFactorIncrease(){
	return factor_increase;
}

void ReactiveModelParameters::setFactorIncrease(float factorIncrease) {
	factor_increase = factorIncrease;
}

float ReactiveModelParameters::getIncreaseCoefficient(){
	return increase_coefficient;
}

void ReactiveModelParameters::setIncreaseCoefficient(float increaseCoefficient) {
	increase_coefficient = increaseCoefficient;
}

float ReactiveModelParameters::getMinimumTimeToImage(){
	return minimum_time_to_image;
}

void ReactiveModelParameters::setMinimumTimeToImage(float minimumTimeToImage) {
	minimum_time_to_image = minimumTimeToImage;
}

float ReactiveModelParameters::getSocialBias(){
	return social_bias;
}

void ReactiveModelParameters::setSocialBias(float socialBias) {
	social_bias = socialBias;
}

int ReactiveModelParameters::getThreshold(){
	return threshold;
}

void ReactiveModelParameters::setThreshold(int threshold) {
	this->threshold = threshold;
}

float ReactiveModelParameters::getTimeFactorCoefficient() {
	return time_factor_coefficient;
}

void ReactiveModelParameters::setTimeFactorCoefficient(float timeFactorCoefficient) {
	time_factor_coefficient = timeFactorCoefficient;
}
