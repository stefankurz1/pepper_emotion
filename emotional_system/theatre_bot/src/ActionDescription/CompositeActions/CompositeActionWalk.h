/*
 * CompositeActionWalk.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef COMPOSITEACTIONWALK_H_
#define COMPOSITEACTIONWALK_H_

#include "../CompositeActionDescription.h"
#include "../SimpleActions/SimpleActionMoveBody.h"
#include "../SimpleActions/SimpleActionMoveTorso.h"
#include "../SimpleActions/SimpleActionOscillateShoulder.h"

class CompositeActionWalk : public CompositeActionDescription {
public:
	CompositeActionWalk();
	virtual ~CompositeActionWalk();
	std::string getActionName();
private:
	bool MandatoryParameterVerification(Json::Value parameter);
	bool OptionalParameterVerification(Json::Value parameter);

};

#endif /* COMPOSITEACTIONWALK_H_ */
