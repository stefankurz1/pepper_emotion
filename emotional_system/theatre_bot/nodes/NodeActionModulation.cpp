/*
 * NodeActionModulation.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: julian
 */


#include "NodeActionModulation.h"


NodeActionModulation::NodeActionModulation(){

}
NodeActionModulation::~NodeActionModulation(){

}


void NodeActionModulation::stopActions(std::vector<std::string> list){
	std::cout<<"actions to finish: ";
	//ROS_INFO("actions to finish: \n");
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
		//Here comes the messages to the action
		std::cout<<*it<<" "<<std::endl;
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.header.stamp = ros::Time::now();
		temp_message.coming_to = *it;
		temp_message.coming_from = "";
		temp_message.message = "stop";
		temp_message.stop_action = true;
		std::map<std::string,ros::Publisher *>::iterator pub = this->pub_action_parameter.find(*it);
		if(pub != this->pub_action_parameter.end()){
			//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
			pub->second->publish(temp_message);
		}
	}
	//std::cout<<std::endl;
}


std::map<std::string,std::string> NodeActionModulation::eliminateUnStopActions(std::map<std::string,std::string> list_message_actions,std::vector<std::string> list){
	std::map<std::string,std::string> result;
	for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
		std::map<std::string,string>::iterator it_hash = list_message_actions.find(*it);
		std::cout<<"Action to stop "<<*it<<std::endl;
		if(it_hash != list_message_actions.end()){
			std::cout<<"Action to send message "<<it_hash->first<<std::endl;
			result[it_hash->first] = it_hash->second;
		}
	}
	return result;
}

void NodeActionModulation::callbackActionExecutionSynch(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	std::cout<<"Synch "<<msg->coming_from<<": "<<msg->message<<std::endl;
	if(msg->message.compare("action_finished") == 0){
		std::cout<<"Clearing action list"<<std::endl;
		this->action_modulation_sub_system.clearListNewAction();
		//std::cout<<"Actions have cleared"<<std::endl;
		std::vector<std::string> list = this->action_modulation_sub_system.actionSynchronization(msg->coming_from);
		//std::cout<<"Action list size "<<list.size()<<std::endl;
		this->stopActions(list);
		std::map<std::string,std::string> list_message_actions = action_modulation_sub_system.getListNewAction();
		//list_message_actions = eliminateUnStopActions(list_message_actions,list);
		sendActionsInformation(list_message_actions);
		list_message_actions = action_modulation_sub_system.getListNewActionEmotional();
		//list_message_actions = eliminateUnStopActions(list_message_actions,list);
		sendActionsEmotionInformation(list_message_actions);
	}else if(msg->message.compare("emotion_synch") == 0){
		//TODO here it is diferent the stop, here it should be done through the emotional channel
		std::vector<std::string> list = this->action_modulation_sub_system.emotionSynchronization(msg->coming_from);
		for(std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it){
			//std::cout<<" Emotional synchronization "<<*it<<std::endl;
			theatre_bot::ActionExecutionMessage temp_message;
			temp_message.header.stamp = ros::Time::now();
			temp_message.coming_to = *it;
			temp_message.coming_from = "";
			temp_message.message = "emotion_synch";
			temp_message.stop_action = false;
			std::map<std::string,ros::Publisher *>::iterator pub = this->pub_emotion_parameter.find(temp_message.coming_to);
			if(pub != this->pub_emotion_parameter.end()){
				//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
				pub->second->publish(temp_message);
			}
		}
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.header.stamp = ros::Time::now();
		temp_message.coming_to = msg->coming_from;
		temp_message.coming_from = "";
		temp_message.message = "emotion_synch";
		temp_message.stop_action = false;
		std::map<std::string,ros::Publisher *>::iterator pub = this->pub_emotion_parameter.find(temp_message.coming_to);
		if(pub != this->pub_emotion_parameter.end()){
			//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
			pub->second->publish(temp_message);
		}
	}
}

void NodeActionModulation::setActionsParameter(std::map<std::string,ros::Publisher *> pub_actions_parameter){
	this->pub_action_parameter = pub_actions_parameter;
}


void NodeActionModulation::setEmotionParameter(std::map<std::string,ros::Publisher *> pub_emotion_parameter){
	this->pub_emotion_parameter = pub_emotion_parameter;
}
/*
 * when a change is done it should send a message to all the actions through the emotion channel
 */
void NodeActionModulation::callbackNewEmotion(const theatre_bot::EmotionMessage::ConstPtr& msg){
	std::string emotion = msg->emotion.data;
	float intensity = msg->intensity.data;
	ROS_INFO("Emotion %s, intensity %f", emotion.c_str(), intensity);
	action_modulation_sub_system.callBackNewEmotion(emotion,intensity);
	//stopActions
	this->stopActions(this->action_modulation_sub_system.actiosToStop());
	std::map<std::string,std::string> list_message_actions = action_modulation_sub_system.generateEmotionalParameterMessage();
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		ROS_INFO("Sending emotions %s %s", it->first.c_str(), it->second.c_str());
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.header.stamp = ros::Time::now();
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		std::map<std::string,ros::Publisher *>::iterator pub = this->pub_emotion_parameter.find(temp_message.coming_to);
		if(pub != this->pub_emotion_parameter.end()){
			//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
			pub->second->publish(temp_message);
		}
	}
}

void NodeActionModulation::sendActionsInformation(std::map<std::string,std::string> list_message_actions){
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the action channel
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.header.stamp = ros::Time::now();
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		std::map<std::string,ros::Publisher *>::iterator pub = this->pub_action_parameter.find(temp_message.coming_to);
		if(pub != this->pub_action_parameter.end()){
			//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
			pub->second->publish(temp_message);
		}
		ROS_INFO("Sending action parameters %s %s", it->first.c_str(), it->second.c_str());
	}
}

void NodeActionModulation::sendActionsEmotionInformation(std::map<std::string,std::string> list_message_actions){
	for(std::map<std::string,std::string>::iterator it = list_message_actions.begin();
			it != list_message_actions.end(); ++it){
		//The information should be send using the emotion channel
		ROS_INFO("Sending emotions %s %s", it->first.c_str(), it->second.c_str());
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.header.stamp = ros::Time::now();
		temp_message.coming_to = it->first;
		temp_message.coming_from = "";
		temp_message.message = it->second;
		temp_message.stop_action = false;
		std::map<std::string,ros::Publisher *>::iterator pub = this->pub_emotion_parameter.find(temp_message.coming_to);
		if(pub != this->pub_emotion_parameter.end()){
			//std::cout<<"Found a publisher for "<<temp_message.coming_to<<std::endl;
			pub->second->publish(temp_message);
		}
	}
}

bool NodeActionModulation::callbackNewAction(theatre_bot::ActionService::Request &req, theatre_bot::ActionService::Response &res){
	std::string desire_action = req.action;
	ROS_INFO("the action:-%s-", desire_action.c_str());
	action_modulation_sub_system.callBackNewAction(desire_action);
	//stopActions
	this->stopActions(this->action_modulation_sub_system.actiosToStop());
	//Get the action messages
	sendActionsInformation(action_modulation_sub_system.generateParameterMessage());
	sendActionsEmotionInformation(action_modulation_sub_system.generateEmotionalParameterMessage());
	res.response = "done";
	return true;
}

void NodeActionModulation::loadInformation(){
	action_modulation_sub_system.setPathEmotion(path_name_emotion);
	action_modulation_sub_system.setPathCharacterPace(path_name_character);
	action_modulation_sub_system.loadInformation();
	//Print the emotions
	std::vector<std::string> temp_list = action_modulation_sub_system.getEmotions();
	//std::string temp_string;
	//ROS_INFO("Emotions: ");
	std::cout<<"Emotions: "<<std::endl;
	for(std::vector<std::string>::iterator it = temp_list.begin() ; it != temp_list.end(); ++it){
		//temp_string = *it
		//ROS_INFO(" %s, ",it->c_str());
		std::cout<<*it<<", "<<std::endl;
	}
	//Print the actions
	temp_list = action_modulation_sub_system.getActions();
	//ROS_INFO("Actions: ");
	std::cout<<"Actions: "<<std::endl;
	for(std::vector<std::string>::iterator it = temp_list.begin() ; it != temp_list.end(); ++it){
		//ROS_INFO(" %s, ",it->c_str());
		std::cout<<*it<<", "<<std::endl;
	}
}

void NodeActionModulation::setPathEmotion(std::string path_emotion){
	this->path_name_emotion = path_emotion;
}

void NodeActionModulation::setPathCharacter(std::string path_character){
	this->path_name_character = path_character;
}

int main(int argc, char **argv){
	//Init the node
	ros::init(argc, argv, "action_modulation_sub_system");
	ros::NodeHandle n("/action_modulation");
	//Files with the specification
	if(!n.hasParam("directory_emotions")&&!n.hasParam("character_profile")){
		ROS_INFO("it is necessary to give the emotions' and character directory");
	}else{
		NodeActionModulation node;
		//Get the parameters
		std::string parameter_directory_emotions;
		std::string parameter_character_directory;
		//Get emotion directory
		n.getParam("directory_emotions",parameter_directory_emotions);
		n.getParam("character_profile",parameter_character_directory);
		node.setPathEmotion(parameter_directory_emotions);
		node.setPathCharacter(parameter_character_directory);
		node.loadInformation();
		//Topic emotion
		ros::Subscriber sub = n.subscribe("change_emotion", 10, &NodeActionModulation::callbackNewEmotion, &node);
		//Topic synch
		ros::Subscriber sub_synch = n.subscribe("action_execution_synch", 10, &NodeActionModulation::callbackActionExecutionSynch, &node);
		//Service new emotion
		ros::ServiceServer service = n.advertiseService("change_action",&NodeActionModulation::callbackNewAction,&node);
		//Publishes the new action parameters
		std::map<std::string,ros::Publisher *> pub_actions_parameter;
		ros::Publisher pub_action_parameter_do_nothing = n.advertise<theatre_bot::ActionExecutionMessage>("change_action_parameters_do_nothing", 10);
		pub_actions_parameter["do_nothing"] = &pub_action_parameter_do_nothing;
		ros::Publisher pub_action_parameter_torso = n.advertise<theatre_bot::ActionExecutionMessage>("change_action_parameters_torso", 10);
		pub_actions_parameter["move_torso"] = &pub_action_parameter_torso;
		pub_actions_parameter["oscillate_torso"] = &pub_action_parameter_torso;
		ros::Publisher pub_action_parameter_body = n.advertise<theatre_bot::ActionExecutionMessage>("change_action_parameters_body", 10);
		pub_actions_parameter["move_body"] = &pub_action_parameter_body;
		pub_actions_parameter["oscillate_body"] = &pub_action_parameter_body;
		ros::Publisher pub_action_parameter_shoulder = n.advertise<theatre_bot::ActionExecutionMessage>("change_action_parameters_shoulder", 10);
		pub_actions_parameter["move_shoulder"] = &pub_action_parameter_shoulder;
		pub_actions_parameter["oscillate_shoulder"] = &pub_action_parameter_shoulder;
		node.setActionsParameter(pub_actions_parameter);
		//Publishes the new emotion parameters
		std::map<std::string,ros::Publisher *> pub_emotions_parameter;
		ros::Publisher pub_emotion_parameter_torso = n.advertise<theatre_bot::ActionExecutionMessage>("change_emotion_parameters_torso", 10);
		pub_emotions_parameter["move_torso"] = &pub_emotion_parameter_torso;
		pub_emotions_parameter["oscillate_torso"] = &pub_emotion_parameter_torso;
		ros::Publisher pub_emotion_parameter_body = n.advertise<theatre_bot::ActionExecutionMessage>("change_emotion_parameters_body", 10);
		pub_emotions_parameter["move_body"] = &pub_emotion_parameter_body;
		pub_emotions_parameter["oscillate_body"] = &pub_emotion_parameter_body;
		ros::Publisher pub_emotion_parameter_shoulder = n.advertise<theatre_bot::ActionExecutionMessage>("change_emotion_parameters_shoulder", 10);
		pub_emotions_parameter["move_shoulder"] = &pub_emotion_parameter_shoulder;
		pub_emotions_parameter["oscillate_shoulder"] = &pub_emotion_parameter_shoulder;
		node.setEmotionParameter(pub_emotions_parameter);
		ROS_INFO("action modulation ready");
		ros::spin();

	}
	return 0;
}
