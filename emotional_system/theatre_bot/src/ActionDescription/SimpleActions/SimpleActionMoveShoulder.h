/*
 * SimpleActionMoveShoulder.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONMOVESHOULDER_H_
#define SIMPLEACTIONMOVESHOULDER_H_

#include "../SimpleActionDescription.h"

class SimpleActionMoveShoulder : public SimpleActionDescription{
public:
	SimpleActionMoveShoulder();
	virtual ~SimpleActionMoveShoulder();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONMOVESHOULDER_H_ */
