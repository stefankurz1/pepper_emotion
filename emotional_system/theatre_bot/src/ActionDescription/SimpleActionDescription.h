///////////////////////////////////////////////////////////
//  SimpleActionDescription.h
//  Implementation of the Class SimpleActionDescription
//  Created on:      04-dic-2014 04:40:57 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(SIMPLEACTIONDESCRIPTION_H_)
#define SIMPLEACTIONDESCRIPTION_H_

#include "AbstractActionDescription.h"

/**
 * it has to verify that the parameters works and generate the simple action
 * context
 */
class SimpleActionDescription : public AbstractActionDescription
{

public:
	SimpleActionDescription();
	virtual ~SimpleActionDescription();
	/*
	 * parameter: the parameter that should be verified by the class
	 * name_parameter: the name of the parameter
	 * type_parameter: check if the parameter is mandatory or optional
	 */
	bool ParametersVerification(Json::Value parameter, std::string name_parameter, std::string type_parameter);
	AbstractContextDescription * analyze();
	bool getIsPrimary();
protected:
	virtual bool MandatoryParameterVerification(Json::Value parameter) = 0;
	virtual bool OptionalParameterVerification(Json::Value parameter) = 0;
	std::string parameter_message;

};
#endif // !defined(SIMPLEACTIONDESCRIPTION_H_)
