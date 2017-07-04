/*
 * NodeLandmarkLocalization.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: julian
 */

#include "NodeLandmarkLocalization.h"

NodeLandmarkLocalization::NodeLandmarkLocalization() {
	this->listener =  0;
	this->pub_odometry = 0;
	this->robot_initial_x = 0.0;
	this->robot_initial_y = 0.0;
	this->robot_initial_yaw = 0.0;
	this->robot_current_x = 0.0;
	this->robot_current_y = 0.0;
	this->robot_current_yaw = 0.0;
	this->robot_last_x = 0.0;
	this->robot_last_y = 0.0;
	this->robot_last_yaw = 0.0;
	this->time_to_wait = 0.5;
	this->is_moving = false;
	R<<	5.0,	0.05,	0.001,
		0.05,	5.0,	0.001,
		0.001,	0.001,	0.01;
	/*sigma <<0.001,0.001,0.001,
			0.001,0.001,0.001,
			0.001,0.001,0.001;*/

	//Initiation coefficient sigma matrix values
			sigma <<30.0,	2.0,	0.02,
					2.0,	30.0,	0.02,
					0.02,	0.02,	0.1;
	//Initiation of G coefficient matrix
	G<< 1.0,	0.0,	0.0,
		0.0,	1.0,	0.0,
		0.0,	0.0,	1.0;
	//Initiation of Fu coefficient matrix
	Fu(2,0) = 0.0;
	Fu(2,1) = 0.0;
	Fu(2,2) = 1.0;
	//Measure Values
	Q<<10.0,	0.0,
		0.0,	0.01;
	q=0;
}

NodeLandmarkLocalization::~NodeLandmarkLocalization() {
	// TODO Auto-generated destructor stub
	myfile_marker.close();
	myfile_position.close();
}

void NodeLandmarkLocalization::callbackSpecialCommandsTriskar(const std_msgs::Char::ConstPtr& msg){
	if(msg->data == 'R'){
		this->is_moving = false;
		std::cout<<"Reseting"<<std::endl;	//Initiation coefficient sigma matrix values
		sigma <<30.0,	2.0,	0.02,
				2.0,	30.0,	0.02,
				0.02,	0.02,	0.1;
		robot_last_x = 0.0;
		robot_last_y = 0.0;
		robot_last_yaw = 0.0;
		//Position of the robot in the robot's frame
		robot_current_x = 0.0;
		robot_current_y = 0.0;
		robot_current_yaw = 0.0;
	}
}

void NodeLandmarkLocalization::verifyAngle(float *angle){
	if(*angle>M_PI){
		*angle= *angle-2.0*M_PI;
	}else if(*angle<-M_PI){
		*angle = *angle+2.0*M_PI;
	}
}

void NodeLandmarkLocalization::setPublisherOdometry(ros::Publisher * pub){
	this->pub_odometry = pub;
}

void NodeLandmarkLocalization::loadInformation(){
	ParserConfigurationFiles temp_configuration;
	std::string file = project_directory +"/robot_configuration_files/scene_description.json";
	markers_position = temp_configuration.readMarkersPositionDescriptionFile(file);
	file = project_directory +"/robot_configuration_files/robot_initial_position.json";
	temp_configuration.readRobotInitialPositionFile(file,&this->robot_initial_x,&this->robot_initial_y,&this->robot_initial_yaw);
}

void NodeLandmarkLocalization::setProjectDirectory(std::string directory){
	this->project_directory = directory;
	std::string file = project_directory+"/markerInfo.txt";
	myfile_marker.open(file.c_str());
	file = project_directory+"/positionInfo.txt";
	myfile_position.open(file.c_str());
}

void NodeLandmarkLocalization::setTransformListener(tf::TransformListener *listener){
	this->listener = listener;
}


void NodeLandmarkLocalization::callbackNewOdometry(const theatre_bot::OdometryTriskar::ConstPtr& msg){
		//X = A*x-1+Bu comes from the triskar
		//Save the last positions
		robot_last_x = robot_current_x;
		robot_last_y = robot_current_y;
		robot_last_yaw = robot_current_yaw;
		//Position of the robot in the robot's frame
		robot_current_x = msg->pose.position.x;
		robot_current_y = msg->pose.position.y;
		robot_current_yaw = msg->pose.orientation;
		if(msg->twist.angular!=0||msg->twist.linear.x!=0||msg->twist.linear.y!=0){
			this->is_moving = true;
		}else{
			this->is_moving = false;
		}
}
void NodeLandmarkLocalization::callbackNewMarker(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg){
	markers_info =msg->markers;
}

void NodeLandmarkLocalization::updatePosition(){
	difference_time = ros::Time::now() - last_time;
	if(difference_time.toSec()>=time_to_wait){
		//Update Position
		float delta_x = robot_current_x - robot_last_x;
		float delta_y = robot_current_y - robot_last_y;
		G(0,2) = -delta_x*sinf(robot_current_yaw)-delta_y*cosf(robot_current_yaw);
		G(1,2) = delta_x*cosf(robot_current_yaw)-delta_y*sinf(robot_current_yaw);
		Fu(0,0) = cosf(robot_current_yaw);
		Fu(0,1) = -sinf(robot_current_yaw);
		Fu(0,2) = G(0,2);
		Fu(1,0) = sinf(robot_current_yaw);
		Fu(1,1) =cosf(robot_current_yaw);
		Fu(1,2) = G(1,2);
		sigma = G*sigma*G.transpose()+Fu*R*Fu.transpose();

		//Variables for sensor information
		ar_track_alvar_msgs::AlvarMarker marker;
		float marker_pos_x = 0.0;
		float marker_pos_y = 0.0;
		float marker_yaw = 0.0;
		float robot_calculated_x = 0.0;
		float robot_calculated_y = 0.0;
		float robot_calculated_yaw = 0.0;
		Eigen::MatrixXf H(2,3);
		Eigen::MatrixXf K(3,2);
		Eigen::Matrix2f K_temp;
		Eigen::Vector3f sum;
		Eigen::Matrix3f sum_H_K = Eigen::Matrix3f::Zero(3,3);
		Eigen::Vector2f z;
		sum(0) = 0.0;
		sum(1) = 0.0;
		sum(2) = 0.0;		//The markers' localization are in the scene frame, therefore they should change to robots frame of reference
		for(int i=0; i<markers_info.size(); ++i){
			marker = markers_info[i];
			std::map<int, MarkerPosition>::iterator it;
			it = this->markers_position.find(marker.id);
			if(it != this->markers_position.end()){
				try{
					geometry_msgs::PoseStamped temp_pose;
					geometry_msgs::PoseStamped base_pose;
					temp_pose.header = marker.header;
					temp_pose.pose = marker.pose.pose;
					listener->transformPose("robot",temp_pose,base_pose);
					//Convert meters to millimeters
					z(0) = sqrtf(powf(base_pose.pose.position.x*1000.0,2)+powf(base_pose.pose.position.y*1000.0,2));
					z(1) = atan2f(base_pose.pose.position.y,base_pose.pose.position.x);
					//tf::Quaternion q_t(base_pose.pose.orientation.x,base_pose.pose.orientation.y,base_pose.pose.orientation.z,base_pose.pose.orientation.w);
					//tf::Matrix3x3 m(q_t);
					//double roll, pitch, yaw;
					//m.getRPY(roll, pitch, yaw);
					//std::cout<<base_pose.pose.orientation.x<<" "<<base_pose.pose.orientation.y<<" "<<base_pose.pose.orientation.z<<" "<<base_pose.pose.orientation.w<<std::endl;
					//std::cout<<roll/M_PI*180.0<<" "<<pitch/M_PI*180.0<<" "<<yaw/M_PI*180.0<<std::endl;
					//Convert marker position to robots frame
					marker_pos_x = (it->second.getMarkerX()-robot_initial_x)*cosf(robot_initial_yaw)+(it->second.getMarkerY()-robot_initial_y)*sinf(robot_initial_yaw);
					marker_pos_y =-(it->second.getMarkerX()-robot_initial_x)*sinf(robot_initial_yaw)+(it->second.getMarkerY()-robot_initial_y)*cosf(robot_initial_yaw);
					marker_yaw =it->second.getMarkerYaw() - robot_initial_yaw;
					d(0) = marker_pos_x - robot_current_x;
					d(1) = marker_pos_y - robot_current_y;
					q = d.transpose()*d;
					z_ideal(0) = sqrtf(q);
					float d_0 = d(0);
					float d_1 = d(1);
					z_ideal(1) = atan2f(d_1,d_0)-robot_current_yaw;
					/*H(0,0) = z_ideal(0)*d(0);
					H(0,1) = -z_ideal(0)*d(1);
					H(0,2) = 0;
					H(1,0) = d(1);
					H(1,1) = d(0);
					H(1,2) = -q;
					H = H*1/q;*/
					H(0,0)	=	-d(0)/z_ideal(0);
					H(0,1)	=	-d(1)/z_ideal(0);
					H(0,2)	= 	0;
					H(1,0)	=	d(1)/q;
					H(1,1)	=	-d(0)/q;
					H(1,2)	=	-1;
					K_temp = H*sigma*H.transpose()+Q;
					K = sigma*H.transpose()*K_temp.inverse();
					myfile_marker<<z(0)<<";"<<z(1)<<";"<<z_ideal(0)<<";"<<z(1)<<"\n";
					sum += K*(z-z_ideal);
					sum_H_K += K*H;
				}catch(tf::TransformException& ex){
					ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
					std::cout<<ex.what()<<std::endl;
				}
			}
		}

		//Update position with the sensor information
		robot_calculated_x = robot_current_x + sum(0);
		robot_calculated_y = robot_current_y + sum(1);
		robot_calculated_yaw = robot_current_yaw + sum(2);
		this->verifyAngle(&robot_calculated_yaw);
		//std::cout<<"Robot "<<robot_calculated_x<<" "<<robot_calculated_y<<" "<<robot_calculated_yaw<<" "<<robot_calculated_yaw/M_PI*180.0<<std::endl;
		//Update sigma with position
		sigma = (Eigen::Matrix3f::Identity(3,3)-sum_H_K)*sigma;
		//std::cout<<"***********"<<std::endl;
		//std::cout<<sigma<<std::endl;
		//std::cout<<"***********"<<std::endl;
		//Send position
		//Save the last positions
	/*	robot_last_x = robot_current_x;
		robot_last_y = robot_current_y;
		robot_last_yaw = robot_current_yaw;
		//Position of the robot in the robot's frame
		robot_current_x = robot_calculated_x;
		robot_current_y = robot_calculated_y;
		robot_current_yaw = robot_calculated_yaw;*/
		myfile_position<<robot_calculated_x<<";"<<robot_calculated_y<<";"<<robot_calculated_yaw<<"\n";
		theatre_bot::OdometryTriskar odom;
		odom.pose.position.x = robot_calculated_x;
		odom.pose.position.y = robot_calculated_y;
		odom.pose.orientation = robot_calculated_yaw;
		this->pub_odometry->publish(odom);
		last_time = ros::Time::now();
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "landmakr_position_node");
	ros::NodeHandle n;
	NodeLandmarkLocalization node;
	if(n.hasParam("project_directory")){
		std::string project_path;
		n.getParam("project_directory",project_path);
		//std::cout<<"Project path "<<project_path<<std::endl;
		node.setProjectDirectory(project_path);
		node.loadInformation();
	}
	tf::TransformListener listener(ros::Duration(10));
	node.setTransformListener(&listener);
	ros::Publisher pub_odometry = n.advertise<theatre_bot::OdometryTriskar>("odometry_landmarks", 1);
	//TODO publish new position triskar to set it in the triskar, this includes changing triskar code
	ros::Subscriber sub_ar_pose = n.subscribe("ar_pose_marker", 1, &NodeLandmarkLocalization::callbackNewMarker, &node);
	ros::Subscriber sub_odometry = n.subscribe("odometry_triskar", 1, &NodeLandmarkLocalization::callbackNewOdometry, &node);
	ros::Subscriber sub_special_commands = n.subscribe("commands_triskar", 1, &NodeLandmarkLocalization::callbackSpecialCommandsTriskar, &node);
	node.setPublisherOdometry(&pub_odometry);
	while(ros::ok()){
		node.updatePosition();
		ros::spinOnce();
	}
}
