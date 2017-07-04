/*
 * pepper_emotion.h
 *
 *  Created on: June 04, 2017
 *      Author: Stefan Kurz
 */

#include <ros/ros.h>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>

#include <alproxies/almotionproxy.h>
#include <alproxies/alledsproxy.h>
#include <alproxies/alpreferencemanagerproxy.h>
#include <alcommon/albroker.h>
#include <qi/os.hpp>

#include "pepper_platform/PepperInfo.h"
#include "pepper_platform/PepperMove.h"
#include "pepper_platform/PepperUpper.h"
#include "pepper_platform/EmotionMessage.h"

// ----- SET TO A PLAUSIBLE VALUE -----
std::string robotIp = "192.168.1.149"; 		// robotIP
float angle_error = 1.0/180.0 * M_PI;  		// allowed error of 1° [in grad]
float factor_velocity_y = 0.1;			// factor multiplied with velocity_lin to move in y direction when oscillating

// only needed std_velocity_shoulder (for all joints) and std_velocity_move and oscillate
float std_velocity_shoulder = 0.2;		// (fraction - maximum 1)
float std_velocity_torso = 0.5;			// (fraction - maximum 1)
float std_velocity_head = 0.05;			// (fraction - maximum 1)
float std_velocity_move = 1;			// maximum 0.55   m/s 	-   minimum 0.1    m/s
float std_velocity_oscillate_body = 0.3;	// maximum 2.0  rad/s	-   minimum 0.2  rad/s

// shoulder
float shoulder_angle_move;
float shoulder_angle_oscillate;
float shoulder_angle_left;
float shoulder_angle_right;
float shoulder_velocity_move = 0.1;
float shoulder_velocity_oscillate = 0.1;
bool start_shoulder = false;
bool shoulderosc = false;
bool shoulder_fwd = false;
bool inform_shoulder = false;

// torso
float torso_angle_move_x;
float torso_angle_move_y;
float torso_angle_oscillate_x;
float torso_angle_oscillate_y;
float torso_angle_x;
float torso_angle_y;
float torso_velocity_move_x = 0.1;
float torso_velocity_move_y = 0.1;
float torso_velocity_oscillate_x = 0.1;
float torso_velocity_oscillate_y = 0.1;
bool start_torso_x = false;
bool start_torso_y = false;
bool torsoosc_x = false;
bool torsoosc_y = false;
bool torso_x_fwd = false;
bool torso_y_fwd = false;
bool inform_torso_x = false;
bool inform_torso_y = false;

// body
float body_move_x;
float body_move_y;
float body_angle_oscillate;
float std_angle;			// desired angle to move as absolute value (standard move direction without oscillation)
float body_angle_left;			// desired angle for counterclockwise oscillation
float body_angle_right;			// desired angle for clockwise oscillation
float velocity_x;
float velocity_y;
float velocity_theta;
float velocity_lin;
float velocity_ang;
bool newmove = false;
bool newmovosc = false;
bool moving = false;
bool movosc = false;			// movement with oscillation
bool movosc_temp = false;		// temporary value to store previous movosc value -> if (temp && !moveosc) -> finish osc
bool turnright = false;
bool stop = false;			// send stopMove message to Robot


// head
std::string emotion;
std::string eyecolor;
float earintensity;
float head_angle_pitch;


// ROS and AL Proxy
ros::Subscriber pepper_shoulder;
ros::Subscriber pepper_torso;
ros::Subscriber pepper_body;
ros::Subscriber pepper_emotion;
ros::Publisher pepper_info;

// Aldebaran Proxies and values
// init motion broker               				 //  name, ipbroker, portbroker, robotip, robotport
boost::shared_ptr<AL::ALBroker> broker = AL::ALBroker::createBroker("motionbroker", "0.0.0.0", 0, robotIp, 9559); 
AL::ALMotionProxy motion(broker);
AL::ALLedsProxy led(broker);

AL::ALValue jointname = AL::ALValue::array("LShoulderPitch", "RShoulderPitch", "HipPitch", "HipRoll", "HeadPitch");

std::string earled = "EarLeds";
std::string eyeled = "FaceLeds";

AL::ALValue angles;			// setAngles
std::vector<float> sensorAngles;	// getAngles
std::vector<float> positionstart;	// getRobotPosition (start of movement)
std::vector<float> positioncur;		// getRobotPosition (curren)

bool update_joints = false;
bool update_move = false;
bool update_led = false;

// functions
bool UpdateJoints();
bool UpdateMovement();
bool dstreached();

void callbackUpdateShoulder(const pepper_platform::PepperUpper::ConstPtr& msg);
void callbackUpdateTorso(const pepper_platform::PepperUpper::ConstPtr& msg);
void callbackUpdateBody(const pepper_platform::PepperMove::ConstPtr& msg);
void callbackUpdateEmotion(const pepper_platform::EmotionMessage::ConstPtr& msg);

