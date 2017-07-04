/*
 * NodeTorsoActionExecution.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#include "NodeTorsoActionExecution.h"

int main(int argc, char **argv){
	NodeTorsoActionExecution node;
	//TODO load this from parameters
	std::string platform = "triskar_small";
	ros::init(argc, argv, "torso_action_node");
	ros::NodeHandle n("/action_modulation");
	if(n.hasParam("desire_platform")){
		n.getParam("desire_platform",platform);
	}
	ros::Subscriber sub = n.subscribe("change_action_parameters_torso", 10, &NodeTorsoActionExecution::callbackNewActionParameters, &node);
	ros::Subscriber sub_emotion = n.subscribe("change_emotion_parameters_torso", 10, &NodeTorsoActionExecution::callbackNewEmotionParameters, &node);
	ros::Publisher pub_action_synch = n.advertise<theatre_bot::ActionExecutionMessage>("action_execution_synch", 10);
	node.setPublisherActionSynch(&pub_action_synch);
	//The last thing to do
	node.setPlatform(platform,&n);
	ros::spin();
	return 0;
}

NodeTorsoActionExecution::NodeTorsoActionExecution() {
	platform = Unkown_Platform;
	action_name_move = "move_torso";
	action_name_oscillate = "oscillate_torso";
	pub_action_synch = 0;
	torso_action = 0;
}

NodeTorsoActionExecution::~NodeTorsoActionExecution() {
	if(torso_action!= 0){
		delete torso_action;
	}
}

void NodeTorsoActionExecution::setPlatform(std::string platform, ros::NodeHandle *node){
	if(platform.compare("keepon")==0){
		torso_action = new KeeponTorso;
		torso_action->setPublisherAction(node);
		torso_action->setPublisherActionSynch(this->pub_action_synch);
		torso_action->setActionMoveName(this->action_name_move);
		torso_action->setActionOscillateName(this->action_name_oscillate);
		torso_action->initSubscriberAction(node);
	}else if(platform.compare("triskar_small") == 0){
		torso_action = new TriskarSmallTorso;
		torso_action->setPublisherAction(node);
		torso_action->setActionMoveName(this->action_name_move);
		torso_action->setActionOscillateName(this->action_name_oscillate);
		torso_action->setPublisherActionSynch(this->pub_action_synch);
		torso_action->setPublisherActionSynch(this->pub_action_synch);
		torso_action->initSubscriberAction(node);
	}
}


void NodeTorsoActionExecution::callbackEmtyPlatform(Amplitude amplitude_parameter){
	//ROS_INFO("It works");
	//std::cout<<"Info: "<<amplitude_parameter.getDistanceX()<<", "<<amplitude_parameter.getDistanceY()<<", "<<amplitude_parameter.getDistanceZ()<<std::endl;
}

void NodeTorsoActionExecution::callbackNewActionParameters(
		const theatre_bot::ActionExecutionMessage::ConstPtr& msg) {
	//std::cout << "Info " << msg->coming_to << " " << msg->message << std::endl;
	if (msg->coming_to.compare(this->action_name_move) == 0) {
		if (!msg->stop_action) {
			//std::cout << "Information " << msg->coming_to << " " << msg->message
				//	<< std::endl;
			Amplitude parameter;
			if (this->parserJSON(msg->message, &parameter)) {
				if (torso_action != 0) {
					torso_action->MoveTorsoAction(parameter);
				} else {
					this->callbackEmtyPlatform(parameter);
				}
			}
		} else {
			if (torso_action != 0) {
				torso_action->stopMoveTorsoAction();
			}
		}
	} else if (msg->coming_to.compare(this->action_name_oscillate) == 0) {
		if (!msg->stop_action) {
			//std::cout << "Information " << msg->coming_to << " " << msg->message
					//<< std::endl;
			Amplitude parameter;
			if (this->parserJSON(msg->message, &parameter)) {
				if (torso_action != 0) {
					torso_action->OscillateTorsoAction(parameter);
				} else {
					this->callbackEmtyPlatform(parameter);
				}
			}
		} else {
			if (torso_action != 0) {
				torso_action->stopOscillateTorsoAction();
			}
		}
	}
}

void NodeTorsoActionExecution::callbackNewEmotionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	//std::cout<<"Message Emotional "<<msg->coming_to<<" "<<msg->message<<std::endl;
	if (this->torso_action != 0) {
		if (msg->coming_to.compare(this->action_name_move) == 0) {
			//std::cout << "Emotion move " << msg->message << std::endl;
			if (msg->message.compare("emotion_synch") == 0) {
				this->torso_action->synchEmotionMove();
			} else {
				std::vector<EmotionMovementParameter> vector_x, vector_y,
						vector_z;
				bool repetition = false;
				bool done = emotion_parser.parse(msg->message, &vector_x,
						&vector_y, &vector_z, &repetition);
				if (done) {
					//std::cout<<"Sending parameters"<<std::endl;
					//Set the parameters
					this->torso_action->setEmotionalMoveTorso(vector_x,
							vector_y, vector_z, repetition);
				}
			}

		} else if (msg->coming_to.compare(this->action_name_oscillate) == 0) {
			//std::cout << "Emotion oscillate 222" << msg->message << std::endl;
			if (msg->message.compare("emotion_synch") == 0) {
				this->torso_action->synchEmotionOscillate();
			} else {
				std::vector<EmotionMovementParameter> vector_x, vector_y,vector_z;
				bool repetition = false;
				bool done = emotion_parser.parse(msg->message, &vector_x,
						&vector_y, &vector_z, &repetition);
				if (done) {
					//std::cout << "The parameters is fine " << vector_x.size()
							//<< " " << vector_y.size() << std::endl;
					//Set the parameters
					this->torso_action->setEmotionalOscillateTorso(vector_x,
							vector_y, vector_z, repetition);
				}
			}
		}
	}
}


void NodeTorsoActionExecution::setPublisherActionSynch(ros::Publisher *pub_message){
	this->pub_action_synch = pub_message;
}

//Json reader function
bool NodeTorsoActionExecution::parserJSON(std::string parameter, Amplitude *result){
	Json::Reader reader;
	Json::Value root;
	bool parsing_successful = reader.parse(parameter, root, false);
	if(parsing_successful){
		Json::Value temp_info = root.get("name","UTF-8");
		if(temp_info.asString().compare("parameter_amplitude") == 0){
			temp_info = root.get("amplitude","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					result->setDistanceZ(numbers.at(2));
					result->setDistanceY(numbers.at(1));
					result->setDistanceX(numbers.at(0));
					return true;
				}
			}
		}
	}
	return false;
}

