/*
 * CharacterMovementModification.h
 *
 *  Created on: Dec 18, 2014
 *      Author: julian
 */

#ifndef CHARACTERMOVEMENTMODIFICATION_H_
#define CHARACTERMOVEMENTMODIFICATION_H_

#include "../Parameter.h"

class CharacterMovementModification : public Parameter{
public:
	CharacterMovementModification();
	virtual ~CharacterMovementModification();

	void setBias(float bias);
	void setAmplitude(float amplitude);
	void setLongness(float longness);
	void setActionName(std::string action_name);

	std::string getActionName();
	float getBias();
	float getAmplitude();
	float getLongness();
private:
	std::string action_name;
	float bias;
	//
	float amplitude;
	//it changes the longness of the pattern
	float longness;
};

#endif /* CHARACTERMOVEMENTMODIFICATION_H_ */
