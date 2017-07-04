/*
 * CharacterPaceLoad.h
 *
 *  Created on: Dec 18, 2014
 *      Author: julian
 *
 *      This class load all the information form the whole files, this is used for the modulation system
 */

#ifndef CHARACTERPACELOAD_H_
#define CHARACTERPACELOAD_H_

#include "Load.h"

#include "../Parameters/CharacterParameters/CharacterEmotionModification.h"

class CharacterPaceLoad: public Load {
public:
	CharacterPaceLoad();
	virtual ~CharacterPaceLoad();
	void LoadInformation();
	void LoadSpecificInformation(std::string file);
	std::map<std::string, CharacterEmotionModification *> getCharacterMovementInformation();
private:
	std::map<std::string, CharacterEmotionModification *> character_emotion_information;
};

#endif /* CHARACTERPACELOAD_H_ */
