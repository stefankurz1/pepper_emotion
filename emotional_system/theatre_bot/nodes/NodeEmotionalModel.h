/*
 * NodeEmotionalModel.h
 *
 *  Created on: Mar 5, 2015
 *      Author: julian
 */

#ifndef NODEEMOTIONALMODEL_H_
#define NODEEMOTIONALMODEL_H_

#include "ros/ros.h"
#include "image_transport/image_transport.h"
#include "sensor_msgs/image_encodings.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/highgui/highgui.hpp"
#include "../src/EmotionalModel/EmotionalModel.h"

#include "theatre_bot/EmotionMessage.h"
#include "theatre_bot/EmotionsIntensities.h"
#include "sensor_msgs/Image.h"

class NodeEmotionalModel {
public:
	NodeEmotionalModel();
	virtual ~NodeEmotionalModel();
	void setEmotionPublisher(ros::Publisher * pub_emotion);
	void setEmotionIntensitiesPublisher(ros::Publisher * pub_emotion);
	void callbackImage(const sensor_msgs::Image::ConstPtr& image);
	void setCameraParameters(int image_width, int image_height);
	void initParameters();
	void activateDebug(std::string folder);
	void setProjectDirectory(std::string folder);
	void loadInformation();
private:
	float intensity;
	std::string emotion_name;
	bool first_iteration;
	float minimum_time_to_image;//this is the interval to get a new image
	ros::Time last_time;
	ros::Time current_time;
	ros::Duration difference;

	bool debug;
	std::string folder_debug;
	std::string folder_project;

	ros::Publisher * pub_emotion;
	ros::Publisher * pub_emotion_intensities;
	EmotionalModel emotional_model;
};

#endif /* NODEEMOTIONALMODEL_H_ */
