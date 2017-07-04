/*
 * SimpleActionOscillateTorso.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONOSCILLATETORSO_H_
#define SIMPLEACTIONOSCILLATETORSO_H_

#include "../SimpleActionDescription.h"

class SimpleActionOscillateTorso : public SimpleActionDescription{
public:
	SimpleActionOscillateTorso();
	virtual ~SimpleActionOscillateTorso();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONOSCILLATETORSO_H_ */
