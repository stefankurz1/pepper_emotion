/*
 * AnalyzerParameters.h
 *
 *  Created on: Mar 25, 2015
 *      Author: julian
 */

#ifndef ANALYZERPARAMETERS_H_
#define ANALYZERPARAMETERS_H_

#include "TypeEmotionAnalyzer.h"

class AnalyzerParameters {
public:
	AnalyzerParameters();
	virtual ~AnalyzerParameters();
	void setWindowSize(int window_size);
	int getWindowSize();
	void setIncreaseFactor(float increase_factor);
	float getIncreaseFactor();
	void setDecreaseFactor(float decrease_factor);
	float getDecreaseFactor();
	void setEmotionAnalyzer(TypeEmotionAnalyzer type);
	TypeEmotionAnalyzer getEmotionAnalyzer();
private:
	TypeEmotionAnalyzer name_analyzer;
	int window_size;
	float increase_factor;
	float decrease_factor;
};

#endif /* ANALYZERPARAMETERS_H_ */
