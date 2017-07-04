/*
 * ParserActionParameters.h
 *
 *  Created on: Jan 21, 2015
 *      Author: julian
 */

#ifndef PARSERACTIONPARAMETERS_H_
#define PARSERACTIONPARAMETERS_H_

#include "../json/json/json.h"
#include "../Parameters/MovementParameters/TypeLandmark.h"
class ParserActionParameters {
public:
	ParserActionParameters();
	virtual ~ParserActionParameters();

	bool parser(std::string message);
private:
	TypeLandmark parseLandmark(Json::Value temp_info);
	std::vector<float> parseVector(Json::Value temp_info);
	float parseFloat(Json::Value temp_info);
	std::string parseString(Json::Value temp_info);
};

#endif /* PARSERACTIONPARAMETERS_H_ */
