/*
 * NodeBodyActionExecution.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: julian
 */

#include "NodeBodyActionExecution.h"

NodeBodyActionExecution::NodeBodyActionExecution() {
	body_action = 0;
	pub_action_synch = 0;
	action_name_move = "move_body";
	action_name_oscillate = "oscillate_body";
	project_directory = "";
	initial_robot_position_x = 0.0;
	initial_robot_position_y = 0.0;
	initial_robot_position_theta = 0.0;
}

NodeBodyActionExecution::~NodeBodyActionExecution() {
	if(body_action != 0){
		delete body_action;
	}
}


void NodeBodyActionExecution::setProjectDirectory(std::string directory){
	this->project_directory = directory;
}

void NodeBodyActionExecution::callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	std::cout<<"Message "<<msg->coming_to<<" "<<msg->message<<" "<<msg->header.seq<<" "<<msg->header.stamp.toSec()<<std::endl;
	if(msg->coming_to.compare(this->action_name_move)==0){
		if(body_action != 0){
			//std::cout<<"body action is not empty"<<std::endl;
			if(!msg->stop_action){
				TypePosition type_position_parameter;
				boost::shared_ptr<Position> temp_parameter;
				if(this->parserJSON(msg->message,&temp_parameter,&type_position_parameter)){
					body_action->MoveBodyAction(temp_parameter,type_position_parameter);
				}
			}else{
				body_action->stopMoveBodyAction();
			}
		}
	}else if(msg->coming_to.compare(this->action_name_oscillate)==0){
		if(body_action != 0){
			if(!msg->stop_action){
				Amplitude amplitude;
				if (this->parserJSON(msg->message, &amplitude)) {
					body_action->OscillateBodyAction(amplitude);
				}
			}else{
				std::cout<<"Stopping oscillate"<<std::endl;
				body_action->stopOscillateBodyAction();
			}
		}
	}
}

void NodeBodyActionExecution::callbackNewInitParameters(const theatre_bot::InitParamVelPos::ConstPtr& msg){
	if(this->body_action != 0){
		this->body_action->setRobotInTheScene(msg->initial_x,msg->initial_y,0.0,msg->initial_theta);
		if(msg->angular_velocity != 0){
			//std::cout<<"Change angular velocity "<<msg->angular_velocity<<std::endl;
			this->body_action->setAngularVelocity(msg->angular_velocity);
		}
		if(msg->linear_velocity != 0){
			//std::cout<<"Change linear velocity "<<msg->linear_velocity<<std::endl;
			this->body_action->setLinearVelocity(msg->linear_velocity);
		}
	}
}

void NodeBodyActionExecution::callbackNewEmotionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg){
	std::cout<<"Message Emotional"<<msg->coming_to<<" "<<msg->message<<" "<<msg->header.seq<<" "<<msg->header.stamp.toSec()<<std::endl;
	if(this->body_action != 0){
		if(msg->coming_to.compare(this->action_name_move) == 0){
			if(msg->message.compare("emotion_synch") == 0){
				this->body_action->synchEmotionMove();
			}else{
				std::vector<EmotionMovementParameter> vector_x, vector_y,
						vector_z;
				bool repetition = false;
				bool done = emotion_parser.parse(msg->message, &vector_x,&vector_y,&vector_z,&repetition);
				if(done){
					this->body_action->setEmotionalMoveBody(vector_x,vector_y,vector_z,repetition);
				}

			}
		}else if(msg->coming_to.compare(this->action_name_oscillate) == 0){
			if(msg->message.compare("emotion_synch") == 0){
				std::cout<<"Synch oscillate body"<<std::endl;
				this->body_action->synchEmotionOscillate();
			}else{
				std::vector<EmotionMovementParameter> vector_x, vector_y,
						vector_z;
				bool repetition = false;
				bool done = emotion_parser.parse(msg->message, &vector_x,&vector_y,&vector_z,&repetition);
				if(done){
					std::cout<<"The parameter is correct and it has: "<<vector_x.size()<<std::endl;
					this->body_action->setEmotionalOscillateBody(vector_x,vector_y,vector_z,repetition);
				}
			}
		}
	}
}

void NodeBodyActionExecution::setPlatform(std::string platform, ros::NodeHandle *node){
	if(platform.compare("keepon")==0){
		body_action = new KeeponBody;
		body_action->setPublisherAction(node);
		body_action->setPublisherActionSynch(this->pub_action_synch);
		body_action->setActionMoveName(this->action_name_move);
		body_action->setActionOscillateName(this->action_name_oscillate);
		body_action->initSubscriberAction(node);
	}else if(platform.compare("triskar_small")==0){
		//std::cout<<"Setting triskar small"<<std::endl;
		body_action = new TriskarSmallBody;
		body_action->setPublisherAction(node);
		body_action->setPublisherActionSynch(this->pub_action_synch);
		body_action->setActionMoveName(this->action_name_move);
		body_action->setActionOscillateName(this->action_name_oscillate);
		body_action->initSubscriberAction(node);
		//std::cout<<"Places information "<<initial_robot_position_x<<" "<<initial_robot_position_y<<" "<<initial_robot_position_theta<<std::endl;
		body_action->setTheatrePlaceInformation(theatre_places);
		body_action->setRobotInTheScene(initial_robot_position_x,initial_robot_position_y,0.0,initial_robot_position_theta);
	}
}

void NodeBodyActionExecution::setPublisherActionSynch(ros::Publisher *pub_message){
	this->pub_action_synch = pub_message;
}

bool NodeBodyActionExecution::parserJSON(std::string parameter, boost::shared_ptr<Position> *result, TypePosition *type_position_parameter){
	Json::Reader reader;
	Json::Value root;
	bool parsing_successful = reader.parse(parameter, root, false);
	if(parsing_successful){
		Json::Value temp_info = root.get("name","UTF-8");
		if(temp_info.asString().compare("parameter_point") == 0){
			*type_position_parameter = PointPosition;
			boost::shared_ptr<Point> point_parameter(new Point);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("pose","UTF-8");
				if(!temp_info.isNull() && temp_info.isArray()){
					point_parameter->setHasPose(true);
					std::vector<float> numbers;
					for(int i = 0; i<temp_info.size(); ++i){
						numbers.push_back(temp_info[i].asFloat());
					}
					if(numbers.size()==4){
						point_parameter->setQuaternionX(numbers.at(0));
						point_parameter->setQuaternionY(numbers.at(1));
						point_parameter->setQuaternionZ(numbers.at(2));
						point_parameter->setQuaternionW(numbers.at(3));
					}
				}else{
					point_parameter->setHasPose(false);
				}
				*result = point_parameter;
				return true;
			}
		}else if(temp_info.asString().compare("parameter_landmark") == 0 ){
			*type_position_parameter = LandmarkPosition;
			boost::shared_ptr<Landmark> landmark_parameter(new Landmark);
			temp_info = root.get("landmark_id","UTF-8");
			if(!temp_info.isNull() && temp_info.isNumeric()){
				landmark_parameter->setIdLandmakr(temp_info.asInt());
				temp_info = root.get("landmark_type","UTF-8");
				if(!temp_info.isNull() && temp_info.isString()){
					if(temp_info.asString().compare("Person_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Person_Landmark);
					}else if(temp_info.asString().compare("Object_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Object_Landmark);
					}else if(temp_info.asString().compare("Place_Landmark") == 0){
						landmark_parameter->setTypeLandmark(Place_Landmark);
					}
					temp_info = root.get("pose","UTF-8");
					if(!temp_info.isNull() && temp_info.isArray()){
						landmark_parameter->setHasPose(true);
						std::vector<float> numbers;
						for(int i = 0; i<temp_info.size(); ++i){
							numbers.push_back(temp_info[i].asFloat());
						}
						if(numbers.size()==4){
							landmark_parameter->setQuaternionX(numbers.at(0));
							landmark_parameter->setQuaternionY(numbers.at(1));
							landmark_parameter->setQuaternionZ(numbers.at(2));
							landmark_parameter->setQuaternionW(numbers.at(3));
						}
					}else{
						landmark_parameter->setHasPose(false);
					}
					*result = landmark_parameter;
					return true;
				}
			}
		}else if(temp_info.asString().compare("parameter_circle") == 0 ){
			*type_position_parameter = CirclePosition;
			boost::shared_ptr<Circle> point_parameter(new Circle);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("radio","UTF-8");
				if(!temp_info.isNull() && temp_info.isNumeric()){
					point_parameter->setRadio(temp_info.asFloat());
					temp_info = root.get("pose","UTF-8");
					if(!temp_info.isNull() && temp_info.isArray()){
						point_parameter->setHasPose(true);
						std::vector<float> numbers;
						for(int i = 0; i<temp_info.size(); ++i){
							numbers.push_back(temp_info[i].asFloat());
						}
						if(numbers.size()==4){
							point_parameter->setQuaternionX(numbers.at(0));
							point_parameter->setQuaternionY(numbers.at(1));
							point_parameter->setQuaternionZ(numbers.at(2));
							point_parameter->setQuaternionW(numbers.at(3));
						}
					}else{
						point_parameter->setHasPose(false);
					}
				}
				*result = point_parameter;
				return true;
			}
		}else if(temp_info.asString().compare("parameter_square") == 0 ){
			*type_position_parameter = SquarePosition;
			boost::shared_ptr<Square> point_parameter(new Square);
			temp_info = root.get("point","UTF-8");
			if(!temp_info.isNull() && temp_info.isArray()){
				std::vector<float> numbers;
				for(int i = 0; i<temp_info.size(); ++i){
					numbers.push_back(temp_info[i].asFloat());
				}
				if(numbers.size()==3){
					point_parameter->setX(numbers.at(0));
					point_parameter->setY(numbers.at(1));
					point_parameter->setZ(numbers.at(2));
				}
				temp_info = root.get("delta","UTF-8");
				if(!temp_info.isNull() && temp_info.isArray()){
					std::vector<float> delta;
					for(int i = 0; i<temp_info.size(); ++i){
						delta.push_back(temp_info[i].asFloat());
					}
					if(delta.size()==2){
						point_parameter->setDeltaX(delta.at(0));
						point_parameter->setDeltaY(delta.at(0));
						temp_info = root.get("pose","UTF-8");
						if(!temp_info.isNull() && temp_info.isArray()){
							point_parameter->setHasPose(true);
							std::vector<float> numbers;
							for(int i = 0; i<temp_info.size(); ++i){
								numbers.push_back(temp_info[i].asFloat());
							}
							if(numbers.size()==4){
								point_parameter->setQuaternionX(numbers.at(0));
								point_parameter->setQuaternionY(numbers.at(1));
								point_parameter->setQuaternionZ(numbers.at(2));
								point_parameter->setQuaternionW(numbers.at(3));
							}
						}else{
							point_parameter->setHasPose(false);
						}
					}
				}
				*result = point_parameter;
				return true;
			}
		}
	}
	return false;
}

//Json reader function
bool NodeBodyActionExecution::parserJSON(std::string parameter, Amplitude *result){
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

bool NodeBodyActionExecution::parserEmotionJSON(std::string parameter, std::vector<EmotionMovementParameter> *result){
	return true;
}

void NodeBodyActionExecution::loadInformation(){
	ParserConfigurationFiles temp_configuration;
	std::string file = project_directory +"/robot_configuration_files/scene_description.json";
	theatre_places = temp_configuration.readSceneDescriptionFile(file);
	//std::cout<<theatre_places.getMaximumLenghtX()<<" "<<theatre_places.getMaximumLenghtY()<<" "<<theatre_places.getNumberRectanglesX()<<" "<<theatre_places.getNumberRectanglesY()<<std::endl;
	file = project_directory +"/robot_configuration_files/robot_initial_position.json";
	temp_configuration.readRobotInitialPositionFile(file,&initial_robot_position_x,&initial_robot_position_y,&initial_robot_position_theta);
}

int main(int argc, char **argv){
	NodeBodyActionExecution node;
	std::string platform = "triskar_small";
	ros::init(argc, argv, "body_action_node");
	ros::NodeHandle n("/action_modulation");
	if(n.hasParam("desire_platform")){
		n.getParam("desire_platform",platform);
	}
	if(n.hasParam("project_directory")){
		std::string project_path;
		n.getParam("project_directory",project_path);
		node.setProjectDirectory(project_path);
		node.loadInformation();
	}
	ros::Subscriber sub = n.subscribe("change_action_parameters_body", 10, &NodeBodyActionExecution::callbackNewActionParameters, &node);
	ros::Subscriber sub_emotion = n.subscribe("change_emotion_parameters_body", 10, &NodeBodyActionExecution::callbackNewEmotionParameters, &node);
	ros::Subscriber sub_init_parameters = n.subscribe("change_init_parameters_body", 10, &NodeBodyActionExecution::callbackNewInitParameters, &node);
	ros::Publisher pub_action_synch = n.advertise<theatre_bot::ActionExecutionMessage>("action_execution_synch", 10);
	node.setPublisherActionSynch(&pub_action_synch);
	//The last thing to do
	node.setPlatform(platform,&n);
	ROS_INFO("body action node is ready");
	ros::spin();
	return 0;
}
