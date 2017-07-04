/*
 * ParserAction.h
 *
 *  Created on: Dec 10, 2014
 *      Author: julian
 *
 *      This class parser an action from a string written in JSON
 */

#ifndef SRC_PARSERS_PARSERACTION_H_
#define SRC_PARSERS_PARSERACTION_H_

#include "../json/json/json.h"

//To verify the actions parameters
#include "../ActionDescription/SimpleActionDescription.h"
#include "../ActionDescription/CompositeActionDescription.h"
//To generate the context tree
#include "../ContextDescription/SimpleContextDescription.h"
#include "../ContextDescription/CompositeContextDescription.h"
//Simple actions description
#include "../ActionDescription/SimpleActions/SimpleActionDoNothing.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionSpeak.h"
//composite action description
#include "../ActionDescription/CompositeActions/CompositeActionWalk.h"

class ParserAction {
public:
	ParserAction();
	virtual ~ParserAction();
	AbstractContextDescription * parser(std::string message);
	void setActionsAvailable(std::map <std::string,AbstractActionDescription *> * actions_available);
private:
	AbstractContextDescription * parser(Json::Value root, AbstractContextDescription * predecessor);
	AbstractContextDescription * parserAction(Json::Value action, AbstractContextDescription * predecessor);
	void parserContext(Json::Value context, CompositeContextDescription * predecessor,bool is_sequential);
	AbstractContextDescription * parserParallelContext(Json::Value context, AbstractContextDescription * predecessor);
	AbstractContextDescription * parserSequentialContext(Json::Value context, AbstractContextDescription * predecessor);
	std::map <std::string,AbstractActionDescription *> * actions_available;
};

#endif /* SRC_PARSERS_PARSERACTION_H_ */
