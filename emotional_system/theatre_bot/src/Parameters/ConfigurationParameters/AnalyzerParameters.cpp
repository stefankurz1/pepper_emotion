/*
 * AnalyzerParameters.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: julian
 */

#include "AnalyzerParameters.h"

AnalyzerParameters::AnalyzerParameters() {
	window_size = 1;
	increase_factor = 1.0;
	decrease_factor = 1.0;
	name_analyzer = UnknownEmotionAnalyzer;
}

AnalyzerParameters::~AnalyzerParameters() {
	// TODO Auto-generated destructor stub
}
void AnalyzerParameters::setWindowSize(int window_size)
{
	this->window_size = window_size;
}
int AnalyzerParameters::getWindowSize(){
	return this->window_size;
}
void AnalyzerParameters::setIncreaseFactor(float increase_factor){
	this->increase_factor = increase_factor;
}
float AnalyzerParameters::getIncreaseFactor(){
	return this->increase_factor;
}
void AnalyzerParameters::setDecreaseFactor(float decrease_factor){
	this->decrease_factor = decrease_factor;
}
float AnalyzerParameters::getDecreaseFactor(){
	return this->decrease_factor;
}
void AnalyzerParameters::setEmotionAnalyzer(TypeEmotionAnalyzer type){
	this->name_analyzer = type;
}
TypeEmotionAnalyzer AnalyzerParameters::getEmotionAnalyzer(){
	return this->name_analyzer;
}

