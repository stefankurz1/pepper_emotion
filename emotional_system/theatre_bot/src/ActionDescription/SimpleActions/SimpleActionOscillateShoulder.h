/*
 * SimpleActionOscillateShoulder.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONOSCILLATESHOULDER_H_
#define SIMPLEACTIONOSCILLATESHOULDER_H_

#include "../SimpleActionDescription.h"

class SimpleActionOscillateShoulder : public SimpleActionDescription{
public:
	SimpleActionOscillateShoulder();
	virtual ~SimpleActionOscillateShoulder();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONOSCILLATESHOULDER_H_ */
