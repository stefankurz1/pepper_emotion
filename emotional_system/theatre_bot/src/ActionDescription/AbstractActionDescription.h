///////////////////////////////////////////////////////////
//  AbstractActionDescription.h
//  Implementation of the Class AbstractActionDescription
//  Created on:      04-dic-2014 04:40:56 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(ABSTRACTACTIONDESCRIPTION_H_)
#define ABSTRACTACTIONDESCRIPTION_H_

#include <iostream>
#include "../ContextDescription/CompositeContextDescription.h"
#include "../ContextDescription/SimpleContextDescription.h"
#include "../json/json/json.h"

class AbstractActionDescription
{

public:
	AbstractActionDescription();
	virtual ~AbstractActionDescription();
	/*
	 * This method tells if the parameters are accepted or not by the action.
	 * T
	 */
	virtual AbstractContextDescription * analyze() = 0;
	bool ParametersVerification(Json::Value parameters);
	void setIsPrimary(bool is_primary);
	std::string getActionName();
protected:
	/*
	 * The content in the parameters is not going to be checked by this module
	 */
	virtual bool MandatoryParameterVerification(Json::Value parameter) = 0;
	virtual bool OptionalParameterVerification(Json::Value parameter) = 0;
	std::string action_name;
	bool is_primary;
};
#endif // !defined(ABSTRACTACTIONDESCRIPTION_H_)
