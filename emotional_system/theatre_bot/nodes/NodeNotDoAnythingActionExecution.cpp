/*
 * NodeNotDoAnythingActionExecution.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#include "NodeNotDoAnythingActionExecution.h"

NodeNotDoAnythingActionExecution::NodeNotDoAnythingActionExecution() {
	pub_action_synch = 0;
	action_name = "do_nothing";
	time_to_wait = 0.0;
	emotional_time_to_wait = 0.0;
	repeat_emotional = false;
	is_executing = false;
	emotinal_messsage = false;
}

NodeNotDoAnythingActionExecution::~NodeNotDoAnythingActionExecution() {
	// TODO Auto-generated destructor stub
}

bool NodeNotDoAnythingActionExecution::getIsExecuting(){
	return is_executing;
}

void NodeNotDoAnythingActionExecution::isActionFinish(){
	current_time = ros::Time::now();
	difference = current_time - action_strated_at_time;
	if(difference.toSec()>=time_to_wait){
		is_executing = false;
		emotinal_messsage = false;
		//Send message
		theatre_bot::ActionExecutionMessage temp_message;
		temp_message.coming_from = action_name;
		temp_message.coming_to = "";
		temp_message.message = "action_finished";
		std::cout<<"Sending end message"<<std::endl;
		pub_action_synch->publish(temp_message);
	}
}

void NodeNotDoAnythingActionExecution::synchEmotion(){
	if(emotinal_messsage){
		current_time = ros::Time::now();
		difference = current_time - emotinal_strated_at_time;
		if(difference.toSec()>=emotional_time_to_wait){
			if(repeat_emotional){
				emotinal_strated_at_time = ros::Time::now();
			}else{
				emotinal_messsage = false;
			}
			//Send message
			theatre_bot::ActionExecutionMessage temp_message;
			temp_message.coming_from = action_name;
			temp_message.coming_to = "";
			temp_message.message = "emotion_synch";
			std::cout<<"Sending synch message"<<std::endl;
			pub_action_synch->publish(temp_message);
		}
	}
}

void NodeNotDoAnythingActionExecution::callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	if(msg->coming_to.compare("do_nothing") == 0){
		ROS_INFO("Processing message");
		Json::Reader reader;
		Json::Value root;
		bool parsing_successful = reader.parse(msg->message, root, false);
		if(parsing_successful){
			Json::Value temp_info = root.get("time","UTF-8");
			if(!temp_info.isNull() && temp_info.isNumeric()){
				time_to_wait = temp_info.asFloat();
				action_strated_at_time = ros::Time::now();
				temp_info = root.get("emotional_time","UTF-8");
				if(!temp_info.isNull() && temp_info.isNumeric()){
					emotional_time_to_wait = temp_info.asFloat();
					emotinal_strated_at_time = ros::Time::now();
					emotinal_messsage = true;
				}
				temp_info = root.get("repeat_emotional","UTF-8");
				if(!temp_info.isNull() && temp_info.isString()){
					repeat_emotional = (temp_info.asString().compare("yes") == 0)?true:false;
				}
				is_executing = true;
			}
		}
	}
}

void NodeNotDoAnythingActionExecution::setPublisherActionSynch(ros::Publisher *pub_message){
	pub_action_synch = pub_message;
}

int main(int argc, char **argv){
	NodeNotDoAnythingActionExecution node;
	//Init the node
	ros::init(argc, argv, "node_not_do_anything_execution");
	ros::NodeHandle n;
	//Topic change parameters
	ros::Subscriber sub = n.subscribe("change_action_parameters_do_nothing", 10, &NodeNotDoAnythingActionExecution::callbackNewActionParameters, &node);
	ros::Publisher pub_action_synch = n.advertise<theatre_bot::ActionExecutionMessage>("action_execution_synch", 10);
	node.setPublisherActionSynch(&pub_action_synch);
	//ros::spin();
	while(ros::ok()){
		if(node.getIsExecuting()){
			//Time for emotional synch
			node.synchEmotion();
			//Time for normal end
			node.isActionFinish();
		}
		ros::spinOnce();
	}
	return 0;
}
