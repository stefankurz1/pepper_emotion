/*
 * EmotionMovementParameter.h
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#ifndef EMOTIONMOVEMENTPARAMETER_H_
#define EMOTIONMOVEMENTPARAMETER_H_

#include "EmotionParameter.h"

/**
 * This class is a specialization of Emotion parameter for all the actions that are related with movement and where
 * the animacy principles applies
 */

class EmotionMovementParameter: public EmotionParameter {
public:
	EmotionMovementParameter();
	virtual ~EmotionMovementParameter();


	float getEmotionParameterTime();
	/*
	 * set the time in which the modification should be done. The time is in milliseconds.
	 */
	void setEmotionParameterTime(float emotion_parameter_time);
	float getEmotionParameterSpacing();
	/*
	 * set the space between the two points
	 */
	void setEmotionParameterSpacing(float emotion_parameter_spacing);
	EmotionParameter * copyEmotionParameter();
	std::string generateMessage();

private:
	float spacing;
	float timing;
};

#endif /* EMOTIONMOVEMENTPARAMETER_H_ */
