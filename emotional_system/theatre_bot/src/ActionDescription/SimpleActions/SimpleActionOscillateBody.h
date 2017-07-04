/*
 * SimpleActionOscillateBody.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONOSCILLATEBODY_H_
#define SIMPLEACTIONOSCILLATEBODY_H_

#include "../SimpleActionDescription.h"

class SimpleActionOscillateBody : public SimpleActionDescription{
public:
	SimpleActionOscillateBody();
	virtual ~SimpleActionOscillateBody();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONOSCILLATEBODY_H_ */
