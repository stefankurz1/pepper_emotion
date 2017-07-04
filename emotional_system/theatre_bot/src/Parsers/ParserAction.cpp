/*
 * ParserAction.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: julian
 */

#include "ParserAction.h"


//I need the action available in the system
ParserAction::ParserAction() {
	actions_available = 0;

}

ParserAction::~ParserAction() {
	// TODO Auto-generated destructor stub
}


AbstractContextDescription * ParserAction::parserAction(Json::Value action, AbstractContextDescription * predecessor){
	AbstractContextDescription * temp_context = 0;
	std::string name_action = action.get("name","UTF-8").asString();
	std::map<std::string,AbstractActionDescription *>::iterator temp_action = (*actions_available).find(name_action);
	if(temp_action != actions_available->end()){
		temp_action->second->setIsPrimary(action.get("is_primary","UTF-8").asString().compare("yes")==0?true:false);
		Json::Value temp_parameters = action.get("parameters","UTF-8");
		if(!temp_parameters.isNull() && temp_action->second->ParametersVerification(temp_parameters)){
			temp_context = temp_action->second->analyze();
			temp_context->setPredecessor(predecessor);
		}
	}
	return temp_context;
}

void ParserAction::parserContext(Json::Value context, CompositeContextDescription * predecessor, bool is_sequential){
	Json::Value action_values = context.get("actions","UTF-8");
	Json::Value temp;
	AbstractContextDescription * temp_context;
	if(!action_values.isNull()){
		for(unsigned int i=0; i<action_values.size();i++){
			temp = action_values.get(i,"UTF-8");
			if(temp.isObject()){
				temp_context = this->parser(temp, predecessor);
				if(temp_context!=0){
					if(is_sequential){
						temp_context->setIsPrimaryContext(true);
					}
					predecessor->addNextContext(temp_context);
				}else{//TODO add throw telling why is the problem
					for(std::vector<AbstractContextDescription*>::iterator it = predecessor->getSubContext().begin();
							it != predecessor->getSubContext().end(); ++it){
						delete *it;
					}
					return;
				}

			}else{//TODO add throw telling why is the problem
				for(std::vector<AbstractContextDescription*>::iterator it = predecessor->getSubContext().begin();
						it != predecessor->getSubContext().end(); ++it){
					delete *it;
				}
				return;
			}
		}
	}
}
AbstractContextDescription * ParserAction::parserParallelContext(Json::Value context, AbstractContextDescription * predecessor){
	//Get the parallel info
	CompositeContextDescription * temp_context = new CompositeContextDescription;
	temp_context->setPredecessor(predecessor);
	temp_context->setContextType(ParallelContext);
	temp_context->setEmotionalSynch(context.get("emotion_synch","UTF-8").asString().compare("yes")==0?true:false);
	temp_context->setIsPrimaryContext(context.get("is_primary","UTF-8").asString().compare("yes")==0?true:false);
	temp_context->setActionsSynch(context.get("action_synch","UTF-8").asString().compare("yes")==0?true:false);
	this->parserContext(context,temp_context, false);
	if(temp_context->getNumberOfContext()==0){
		delete temp_context;
		return 0;
	}
	return temp_context;
}
AbstractContextDescription * ParserAction::parserSequentialContext(Json::Value context, AbstractContextDescription * predecessor){
	//Get serial info
	CompositeContextDescription * temp_context = new CompositeContextDescription;
	temp_context->setPredecessor(predecessor);
	temp_context->setContextType(SequentialContext);
	temp_context->setIsPrimaryContext(context.get("is_primary","UTF-8").asString().compare("yes")==0?true:false);
	this->parserContext(context,temp_context, true);
	if(temp_context->getNumberOfContext()==0){
		delete temp_context;
		return 0;
	}
	return temp_context;
}

AbstractContextDescription * ParserAction::parser(Json::Value root, AbstractContextDescription * predecessor){
	/*
	 * Get what kind of information is:
	 * 	-simple_action
	 * 	-composite_action
	 * 	-parallel_context
	 * 	-serial_context
	 */
	Json::Value temp;
	std::string type_action = root.get("type","UTF-8").asString();
	if(type_action.compare("simple_action")==0){
		return this->parserAction(root,predecessor);
	}else if(type_action.compare("composite_action")==0){
		return this->parserAction(root,predecessor);
	}else if(type_action.compare("parallel_context")==0){
		return this->parserParallelContext(root,predecessor);
	}else if(type_action.compare("serial_context")==0){
		return this->parserSequentialContext(root,predecessor);
	}
	return 0;
}

AbstractContextDescription * ParserAction::parser(std::string message){
	if(actions_available != 0){
		Json::Reader reader;
		Json::Value root, tempValue;
		//Parser the string with jsoncpp
		bool parsingSuccessful = reader.parse(message,root,false);
		if (!parsingSuccessful) {
			std::cout<<"Error"<<std::endl;
			return 0;
		}
		if(root.isNull()){
			return 0;
		}
		return this->parser(root, 0);
	}
	return 0;
}


void ParserAction::setActionsAvailable(std::map <std::string,AbstractActionDescription *> * actions_available){
	this->actions_available = actions_available;
}
