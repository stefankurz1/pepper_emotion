/*
 * NodeEmotionalModel.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#include "NodeEmotionalModel.h"

NodeEmotionalModel::NodeEmotionalModel() {
	this->pub_emotion = 0;
	this->pub_emotion_intensities = 0;
	this->intensity = 0.0;
	this->emotion_name = "neutral";
	this->first_iteration = true;
	this->minimum_time_to_image = 0.1;
	this->emotional_model.setMinimumTimeToImage(minimum_time_to_image);
	this->debug = false;
	this->folder_debug = "";
}

NodeEmotionalModel::~NodeEmotionalModel() {
	// TODO Auto-generated destructor stub
}

void NodeEmotionalModel::activateDebug(std::string folder){
	this->folder_debug = folder;
	this->debug = true;
	this->emotional_model.activateDebug(folder);
}
void NodeEmotionalModel::setEmotionPublisher(ros::Publisher * pub_emotion){
	this->pub_emotion = pub_emotion;
}

void NodeEmotionalModel::setEmotionIntensitiesPublisher(ros::Publisher * pub_emotion){
	this->pub_emotion_intensities = pub_emotion;
}
void NodeEmotionalModel::setCameraParameters(int image_width, int image_height){
	emotional_model.setCameraParameters(image_width,image_height);
}

void NodeEmotionalModel::initParameters(){
	emotional_model.initParameters();
}

void NodeEmotionalModel::callbackImage(const sensor_msgs::Image::ConstPtr& image){
	  std::cout<<"Processing time "<<minimum_time_to_image<<std::endl;
	cv_bridge::CvImagePtr cv_ptr;
    try
    {
      current_time = ros::Time::now();
      if(!first_iteration){
    	  difference = current_time - last_time;
    	  if(difference.toSec()>minimum_time_to_image){
    		  theatre_bot::EmotionsIntensities message_intensities;
    	      cv_ptr = cv_bridge::toCvCopy(image, sensor_msgs::image_encodings::BGR8);
    	      cv::Mat gray_image;
      	  	  cv::cvtColor(cv_ptr->image,gray_image,CV_RGB2GRAY);
      	  	  if(debug){
      	  		  emotional_model.newImageDebug(gray_image ,&emotion_name,&intensity,static_cast<float>(difference.toSec()),&message_intensities.fear,&message_intensities.surprise,&message_intensities.relief,&message_intensities.interest);
          	  	  pub_emotion_intensities->publish(message_intensities);
      	  	  }else{
          	  	  emotional_model.newImage(gray_image,&emotion_name,&intensity,static_cast<float>(difference.toSec()));
      	  	  }
      	  	  theatre_bot::EmotionMessage tem_emotion_message;
      	  	  tem_emotion_message.emotion.data = "neutral";
      	  	  tem_emotion_message.intensity.data = intensity;
      	  	  pub_emotion->publish(tem_emotion_message);
      	      last_time = current_time;
    	  }
      }else{
    	  first_iteration = false;
          last_time = current_time;
      }
    }
    catch (cv_bridge::Exception& e)
    {
    	ROS_ERROR("cv_bridge exception: %s", e.what());
    	return;
    }catch (const std::exception& ex){
    	ROS_ERROR("error in the system: %s", ex.what());
    	//return;
    }
}


void NodeEmotionalModel::setProjectDirectory(std::string folder){
	this->folder_project = folder;
}


void NodeEmotionalModel::loadInformation(){
	std::string config_path;
	config_path = folder_project +"/robot_configuration_files/emotion_processing_parameters.json";
	this->emotional_model.readAnalyzerParameters(config_path);
	config_path = folder_project +"/robot_configuration_files/stimuli_system_parameters.json";
	this->emotional_model.readReactiveModelParameters(config_path);
	this->minimum_time_to_image = this->emotional_model.getMinimumTimeToImage();
}

int main(int argc, char **argv){
	NodeEmotionalModel node;
	//TODO get parameters
	ros::init(argc, argv, "emotion_model_sub_system");
	ros::NodeHandle n;
	//TODO get parameters
	node.setCameraParameters(640,480);
	node.initParameters();
	//Subscriber to world model
	//Subscriber to camera /usb_cam/image_rect
	//TODO it has to take this from parameters
	ros::Subscriber sub_camera = n.subscribe("/usb_cam/image_rect", 1, &NodeEmotionalModel::callbackImage, &node);
	//Publisher of emotion
	ros::Publisher pub_emotion = n.advertise<theatre_bot::EmotionMessage>("change_emotion", 10);
	ros::Publisher pub_emotion_intensities = n.advertise<theatre_bot::EmotionsIntensities>("emotions_intensities", 10);
	node.setEmotionPublisher(&pub_emotion);
	node.setEmotionIntensitiesPublisher(&pub_emotion_intensities);
	if(n.hasParam("debug_emotional_system")){
		std::string folder;
		n.getParam("debug_emotional_system",folder);
		node.activateDebug(folder);
	}
	if(n.hasParam("project_directory")){
		std::string project_path;
		n.getParam("project_directory",project_path);
		node.setProjectDirectory(project_path);
		node.loadInformation();
	}
	ros::spin();
	return 0;
}

