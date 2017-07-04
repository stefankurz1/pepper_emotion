/*
 * SimpleActionMoveBody.h
 *
 *  Created on: Dec 5, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONMOVEBODY_H_
#define SIMPLEACTIONMOVEBODY_H_

#include "../SimpleActionDescription.h"

class SimpleActionMoveBody : public SimpleActionDescription {
public:
	SimpleActionMoveBody();
	virtual ~SimpleActionMoveBody();
	bool ParametersVerification(Json::Value parameters);
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);
};

#endif /* SIMPLEACTIONMOVEBODY_H_ */
