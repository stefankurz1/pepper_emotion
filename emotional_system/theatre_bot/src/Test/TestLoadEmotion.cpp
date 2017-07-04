/*
 * TestLoadEmotion.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#define DEBUG_C_PLUS_PLUS

#include <typeinfo>
#include "../Parameters/Parameter.h"
#include "../Parameters/EmotionalParameters/EmotionMovementParameter.h"
#include "../EmotionDescription/ActionChanges.h"
#include "../EmotionDescription/EmotionProfile.h"
#include "../LoadInformation/EmotionalLoad.h"
#include "../Parsers/ParserAction.h"
#include "../ActionModulation/ActionAddition.h"
#include "../ActionDescription/SimpleActions/SimpleActionDoNothing.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionMoveTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateBody.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateShoulder.h"
#include "../ActionDescription/SimpleActions/SimpleActionOscillateTorso.h"
#include "../ActionDescription/SimpleActions/SimpleActionSpeak.h"
#include "../ActionDescription/CompositeActions/CompositeActionWalk.h"
#include "../ActionModulation/ActionModulationSubSystem.h"
#include "../LoadInformation/CharacterPaceLoad.h"

void testActionChanges();
void testLoadEmotions();
void testFindSubString();
void testParserActions();
void testActionAddition();
void testActionSubSystem();
void testActionSubSystemActionModulation();
void testCharacterEmotionDescription();
void printContext(AbstractContextDescription *context);
std::map<std::string,AbstractActionDescription * > loadAvailableAction();

int main(){
	testActionSubSystemActionModulation();
	//testCharacterEmotionDescription();
	//testActionSubSystem();
	//testActionAddition();
	//testParserActions();
	//testFindSubString();
	//testLoadEmotions();
	//testActionChanges();
	return 0;
}

void testActionSubSystemActionModulation(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string path_name_character = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.setPathCharacterPace(path_name_character);
		action_sub_system.loadInformation();
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion"<<std::endl;
		std::vector<std::string> list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body emotion"<<std::endl;
		list = action_sub_system.emotionSynchronization("move_body");
		for(int i=0 ; i < list.size();i++){
			std::cout<<" - "<<list.at(i);
		}
		std::cout<<std::endl;
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action oscilalte_body"<<std::endl;
		action_sub_system.actionSynchronization("oscillate_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_torso");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("speak");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing intensity happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",0.5);
		std::cout<<"Testing emotion sad"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing emotion and intensity content"<<std::endl;
		action_sub_system.callBackNewEmotion("content",0.5);
		file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
		std::ifstream test2(file.c_str(), std::ifstream::binary);
		std::string message2((std::istreambuf_iterator<char>(test2)), std::istreambuf_iterator<char>());
		std::cout<<"Testing action message2"<<std::endl;
		action_sub_system.callBackNewAction(message2);
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("move_body");
		std::cout<<"----------------------"<<std::endl;
		std::cout<<"Testing end action move_body"<<std::endl;
		action_sub_system.actionSynchronization("speak");
	}
}

void testActionSubSystem(){
	ActionModulationSubSystem action_sub_system;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_sub_system.setPathEmotion(path_name);
		action_sub_system.loadInformation();
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message);
		std::cout<<"Testing emotion happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",1);
		std::cout<<"Testing intensity happy"<<std::endl;
		action_sub_system.callBackNewEmotion("happy",0.5);
		std::cout<<"Testing emotion sad"<<std::endl;
		action_sub_system.callBackNewEmotion("sad",1);
		std::cout<<"Testing emotion and intensity content"<<std::endl;
		action_sub_system.callBackNewEmotion("content",0.5);
		file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
		std::ifstream test2(file.c_str(), std::ifstream::binary);
		std::string message2((std::istreambuf_iterator<char>(test2)), std::istreambuf_iterator<char>());
		std::cout<<"Testing action message"<<std::endl;
		action_sub_system.callBackNewAction(message2);
	}
}

void testCharacterEmotionDescription(){
	std::string path_name = "/home/julian/workspace/TheatreBot/character_description_emotion/character_one";
	CharacterPaceLoad character_pace_load;
	character_pace_load.setDirectoryPath(path_name);
	character_pace_load.LoadInformation();
	std::map<std::string, CharacterEmotionModification *> temp = character_pace_load.getCharacterMovementInformation();
	std::cout<<"aaa"<<std::endl;
	for(std::map<std::string, CharacterEmotionModification *>::iterator it = temp.begin(); it != temp.end(); ++it){
		delete it->second;
	}
}

void testActionAddition(){
	ActionAddition action_addition;
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		action_addition.setPathName(path_name);
		action_addition.loadEmotions();
		action_addition.loadEmotions();
		AbstractContextDescription *context = action_addition.addAdditionalActions(message,"happy");
		printContext(context);
		std::cout<<"Ready"<<std::endl;
		if (test.good()) {
			std::cout<<"So far so good"<<std::endl;
			action_addition.changeEmotionalAction(&context,"sad");
			std::cout<<"New context"<<std::endl;
			printContext(context);
		}
		delete context;
	}
}
void testParserActions(){
	ParserAction  parserAction;
	std::map<std::string,AbstractActionDescription * >  actions = loadAvailableAction();
	parserAction.setActionsAvailable(&actions);
	/*std::string message1 = "{\"type\": \"simple_action\","
	"\"name\": \"move_body\","
	"\"parameters\":"
	"["
	"		{"
	"			\"type\"		:	\"mandatory_parameter\","
	"			\"name\"		:	\"parameter_point\","
	"			\"pose\" 		:	[0,0,0,1],"
	"			\"point\" 	:	[0,0,0]"
	"		}"
	"]"
	"}";*/
	//std::string file = "/media/julian/Julian/workspace-cpp/TheatreBot/action_description_test/abstract_action_speak_walk_parallel.json";
	//std::string file = "/media/julian/Julian/workspace-cpp/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	std::string file = "/home/julian/workspace/TheatreBot/action_description_test/abstract_action_speak_walk_sequential.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/simple_action_point.json";
	//std::string file = "/home/julian/workspace/TheatreBot/action_description_test/walk_action_point.json";
	std::ifstream test(file.c_str(), std::ifstream::binary);
	std::cout<<"Ready"<<std::endl;
	if (test.good()) {
		std::cout<<"So far so good"<<std::endl;
		std::string message((std::istreambuf_iterator<char>(test)), std::istreambuf_iterator<char>());
		AbstractContextDescription *context  = parserAction.parser(message);
		printContext(context);
		delete context;
	}
	for(std::map<std::string,AbstractActionDescription *>::iterator it = actions.begin();
			it !=actions.end();++it){
		delete it->second;
	}
	//std::cout<<message<<std::endl;
}


void printContext(AbstractContextDescription *context){
	if(context!=0){
		std::cout<<"context name: "<<typeid(*context).name()<<std::endl;
		if(typeid(*context).name()==typeid(CompositeContextDescription).name()){
			CompositeContextDescription * temp_context = static_cast<CompositeContextDescription *>(context);
			std::cout<<"*****************"<<std::endl;
			std::cout<<"Context-action synch: "<<temp_context->getActionsSynch()<<", type: "<<temp_context->getContextType()
					<<", emotion synch:"<<temp_context->getEmotionalSynch()<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::vector<AbstractContextDescription *> temp_sub_context = temp_context->getSubContext();
			std::cout<<"---------------"<<std::endl;
			for(std::vector<AbstractContextDescription *>::iterator it = temp_sub_context.begin();
					it != temp_sub_context.end(); ++it){
					printContext(*it);
				std::cout<<"---------------"<<std::endl;
			}
			std::cout<<"*****************"<<std::endl;
		}else if(typeid(*context).name()==typeid(SimpleContextDescription).name()){
			SimpleContextDescription * temp_context = static_cast<SimpleContextDescription *>(context);
			std::cout<<"Action - name: "<<temp_context->getActionName()<<", emotional "<<temp_context->getIsEmotional()<<", parameters: "<<temp_context->getActionParameters()
					<<", primary: "<<temp_context->getIsPrimaryContext()<<std::endl;
			std::vector<EmotionParameter *> temp_pameter_emotion = temp_context->getEmotionChanges().getVectorParameters();
			for(std::vector<EmotionParameter *>::iterator it_emotion = temp_pameter_emotion.begin();
					it_emotion != temp_pameter_emotion.end(); ++it_emotion){
				EmotionMovementParameter *temp_movement = static_cast<EmotionMovementParameter *>((*it_emotion));
				std::cout<<"Parameter timing "<<temp_movement->getEmotionParameterTime()<<" parameter spacing "<<temp_movement->getEmotionParameterSpacing()<<std::endl;
			}
		}
	}
}

std::map<std::string,AbstractActionDescription * > loadAvailableAction(){

	std::map<std::string,AbstractActionDescription * > actions;
	SimpleActionDoNothing *action_do_nothing = new SimpleActionDoNothing;
	actions[action_do_nothing->getActionName()] = action_do_nothing;
	SimpleActionMoveBody *action_move_body = new SimpleActionMoveBody;
	actions[action_move_body->getActionName()] = action_move_body;
	SimpleActionMoveShoulder *action_move_shoulder = new SimpleActionMoveShoulder;
	actions[action_move_shoulder->getActionName()] = action_move_shoulder;
	SimpleActionMoveTorso *action_move_torso = new SimpleActionMoveTorso;
	actions[action_move_torso->getActionName()] = action_move_torso;
	SimpleActionOscillateBody *action_oscillate_body = new SimpleActionOscillateBody;
	actions[action_oscillate_body->getActionName()] = action_oscillate_body;
	SimpleActionOscillateShoulder *action_oscillate_shoulder = new SimpleActionOscillateShoulder;
	actions[action_oscillate_shoulder->getActionName()] = action_oscillate_shoulder;
	SimpleActionOscillateTorso *action_oscillate_torso = new SimpleActionOscillateTorso;
	actions[action_oscillate_torso->getActionName()] = action_oscillate_torso;
	SimpleActionSpeak *action_speak = new SimpleActionSpeak;
	actions[action_speak->getActionName()] = action_speak;
	CompositeActionWalk *action_walk = new CompositeActionWalk;
	actions[action_walk->getActionName()] = action_walk;

	return actions;
}

void testFindSubString(){
	std::string temp = "parameter_point_body";
	int occurence = temp.find("__bod");
	std::cout<<occurence<<" - "<<temp.size()<<std::endl;
	std::string temp2 = temp.substr(0,occurence);
	std::cout<<"result: "<<temp2<<std::endl;
}
//Test load of emotions
void testLoadEmotions(){
	std::string path_name = "/home/julian/workspace/TheatreBot/emotion_profile";
	EmotionalLoad emotion_load;
	emotion_load.setDirectoryPath(path_name);
	emotion_load.LoadInformation();
	std::map<string, EmotionProfile *> emotions_available = emotion_load.getEmotionsAvailable();
	std::cout<<"Finish to load, the actions loaded are:"<<std::endl;
	for(std::map<string, EmotionProfile *>::iterator it = emotions_available.begin(); it != emotions_available.end();
			it++){
		std::cout<<"Emotion: "<<it->first<<std::endl;
		std::cout<<"Info Profile, Emotion: "<<it->second->getEmotionProfileEmotion()<<
				" Action: "<<it->second->getEmotionProfileAction()<<" ??? "<<it->second->getEmotionProfileName()<<std::endl;
		std::vector<ActionChanges *> temp = it->second->getActionChanges();
		for(std::vector<ActionChanges *>::iterator it_t = temp.begin();
				it_t != temp.end(); ++it_t){
			std::cout<<"Action changes: "<<(*it_t)->getActionThatModyfies()<<std::endl;
		}
		delete it->second;
	}
}

//Test the creation and delete of emotion profile
void testActionChanges(){
	EmotionProfile * emotion = new EmotionProfile();
	ActionChanges * action = new ActionChanges();
	EmotionMovementParameter *test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	test = new EmotionMovementParameter();
	action->addEmotionParameter(test);
	emotion->addActionChanges(action);
	action = new ActionChanges();
	test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		test = new EmotionMovementParameter();
		action->addEmotionParameter(test);
		emotion->addActionChanges(action);
	delete emotion;
}
