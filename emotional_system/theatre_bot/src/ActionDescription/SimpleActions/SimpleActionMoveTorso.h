/*
 * SimpleActionMoveTorso.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONMOVETORSO_H_
#define SIMPLEACTIONMOVETORSO_H_

#include "../SimpleActionDescription.h"

class SimpleActionMoveTorso : public SimpleActionDescription{
public:
	SimpleActionMoveTorso();
	virtual ~SimpleActionMoveTorso();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONMOVETORSO_H_ */
