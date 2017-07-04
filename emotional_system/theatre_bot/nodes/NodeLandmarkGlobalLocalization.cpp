/*
 * NodeLandmarkGlobalLocalization.cpp
 *
 *  Created on: Aug 18, 2015
 *      Author: julian
 */

#include "NodeLandmarkGlobalLocalization.h"

NodeLandmarkGlobalLocalization::NodeLandmarkGlobalLocalization() {
	this->listener_black_camera = 0;
	this->listener_blue_camera = 0;
	this->pub_global_position = 0;
	this->first_execution = true;
	this->time_to_wait = 0.1;
	this->difference_black_camera = 0.0;
	blue_camera_last_position_x = 0.0;
	blue_camera_last_position_y = 0.0;
	blue_camera_last_position_yaw_x = 0.0;
	blue_camera_last_position_yaw_y = 0.0;
	difference_blue_camera = 0.0;
	black_camera_last_position_x = 0.0;
	black_camera_last_position_y = 0.0;
	black_camera_last_position_yaw_x = 0.0;
	black_camera_last_position_yaw_y = 0.0;
}

NodeLandmarkGlobalLocalization::~NodeLandmarkGlobalLocalization() {
	// TODO Auto-generated destructor stub
}

void NodeLandmarkGlobalLocalization::isFirstExecution(){
	last_time = ros::Time::now();
	last_time_black_camera = last_time;
	last_time_blue_camera = last_time;
	first_execution = false;

}
void NodeLandmarkGlobalLocalization::callbackNewMarkerBlueCamera(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg){
	this->markers_info_blue_camera = msg->markers;
	if(first_execution){
		isFirstExecution();
	}else{
		difference_time_blue_camera = msg->header.stamp-last_time_blue_camera;
		last_time_blue_camera = msg->header.stamp;
		difference_blue_camera = static_cast<float>(difference_time_blue_camera.toSec());
	}
}
void NodeLandmarkGlobalLocalization::callbackNewMarkerBlackCamera(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg){
	this->markers_info_black_camera = msg->markers;
	if(first_execution){
		isFirstExecution();
	}else{
		difference_time_black_camera = msg->header.stamp-last_time_black_camera;
		last_time_black_camera = msg->header.stamp;
		difference_black_camera = static_cast<float>(difference_time_black_camera.toSec());
	}
}
void NodeLandmarkGlobalLocalization::setTransformListenerBlueCamera(tf::TransformListener *listener){
	this->listener_blue_camera = listener;
}
void NodeLandmarkGlobalLocalization::setTransformListenerBlackCamera(tf::TransformListener *listener){
	this->listener_black_camera = listener;
}

void NodeLandmarkGlobalLocalization::setPublisherGlobalPosition(ros::Publisher * pub){
	this->pub_global_position = pub;
}
/*
 * This method gets the markers information and it detects if the desire market is inside the list of markets detected.
 * If the marker is detected, then it is calculate the position respect the frame of reference.
 */
bool NodeLandmarkGlobalLocalization::getRobotPosition(ar_track_alvar_msgs::AlvarMarker marker, tf::TransformListener *listener, float *counter,float *positions_x,float *positions_y,float *positions_yaw_x,float *positions_yaw_y){
	if(marker.id == 3){
		try{
			geometry_msgs::PoseStamped temp_pose;
			geometry_msgs::PoseStamped base_pose;
			temp_pose.header = marker.header;
			temp_pose.pose = marker.pose.pose;
			listener->transformPose("scene",temp_pose,base_pose);
			tf::Quaternion q_t(base_pose.pose.orientation.x,base_pose.pose.orientation.y,base_pose.pose.orientation.z,base_pose.pose.orientation.w);
			tf::Matrix3x3 m(q_t);
			double roll, pitch, yaw;
			m.getRPY(roll, pitch, yaw);
			++*counter;
			//X
			*positions_x = base_pose.pose.position.x;
			//Y
			*positions_y = base_pose.pose.position.y;
			//Decomposition of the angle in two components x and y
			*positions_yaw_x = cosf(yaw);
			*positions_yaw_y = sinf(yaw);
			return true;
			//std::cout<<"Info camera x \n"<<position_robot<<std::endl;
		}catch(tf::TransformException& ex){
			ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
		}
	}
	return false;
}

/*
 * This method calculates the next possible position where the robot could be, this is done using the last and current image
 * It uses Kalman to make the prediction
 */
void calculatePossiblePosition(float time,float position_x,float position_y,float position_yaw_x,float position_yaw_y,float last_position_x,float last_position_y,float last_position_yaw_x,float last_position_yaw_y,
			float *possible_position_x,float *possible_position_y, float *possible_position_yaw){
	float velocity_x = (position_x-last_position_x)/time;
	float velocity_y = (position_y-last_position_y)/time;
	float position_yaw = atan2f(position_yaw_y,position_yaw_x);
	float last_position_yaw = atan2f(last_position_yaw_y,last_position_yaw_x);
	float velocity_yaw = (position_yaw-position_yaw)/time;
}

void NodeLandmarkGlobalLocalization::updatePosition(){
	difference_time = ros::Time::now() - last_time;
	float difference = static_cast<float>(difference_time.toSec());
	if(first_execution){
		isFirstExecution();
	}else if(difference>=time_to_wait){
		ar_track_alvar_msgs::AlvarMarker marker;
		theatre_bot::OdometriesTriskar message;
		float position_x = 0.0;
		float position_y = 0.0;
		float position_yaw_x = 0.0;
		float position_yaw_y = 0.0;
		float counter = 0.0;
		//Move over the markers detected by the blue camera
		for(int i=0;i<markers_info_blue_camera.size();++i){
			marker = this->markers_info_blue_camera[i];
			theatre_bot::OdometryTriskar odom;
			if (this->getRobotPosition(marker,listener_blue_camera,&counter,&position_x,&position_y,&position_yaw_x,&position_yaw_y)){
				odom.pose.position.x	= 	position_x;
				odom.pose.position.y	=	position_y;
				odom.pose.orientation	=	atan2f(position_yaw_y,position_yaw_x);
				//message.odometries.push_back(odom);
			}
		}
		markers_info_blue_camera.clear();
		//Move over the markers detected by the black camera
		for(int i=0;i<markers_info_black_camera.size();++i){
			marker = this->markers_info_black_camera[i];
			theatre_bot::OdometryTriskar odom;
			if(this->getRobotPosition(marker,listener_black_camera,&counter,&position_x,&position_y,&position_yaw_x,&position_yaw_y)){
				odom.pose.position.x	= 	position_x;
				odom.pose.position.y	=	position_y;
				odom.pose.orientation	=	atan2f(position_yaw_y,position_yaw_x);
				message.odometries.push_back(odom);
			}
		}
		markers_info_black_camera.clear();
		if(counter >0){
			message.header.stamp = ros::Time::now();
			pub_global_position->publish(message);
		}
		last_time = ros::Time::now();
	}
}

void NodeLandmarkGlobalLocalization::verifyAngle(float *angle){
	if(*angle>M_PI){
		*angle= *angle-2.0*M_PI;
	}else if(*angle<-M_PI){
		*angle = *angle+2.0*M_PI;
	}
}

int main(int argc, char **argv){
	ros::init(argc,argv, "landmark_global_position_node");
	ros::NodeHandle n;
	NodeLandmarkGlobalLocalization node;
	if(n.hasParam("project_directory")){
		std::string project_path;
		//TODO load the objects ID
	}
	tf::TransformListener listener_blue(ros::Duration(10));
	node.setTransformListenerBlueCamera(&listener_blue);
	tf::TransformListener listener_black(ros::Duration(10));
	node.setTransformListenerBlackCamera(&listener_black);
	ros::Publisher pub_global_position = n.advertise<theatre_bot::OdometriesTriskar>("global_position_landmark", 1);
	node.setPublisherGlobalPosition(&pub_global_position);
	ros::Subscriber sub_ar_pose_blue = n.subscribe("/detection_outside_blue/ar_pose_marker", 1, &NodeLandmarkGlobalLocalization::callbackNewMarkerBlueCamera, &node);
	ros::Subscriber sub_ar_pose_black = n.subscribe("/detection_outside_black/ar_pose_marker", 1, &NodeLandmarkGlobalLocalization::callbackNewMarkerBlackCamera, &node);
	while(ros::ok()){
		node.updatePosition();
		ros::spinOnce();
	}
}
