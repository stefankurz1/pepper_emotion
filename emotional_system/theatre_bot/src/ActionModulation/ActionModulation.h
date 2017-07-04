/*
 * ActionModulation.h
 *
 *  Created on: Dec 16, 2014
 *      Author: julian
 *
 *      This action modulate the emotion parameters
 */

#ifndef ACTIONMODULATION_H_
#define ACTIONMODULATION_H_

#include <typeinfo>
#include <cmath>
#include <sstream>

#include "../ContextDescription/SimpleContextDescription.h"
#include "../ContextDescription/CompositeContextDescription.h"
#include "../Parameters/EmotionalParameters/EmotionMovementParameter.h"
#include "../LoadInformation/CharacterPaceLoad.h"

class ActionModulation {
public:
	ActionModulation();
	virtual ~ActionModulation();
	void actionModulation(AbstractContextDescription * context, std::string emotion, float intensity);
	void setPathCharacterModifications(std::string path);
	void loadCharacterModification();
private:
	std::string path_name;
	std::map<std::string, CharacterEmotionModification *> modifications_available;
	/*
	 * This method modifies the parameters and save the changes in the string.
	 * This method should not modify save the changes in the parameters!
	 */
	void modifyParameters(SimpleContextDescription* simple_context, std::string emotion, float intensity);
	/*
	 * This method modulates the parameters that are related to movement
	 * This method should not modify save the changes in the parameters!
	 */
	std::string modifyMovementParameters(EmotionMovementParameter * emotion_parameter, std::string emotion, float modifier, float reference);
	std::string modifyMovementParameters(EmotionMovementParameter * emotion_parameter, std::string emotion, float modifier, float reference,CharacterMovementModification * temp_character, bool is_emotional);
	inline float absFloat(float num){return (num>=0.0)?num:-1.0*num;}
	float intensityFuction(float intensity);
};

#endif /* ACTIONMODULATION_H_ */
