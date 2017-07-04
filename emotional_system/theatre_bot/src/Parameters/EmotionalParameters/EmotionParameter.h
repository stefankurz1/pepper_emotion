///////////////////////////////////////////////////////////
//  EmotionParameter.h
//  Implementation of the Class EmotionParameter
//  Created on:      04-dic-2014 04:42:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(EMOTIONPARAMETER_H_)
#define EMOTIONPARAMETER_H_

#include "../Parameter.h"

#include "../../json/json/json.h"

class EmotionParameter : public Parameter
{
/*
 * Abstract class to generate emotional parameters
 * Emotions derived form this class are:
 * 	-EmotionMovementParameter: parameters to change the movement
 */
public:
	EmotionParameter();
	virtual ~EmotionParameter();
	virtual EmotionParameter * copyEmotionParameter() = 0;
	/*
	 * This message should be in JSON format
	 */
	virtual std::string generateMessage() = 0;
};
#endif // !defined(EMOTIONPARAMETER_H_)
