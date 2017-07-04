/*
 * ParserConfigurationFiles.h
 *
 *  Created on: Mar 23, 2015
 *      Author: julian
 */

#ifndef PARSERCONFIGURATIONFILES_H_
#define PARSERCONFIGURATIONFILES_H_
#include <fstream>
#include <iostream>
#include <map>
#include "../json/json/json.h"
#include "../Parameters/ConfigurationParameters/AnalyzerParameters.h"
#include "../Parameters/ConfigurationParameters/ReactiveModelParameters.h"
#include "../WorldModelDescription/TheatrePlaces.h"
#include "../WorldModelDescription/MarkerPosition.h"

/*
 * This class load all the information concern the configuration files as:
 * 	-robot initial position in the scene
 * 	-places in the scene (this could be improved to other domains, because time constrains I will focus just on theatre )
 */
class ParserConfigurationFiles {
public:
	ParserConfigurationFiles();
	virtual ~ParserConfigurationFiles();
	void readRobotInitialPositionFile(std::string file, float *initial_position_x,float *initial_position_y, float *initial_position_z);
	std::vector<AnalyzerParameters> readAnalyzerParameters(std::string file);
	ReactiveModelParameters readReactiveModelParameters(std::string file);
	TheatrePlaces readSceneDescriptionFile(std::string file);
	std::map<int, MarkerPosition> readMarkersPositionDescriptionFile(std::string file);
private:
	TypeEmotionAnalyzer typeEmotionAnalyzer(std::string name);
};

#endif /* PARSERCONFIGURATIONFILES_H_ */
