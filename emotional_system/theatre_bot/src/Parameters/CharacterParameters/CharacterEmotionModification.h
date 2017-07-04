/*
 * CharacterEmotionModification.h
 *
 *  Created on: Dec 19, 2014
 *      Author: julian
 */

#ifndef CHARACTEREMOTIONMODIFICATION_H_
#define CHARACTEREMOTIONMODIFICATION_H_

#include <iostream>
#include <vector>
#include <map>

#include "CharacterMovementModification.h"

class CharacterEmotionModification {
public:
	CharacterEmotionModification();
	virtual ~CharacterEmotionModification();

	std::map<std::string,CharacterMovementModification *> * getEmotionModification();
	void setEmotionModification(std::vector<CharacterMovementModification *>  character_emotion_modification);
	std::string getEmotionName();
	void setEmotionName(std::string emotion_name);
	void cleanParameters();
	void addParameter(CharacterMovementModification * action_parameter);
private:
	std::string emotion_name;
	std::map<std::string,CharacterMovementModification *> character_emotion_modification;
};

#endif /* CHARACTEREMOTIONMODIFICATION_H_ */
