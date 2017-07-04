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
	this->time_to_wait = 0.2;
	this->count_not_moving = 0;
	//Gloabl variables
	new_message_odometry = false;
	this->new_global_information = false;
	robot_global<< 0.0,0.0,0.0;
	//Kalman
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
	//Measure Values
	Q<<10.0,	0.0,	0.0,
		0.0,	0.01,	0.0,
		0.0,	0.0,	0.01;
	Q_odometry <<5.0,	0.0,	0.0,
				0.0,	5.0,	0.0,
				0.0,	0.0,	0.05;
	z_odometry<<0.0,0.0,0.0;
	R_Coefficients<<1,1,1,
					1,1,1,
					1,1,1;
	q=0;
	is_moving = false;
	first_execution = true;
}

NodeLandmarkLocalization::~NodeLandmarkLocalization() {
	// TODO Auto-generated destructor stub
	myfile_marker.close();
	myfile_position.close();
}

void NodeLandmarkLocalization::callbackSpecialCommandsTriskar(const std_msgs::Char::ConstPtr& msg){
	if(msg->data == 'R'){
		std::cout<<"Reseting"<<std::endl;	//Initiation coefficient sigma matrix values
		sigma = sigma_initial;
		robot_last_x = 0.0;
		robot_last_y = 0.0;
		robot_last_yaw = 0.0;
		//Position of the robot in the robot's frame
		robot_current_x = 0.0;
		robot_current_y = 0.0;
		robot_current_yaw = 0.0;
		z_odometry<<0.0,0.0,0.0;
		is_moving = false;
		count_not_moving = 0;
		markers_info.clear();
		position_info.clear();
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
	//Load Kalman Information
	KalmanParser kalman;
	kalman.setDirectory(this->project_directory);
	kalman.loadInformation();
	sigma_initial = kalman.getSigmaMatrix();
	sigma = sigma_initial;
	R_Coefficients = kalman.getRMatrix();
	Q = kalman.getQMatrix();
	Q_odometry = kalman.getQOdometryMatrix();
	Q_global = kalman.getQGlobalMatrix();
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
	//Position of the robot in the robot's frame
	z_odometry(0) = msg->pose.position.x;
	z_odometry(1) = msg->pose.position.y;
	z_odometry(2) = msg->pose.orientation;
	u(0) = msg->commands.linear.x;
	u(1) = msg->commands.linear.y;
	u(2) = msg->commands.angular;
	u_real(0) = msg->twist.linear.x;
	u_real(1) = msg->twist.linear.y;
	u_real(2) = msg->twist.angular;
	if(u_real(0) != 0 && u_real(1) != 0 && u_real(2) != 0){
		is_moving = true;
		count_not_moving = 0;
	}else{
		is_moving = false;
		sigma = sigma_initial;
	}
	new_message_odometry = true;
	last_time_odometry_message = ros::Time::now();

}
void NodeLandmarkLocalization::callbackNewMarker(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr& msg){
	markers_info =msg->markers;
	std::cout<<"Marker"<<markers_info.size()<<std::endl;
}

void NodeLandmarkLocalization::robotPositionGlobal(float global_position_x,float global_position_y, float global_position_yaw, float *local_position_x, float *local_position_y,float *local_position_yaw){
	std::cout<<"Before info change "<<global_position_x<<" -- "<<global_position_y<<" -- "<<global_position_yaw<<std::endl;
	*local_position_x = (global_position_x - robot_initial_x)*cosf(robot_initial_yaw)  + (global_position_y - robot_initial_y)*sinf(robot_initial_yaw);
	*local_position_y = (global_position_x - robot_initial_x)*-sinf(robot_initial_yaw) + (global_position_y - robot_initial_y)*cosf(robot_initial_yaw);
	*local_position_yaw = global_position_yaw - robot_initial_yaw;
	this->verifyAngle(local_position_yaw);
	std::cout<<"After change "<<*local_position_x<<" -- "<<*local_position_y<<" -- "<<*local_position_yaw<<std::endl;
}

void NodeLandmarkLocalization::callbackNewGlobalPosition(const theatre_bot::OdometriesTriskar::ConstPtr& msg){
	this->new_global_information = true;
	last_time_received_global = ros::Time::now();
	position_info = msg->odometries;
}

void NodeLandmarkLocalization::updatePosition(){
	difference_time = ros::Time::now() - last_time;
	float difference = static_cast<float>(difference_time.toSec());
	if(first_execution){
		last_time = ros::Time::now();
		first_execution = false;
	}
	else if(difference>=time_to_wait && (is_moving || count_not_moving <1) && new_message_odometry){
		//Update Sigma
		new_message_odometry = false;
		if(!is_moving){
			++count_not_moving;
		}
		last_time_webcam_message = ros::Time::now();
		difference_time_odometry_message = ros::Time::now() - last_time_odometry_message;
		float difference_messages = static_cast<float>(difference_time_odometry_message.toSec());
		float real_yaw = z_odometry(2);
		float delta_x = z_odometry(0) - robot_last_x;
		float delta_y = z_odometry(1) - robot_last_y;
		float delta_x_ideal = u(0)*difference_messages;
		float delta_y_ideal = u(1)*difference_messages;
		float delta_yaw_ideal = robot_last_yaw + u(2)*difference_messages/2.0;
		G =  Eigen::Matrix3f::Identity(3,3);
		G(0,2) = (-delta_x_ideal*sinf(delta_yaw_ideal)-delta_y_ideal*cosf(delta_yaw_ideal));
		G(1,2) = (delta_x_ideal*cosf(delta_yaw_ideal)-delta_y_ideal*sinf(delta_yaw_ideal));
		Fu(0,0) = cosf(real_yaw);
		Fu(1,0) = sinf(real_yaw);
		Fu(2,0) = 0.0;
		Fu(0,1) =-sinf(real_yaw);
		Fu(1,1) = cosf(real_yaw);
		Fu(2,1) = 0.0;
		Fu(0,2) = (-1/2*delta_x*sinf(real_yaw)-1/2*delta_y*cosf(real_yaw));
		Fu(1,2) = (1/2*delta_x*cosf(delta_yaw_ideal)-1/2*delta_y*sinf(real_yaw));
		Fu(2,2) = 1;
		//Variables need it to calculate the R matrix
		Eigen::Vector3f z_temp;
		Eigen::Vector2f z_temp_sensor;
		Eigen::Matrix3f Q_temp;
		Eigen::Matrix2f Q_temp_sensor;
		z_temp = difference_messages*(u_real - u);
		float yaw_temp = z_temp(2);
		this->verifyAngle(&yaw_temp);
		z_temp(2) = yaw_temp;
		std::cout<<"z_temp \n"<<z_temp<<std::endl;
		R << (z_temp(0)-Q_odometry(0,0))*(z_temp(0)-Q_odometry(0,0)),	(z_temp(1)-Q_odometry(1,1))*(z_temp(0)-Q_odometry(0,0)),	(z_temp(2)-Q_odometry(2,2))*(z_temp(0)-Q_odometry(0,0))/1000.0,
			  (z_temp(0)-Q_odometry(0,0))*(z_temp(1)-Q_odometry(1,1)), (z_temp(1)-Q_odometry(1,1))*(z_temp(1)-Q_odometry(1,1)), (z_temp(2)-Q_odometry(2,2))*(z_temp(1)-Q_odometry(1,1))/1000.0,
			  (z_temp(0)-Q_odometry(0,0))*(z_temp(2)-Q_odometry(2,2))/1000.0, (z_temp(1)-Q_odometry(1,1))*(z_temp(2)-Q_odometry(2,2))/1000.0, (z_temp(2)-Q_odometry(2,2))*(z_temp(2)-Q_odometry(2,2));
		//R = Q_odometry;
		/*R(0,0) = fabs(static_cast<float>(z_temp(0)))+Q_odometry(0,0);
		R(1,1) = fabs(static_cast<float>(z_temp(1)))+Q_odometry(1,1);
		R(2,2) = fabs(static_cast<float>(z_temp(2)))*0.001+Q_odometry(2,2);*/
		std::cout<<"R: \n"<<R<<"\n..\n"<<std::endl;
		//Calculation of sigma
		sigma = G*sigma*G.transpose()+Fu*R*Fu.transpose();
		std::cout<<"\nsigma\n"<<sigma<<"\nG\n"<<G<<"\nFu\n"<<Fu<<std::endl;
		//Variables for sensor information
		ar_track_alvar_msgs::AlvarMarker marker;
		float marker_pos_x = 0.0;
		float marker_pos_y = 0.0;
		float marker_yaw = 0.0;
		float robot_calculated_x = 0.0;
		float robot_calculated_y = 0.0;
		float robot_calculated_yaw = 0.0;
		Eigen::MatrixXf H(2,3);
		H << 0,0,0,0,0,0;
		Eigen::MatrixXf K(3,2);
		K << 0,0,0,0,0,0;
		Eigen::MatrixXf K_temp(2,2);
		K_temp << 0,0,0,0;
		Eigen::Vector3f sum;
		Eigen::Matrix3f sum_H_K = Eigen::Matrix3f::Zero(3,3);
		Eigen::Vector2f z;		//The markers' localization are in the scene frame, therefore they should change to robots frame of reference
		sum(0) = 0.0;
		sum(1) = 0.0;
		sum(2) = 0.0;
		/*It starts the calculation from the markers information*/
		for(int i=0; i<markers_info.size(); ++i){
			marker = markers_info[i];
			std::map<int, MarkerPosition>::iterator it;
			it = this->markers_position.find(marker.id);
			if(it != this->markers_position.end()){
				try{
					std::cout<<"Analalzing landmark "<<marker.id<<std::endl;
					geometry_msgs::PoseStamped temp_pose;
					geometry_msgs::PoseStamped base_pose;
					temp_pose.header = marker.header;
					temp_pose.pose = marker.pose.pose;
					listener->transformPose("robot",temp_pose,base_pose);
					//Convert meters to millimeters
					z(0) = sqrtf(powf(base_pose.pose.position.x*1000.0,2)+powf(base_pose.pose.position.y*1000.0,2));
					z(1) = atan2f(base_pose.pose.position.y,base_pose.pose.position.x);
					tf::Quaternion q_t(base_pose.pose.orientation.x,base_pose.pose.orientation.y,base_pose.pose.orientation.z,base_pose.pose.orientation.w);
					tf::Matrix3x3 m(q_t);
					double roll, pitch, yaw;
					m.getRPY(roll, pitch, yaw);
					//Convert marker position to robots frame
					marker_pos_x = (it->second.getMarkerX()-robot_initial_x)*cosf(robot_initial_yaw)+(it->second.getMarkerY()-robot_initial_y)*sinf(robot_initial_yaw);
					marker_pos_y =-(it->second.getMarkerX()-robot_initial_x)*sinf(robot_initial_yaw)+(it->second.getMarkerY()-robot_initial_y)*cosf(robot_initial_yaw);
					marker_yaw =it->second.getMarkerYaw() - robot_initial_yaw; // this converts the yaw to robot's frame of reference
					this->verifyAngle(&marker_yaw);
					std::cout<<"Marker Info "<<marker_pos_x<<" "<<marker_pos_y<<" "<<marker_yaw<<" "<<yaw<<std::endl;
					d(0) = marker_pos_x - z_odometry(0);
					d(1) = marker_pos_y - z_odometry(1);
					q = d.transpose()*d;
					z_ideal(0) = sqrtf(q);
					float d_0 = d(0);
					float d_1 = d(1);
					float temp_z;
					z_ideal(1) = atan2f(d_1,d_0)-z_odometry(2);
					temp_z = z_ideal(1);
					this->verifyAngle(&temp_z);
					z_ideal(1) = temp_z;
					H(0,0)	=	-d(0)/z_ideal(0);
					H(0,1)	=	-d(1)/z_ideal(0);
					H(0,2)	= 	0;
					H(1,0)	=	d(1)/q;
					H(1,1)	=	-d(0)/q;
					H(1,2)	=	-1;
					std::cout<<"z\n"<<z<<"\n z_ideal\n"<<z_ideal<<std::endl;
					z_temp_sensor = z-z_ideal;
					yaw_temp = z_temp_sensor(1);
					this->verifyAngle(&yaw_temp);
					z_temp_sensor(1) = yaw_temp;
					Q_temp_sensor << Q(0,0) /*+ sqrtf(powf(static_cast<float>(z_temp(0)),2)+powf(static_cast<float>(z_temp(1)),2))*/ , Q(0,1) , Q(1,0), Q(1,1)/*+fabs(static_cast<float>(z_temp(2)))*/;
					std::cout<<"Q_sensor \n"<<Q_temp_sensor<<"\nH\n"<<H<<std::endl;
					K_temp = H*sigma*H.transpose()+Q_temp_sensor;
					K = sigma*H.transpose()*K_temp.inverse();
					std::cout<<"KKKKK\n"<<K<<"\nfdaf\n"<<K_temp<<std::endl;
					//It verifies if information from the camera is good
					Eigen::Vector3f sum_temp;
					std::cout<<"Error detected \n"<<z_temp_sensor<<""<<std::endl;
					sum_temp = K*(z_temp_sensor);
					std::cout<<"sum_temp\n"<<sum_temp<<std::endl;
					sum += sum_temp;
					sum_H_K += K*H;
				}catch(tf::TransformException& ex){
					ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
					std::cout<<ex.what()<<std::endl;
				}
			}
			yaw_temp = sum(2);
			this->verifyAngle(&yaw_temp);
			sum(2) = yaw_temp;
			std::cout<<"Sum local camera\n"<<sum<<std::endl;
		}
		markers_info.clear();
		/*End the onboard sensor integration*/
		/*Global sensor integration. It is supposed that the information is coming in the robot's frame of reference*/
		//Need it variables
		Eigen::Matrix3f H_global = Eigen::Matrix3f::Identity(3,3);
		Eigen::Matrix3f K_global = Eigen::Matrix3f::Zero(3,3);
		Eigen::Matrix3f K_global_temp = Eigen::Matrix3f::Zero(3,3);
		Eigen::Vector3f sum_global, error_global;
		Eigen::Matrix3f sum_global_H_K = Eigen::Matrix3f::Zero(3,3);
		float global_position_x;
		float global_position_y;
		float global_position_yaw;
		theatre_bot::OdometryTriskar temp_odometry;
		sum_global(0) = 0.0;
		sum_global(1) = 0.0;
		sum_global(2) = 0.0;
		difference_time_global = ros::Time::now() - last_time_received_global;
		std::cout<<"Before updating information from global"<<std::endl;
		if(new_global_information && static_cast<float>(difference_time_global.toSec()) < 2.0*time_to_wait && position_info.size()>0){
			new_global_information = false;
			std::cout<<"Quantity "<<position_info.size()<<std::endl;
			for(int i = 0; i<position_info.size(); ++i){
				temp_odometry = position_info[i];
				std::cout<<"Updating information"<<std::endl;
				Q_temp = Q_global;
				Q_temp(0,0) = Q_temp(0,0)+fabs(static_cast<float>(u_real(0)*u_real(0)));
				Q_temp(1,1) = Q_temp(1,1)+fabs(static_cast<float>(u_real(1)*u_real(1)));
				Q_temp(2,2) = Q_global(2,2)+fabs(static_cast<float>(u_real(2)));
				std::cout<<"dfafafda\n"<<Q_temp<<std::endl;
				K_global_temp = H_global*sigma*H_global.transpose()+Q_temp;
				K_global = sigma*H_global.transpose()*K_global_temp.inverse();
				std::cout<<" Information before call the function "<<temp_odometry.pose.position.x<<" "<<temp_odometry.pose.position.y<<" "<<temp_odometry.pose.orientation<<std::endl;
				this->robotPositionGlobal(static_cast<float>(temp_odometry.pose.position.x),static_cast<float>(temp_odometry.pose.position.y),
						static_cast<float>(temp_odometry.pose.orientation),&global_position_x,&global_position_y,&global_position_yaw);
				std::cout<<" robot position "<<z_odometry(0)<<" | "<<z_odometry(1)<<" | "<<z_odometry(2)<<std::endl;
				error_global(0) = global_position_x - z_odometry(0);
				error_global(1) = global_position_y - z_odometry(1);
				yaw_temp = global_position_yaw - z_odometry(2);
				this->verifyAngle(&yaw_temp);
				error_global(2) = yaw_temp;
				std::cout<<"Error: "<<error_global<<std::endl;
				sum_global += K_global*error_global;
				sum_global_H_K += K_global*H_global;
				std::cout<<"Gain \n"<<K_global<<"\n-----"<<std::endl;
				std::cout<<"Resultado \n"<<sum_global<<"\n-----"<<std::endl;
			}
		}
		position_info.clear();
		yaw_temp = sum_global(2);
		this->verifyAngle(&yaw_temp);
		sum_global(2) = yaw_temp;
		//Update position with the sensor information
		robot_calculated_x = sum(0) +sum_global(0);
		robot_calculated_y = sum(1) + sum_global(1);
		robot_calculated_yaw =  sum(2) + sum_global(2);
		this->verifyAngle(&robot_calculated_yaw);
		std::cout<<"\n.................\nRobot: "<<robot_calculated_x<<" "<<robot_calculated_y<<" "<<robot_calculated_yaw<<" "<<robot_calculated_yaw/M_PI*180.0<<std::endl;
		//Update sigma with position
		sigma = (Eigen::Matrix3f::Identity(3,3)-(sum_H_K+sum_global_H_K))*sigma;
		//std::cout<<"***********"<<std::endl;
		//std::cout<<sigma<<std::endl;
		//std::cout<<"***********"<<std::endl;
		//Send position
		//Save the last positions
		//Position of the robot in the robot's frame
		//Save the last positions
		robot_last_x = robot_calculated_x;
		robot_last_y = robot_calculated_y;
		robot_last_yaw = robot_calculated_yaw;
		theatre_bot::OdometryTriskar odom;
		odom.pose.position.x = robot_calculated_x;
		odom.pose.position.y = robot_calculated_y;
		odom.pose.orientation = robot_calculated_yaw;
		std::cout<<"Before sending "<<ros::Time::now()-last_time_webcam_message<<std::endl;
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
		std::cout<<"It has loaded information"<<std::endl;
		n.getParam("project_directory",project_path);
		//std::cout<<"Project path "<<project_path<<std::endl;
		node.setProjectDirectory(project_path);
		node.loadInformation();
	}
	tf::TransformListener listener(ros::Duration(10));
	node.setTransformListener(&listener);
	ros::Publisher pub_odometry = n.advertise<theatre_bot::OdometryTriskar>("odometry_landmarks", 1);
	ros::Subscriber sub_ar_pose = n.subscribe("ar_pose_marker", 1, &NodeLandmarkLocalization::callbackNewMarker, &node);
	ros::Subscriber sub_odometry = n.subscribe("odometry_triskar", 1, &NodeLandmarkLocalization::callbackNewOdometry, &node);
	ros::Subscriber sub_global_position = n.subscribe("global_position_landmark", 1, &NodeLandmarkLocalization::callbackNewGlobalPosition, &node);
	ros::Subscriber sub_special_commands = n.subscribe("commands_triskar", 5, &NodeLandmarkLocalization::callbackSpecialCommandsTriskar, &node);
	node.setPublisherOdometry(&pub_odometry);
	while(ros::ok()){
		node.updatePosition();
		ros::spinOnce();
	}
}
