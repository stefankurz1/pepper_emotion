/*
 * SimpleActionDoNothing.h
 *
 *  Created on: Dec 9, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONDONOTHING_H_
#define SIMPLEACTIONDONOTHING_H_

#include "../SimpleActionDescription.h"

class SimpleActionDoNothing : public SimpleActionDescription {
public:
	SimpleActionDoNothing();
	virtual ~SimpleActionDoNothing();
	bool ParametersVerification(Json::Value parameters);
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONDONOTHING_H_ */
