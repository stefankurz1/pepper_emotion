/*
 * SimpleActionSpeak.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONSPEAK_H_
#define SIMPLEACTIONSPEAK_H_

#include "../SimpleActionDescription.h"
#include "../../ContextDescription/SimpleContextDescription.h"

class SimpleActionSpeak : public SimpleActionDescription{
public:
	SimpleActionSpeak();
	virtual ~SimpleActionSpeak();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONSPEAK_H_ */
