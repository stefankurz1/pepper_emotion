///////////////////////////////////////////////////////////
//  EmotionalLoad.h
//  Implementation of the Class EmotionalLoad
//  Created on:      04-dic-2014 04:42:19 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(EMOTIONALLOAD_H_)
#define EMOTIONALLOAD_H_


#include "Load.h"
#include "../EmotionDescription/EmotionProfile.h"
#include "../Parameters/EmotionalParameters/EmotionMovementParameter.h"

using std::string;

class EmotionalLoad : public Load
{

public:
	EmotionalLoad();
	virtual ~EmotionalLoad();
	void LoadInformation();
	std::map<string, EmotionProfile *>  getEmotionsAvailable();

private:
	bool has_suffix(const string& s, const string& suffix);
	EmotionType getEmotionType(std::string emotion_type);
	EmotionParameter* generateEmotionParameter(Json::Value info, EmotionType type_emotion);

	std::map<string, EmotionProfile *> emotions_available;
};
#endif // !defined(EMOTIONALLOAD_H_)
