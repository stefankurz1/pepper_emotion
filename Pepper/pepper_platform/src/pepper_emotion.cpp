/*
 * pepper_emotion.cpp
 *
 *  Created on: June 04, 2017
 *      Author: Stefan Kurz
 *
 *
 *  Pepper Joints:'HeadYaw', 'HeadPitch', 'LShoulderPitch', 'LShoulderRoll', 'LElbowYaw', 'LElbowRoll', 'LWristYaw', 'LHand', 
 * 		  'HipRoll', 'HipPitch', 'KneePitch', 'RShoulderPitch', 'RShoulderRoll', 'RElbowYaw', 'RElbowRoll', 'RWristYaw', 'RHand'
 */


#include "pepper_emotion.h"

bool UpdateJoints(){
	bool update = false;

	// get measured joint angles ("LShoulderPitch", "RShoulderPitch", "HipPitch", "HipRoll")
	sensorAngles = motion.getAngles(jointname, true);
	
	// send shoulder joint state - LShoulderPitch, RShoulderPitch
	if(start_shoulder == true){
		shoulder_angle_left = M_PI * (1.0/2.0 - 10.0/180.0)  - (shoulder_angle_move + shoulder_angle_oscillate);
		shoulder_angle_right = M_PI * (1.0/2.0 - 10.0/180.0) - (shoulder_angle_move - shoulder_angle_oscillate);
		start_shoulder = false;	
		shoulder_fwd = true;
		update = true;
	}else if(shoulderosc == true){
		if((sensorAngles[0] - shoulder_angle_left) <= angle_error && shoulder_fwd == true){
			shoulder_angle_left = M_PI * (1.0/2.0 - 10.0/180.0) - (shoulder_angle_move - shoulder_angle_oscillate);
			shoulder_angle_right = M_PI * (1.0/2.0 - 10.0/180.0)  - (shoulder_angle_move + shoulder_angle_oscillate);
			shoulder_fwd = false;
			update = true;
			if(shoulder_angle_oscillate == 0){
				shoulderosc = false;
			}
		}else if((sensorAngles[0] - shoulder_angle_left) >= -angle_error && shoulder_fwd == false){
			shoulder_angle_left = M_PI * (1.0/2.0 - 10.0/180.0)  - (shoulder_angle_move + shoulder_angle_oscillate);
			shoulder_angle_right = M_PI * (1.0/2.0 - 10.0/180.0) - (shoulder_angle_move - shoulder_angle_oscillate);
			shoulder_fwd = true;
			update = true;
			if(shoulder_angle_oscillate == 0){
				shoulderosc = false;
			}	
		}			
	} 	

	// send torso joint state - HipPitch
	if(start_torso_x == true){
		torso_angle_x = -(torso_angle_move_x + torso_angle_oscillate_x  + (M_PI * 5.0/180.0));	
		start_torso_x = false;
		torso_x_fwd = true;
		update = true;
	}else if(torsoosc_x == true){
		if((sensorAngles[2] - torso_angle_x) <= angle_error && torso_x_fwd == true){
			torso_angle_x = -(torso_angle_move_x - torso_angle_oscillate_x + (M_PI * 5.0/180.0));
			torso_x_fwd = false;
			update = true;
			if(torso_angle_oscillate_x == 0){
				torsoosc_x = false;
			}
		}else if((sensorAngles[2] - torso_angle_x) >= -angle_error && torso_x_fwd == false){
			torso_angle_x = -(torso_angle_move_x + torso_angle_oscillate_x + (M_PI * 5.0/180.0));
			torso_x_fwd = true;
			update = true;
			if(torso_angle_oscillate_x == 0){
				torsoosc_x = false;
			}
		}
	}
	
	// send torso joint state - HipRoll	
	if(start_torso_y == true){
		torso_angle_y = torso_angle_move_y + torso_angle_oscillate_y;			
		start_torso_y = false;	
		torso_y_fwd = true;
		update = true;
	}else if(torsoosc_y == true){
		if((sensorAngles[3] - torso_angle_y) >= -angle_error * 4 && torso_y_fwd == true){
			torso_angle_y = torso_angle_move_y - torso_angle_oscillate_y;
			torso_y_fwd = false;
			update = true;
			if(torso_angle_oscillate_y == 0){
				torsoosc_y = false;
			}
		}else if((sensorAngles[3] - torso_angle_y) <= angle_error * 4 && torso_y_fwd == false){
			torso_angle_y = torso_angle_move_y + torso_angle_oscillate_y;
			torso_y_fwd = true;
			update = true;
			if(torso_angle_oscillate_y == 0){
				torsoosc_y = false;
			}
		}
	} 

	// send inform messages
	if((sensorAngles[0] - shoulder_angle_left) <= angle_error && inform_shoulder == true){	
		pepper_platform::PepperInfo message;
		message.fin_move_shoulder = true;
		message.fin_move_torso_x = false;
		message.fin_move_torso_y = false;
		message.fin_move_body = false;
		pepper_info.publish(message);	
		inform_shoulder = false;		
	}
	if((sensorAngles[2] - torso_angle_x) <= angle_error && inform_torso_x == true){
		pepper_platform::PepperInfo message;
		message.fin_move_shoulder = false;
		message.fin_move_torso_x = true;
		message.fin_move_torso_y = false;
		message.fin_move_body = false;
		pepper_info.publish(message); 	
		inform_torso_x = false;	
	}
	if((sensorAngles[3] - torso_angle_y) >= -angle_error * 4 && inform_torso_y == true){
		pepper_platform::PepperInfo message;
		message.fin_move_shoulder = false;
		message.fin_move_torso_x = false;
		message.fin_move_torso_y = true;
		message.fin_move_body = false;
		pepper_info.publish(message);
		inform_torso_y = false;
	}
	
	return update; // set to true if any desired angle has changed
}

bool UpdateMovement(){
	bool update = false;

	// get measured position (absolute)
	positioncur = motion.getRobotPosition(true);

	// if destination reached -> stop movement
	if(dstreached() == true){
		if(velocity_x != 0){
			positionstart = positioncur;
			body_move_x = 0.0;
			body_move_y = 0.0;
			newmove = true;
			// send movement finished message
			pepper_platform::PepperInfo message;
			message.fin_move_shoulder = false;
			message.fin_move_torso_x = false;
			message.fin_move_torso_y = false;
			message.fin_move_body = true;
			pepper_info.publish(message); 
		}  		
	}
	
	// send stop move command if destination reached or stop move message received
	if(newmove == true && body_move_x == 0 && body_move_y == 0){
		velocity_x = 0.0;
		velocity_y = 0.0;
		newmove = false;
		moving = false;
		movosc = false;
		stop = true;
		update = true;
	}
	
	// movement without oscillation 
	if(newmove == true && (body_move_x != 0 || body_move_y != 0)){
		// if desired angle reached (to move in correct direction)
		if(((positioncur[2] - std_angle) <= angle_error) && ((positioncur[2] - std_angle) >= -angle_error)){
			velocity_x = velocity_lin;
			velocity_y = 0.0;			
			velocity_theta = 0.0;
			newmove = false;
			moving = true;
			update = true;	
		}else{	
			velocity_x = 0.0;
			velocity_y = 0.0;	
			if(positioncur[2] > std_angle){
				if(velocity_theta != -std_velocity_oscillate_body){
					velocity_theta = -std_velocity_oscillate_body;
					update = true;
				}	
			}else{
				if(velocity_theta != std_velocity_oscillate_body){
					velocity_theta = std_velocity_oscillate_body;
					update = true;
				}	
			}
			
		}	
	}

	// body is already moving and oscillation is desired  
	if(moving == true  && movosc == true){
		movosc_temp = true; // "previous" status of oscillation - needed for finishing oscillation
		body_angle_right = std_angle + body_angle_oscillate;
		body_angle_left = std_angle - body_angle_oscillate;
		if(newmovosc == true){
			velocity_x = velocity_lin;
			velocity_y = velocity_lin * factor_velocity_y;			
			velocity_theta = -velocity_ang;
			newmovosc = false;
			turnright = true;
			update = true;
		}else if(turnright == true && (positioncur[2] - body_angle_right) <= angle_error){ // right angle reached
			velocity_x = velocity_lin;
			velocity_y = -velocity_lin * factor_velocity_y;			
			velocity_theta = velocity_ang;
			turnright = false;			
			update = true;
		}else if(turnright == false && (positioncur[2] - body_angle_left) >= -angle_error){ // left angle reached
			velocity_x = velocity_lin;
			velocity_y = velocity_lin * factor_velocity_y;			
			velocity_theta = -velocity_ang;
			turnright = true;			
			update = true;
		}
	}

	// if oscillation is stopped -> turn to std_angle (finish oscillation)
	if(movosc == false && movosc_temp == true){
		if(((positioncur[2] - std_angle) <= angle_error) && ((positioncur[2] - std_angle) >= -angle_error)){
			movosc_temp = false;
		}else{	
			velocity_x = 0.0;
			velocity_y = 0.0;	
			if(positioncur[2] > std_angle){	
				velocity_theta = -std_velocity_oscillate_body;	
			}else{
				velocity_theta = std_velocity_oscillate_body;	
			}
			update = true;
		}		
	}

	return update; // set to true when velocities have changed
}

bool dstreached(){
	float x = positioncur[0] - positionstart[0];
	float y = positioncur[1] - positionstart[1];
	float dst = pow(((body_move_x*body_move_x)+(body_move_y*body_move_y)),0.5) - pow(((x*x)+(y*y)),0.5);
	if(dst <= 0.0){
		return true;
	}else{
		return false;
	}
}

void callbackUpdateShoulder(const pepper_platform::PepperUpper::ConstPtr& msg){
	std::cout<<"update shoulder"<<std::endl;
	start_shoulder = true;	
	if(msg->mode == true){ 		// oscillate shoulder
		shoulder_angle_oscillate = msg->angle;
		if(shoulder_angle_oscillate != 0){
			shoulderosc = true;
		}
		if(msg->velocity > 1){
			shoulder_velocity_oscillate = std_velocity_shoulder;
		}else if(msg->velocity * std_velocity_shoulder < 0.1){
			shoulder_velocity_oscillate = 0.1;
		}else if(msg->velocity * std_velocity_shoulder >= 0.1){
			shoulder_velocity_oscillate = msg->velocity * std_velocity_shoulder;
		}
	}else if(msg->mode == false){ 	// move shoulder
		inform_shoulder = true;
		shoulder_angle_move = msg->angle;
		if(msg->velocity > 1){
			shoulder_velocity_move = std_velocity_shoulder;
		}else if(msg->velocity * std_velocity_shoulder < 0.1){
			shoulder_velocity_move = 0.1;
		}else if(msg->velocity * std_velocity_shoulder >= 0.1){
			shoulder_velocity_move = msg->velocity * std_velocity_shoulder;
		}			
	}
}

void callbackUpdateTorso(const pepper_platform::PepperUpper::ConstPtr& msg){
	std::cout<<"update torso"<<std::endl;
	if(msg->x == true){ 		// update in x direction - HipPitch
		start_torso_x = true;	
		if(msg->mode == true){ 		// oscillate torso x
			torso_angle_oscillate_x = msg->angle;
			if(torso_angle_oscillate_x != 0){
				torsoosc_x = true;
			}
			if(msg->velocity > 1){
				torso_velocity_oscillate_x = std_velocity_torso;
			}else if(msg->velocity * std_velocity_torso < 0.1){
				torso_velocity_oscillate_x = 0.1;
			}else if(msg->velocity * std_velocity_torso >= 0.1){
				torso_velocity_oscillate_x = msg->velocity * std_velocity_torso;
			}	
		}else if(msg->mode == false){	// move torso
			inform_torso_x = true;
			torso_angle_move_x = msg->angle;
			if(msg->velocity > 1){
				torso_velocity_move_x = std_velocity_torso;
			}else if(msg->velocity * std_velocity_torso < 0.1){
				torso_velocity_move_x = 0.1;
			}else if(msg->velocity * std_velocity_torso >= 0.1){
				torso_velocity_move_x = msg->velocity * std_velocity_torso;
			}	
		}
	} 
	if(msg->x == false){		// update in y direction - HipRoll
		start_torso_y = true;
		if(msg->mode == true){ 		// oscillate torso
			torso_angle_oscillate_y = msg->angle;
			if(torso_angle_oscillate_y != 0){
				torsoosc_y = true;
			}
			if(msg->velocity > 1){
				torso_velocity_oscillate_y = std_velocity_torso;
			}else if(msg->velocity * std_velocity_torso < 0.1){
				torso_velocity_oscillate_y = 0.1;
			}else if(msg->velocity * std_velocity_torso >= 0.1){
				torso_velocity_oscillate_y = msg->velocity * std_velocity_torso;
			}
		}else if(msg->mode == false){ 	// move torso
			inform_torso_y = true;
			torso_angle_move_y = msg->angle;
			if(msg->velocity > 1){
				torso_velocity_move_y = std_velocity_torso;
			}else if(msg->velocity * std_velocity_torso < 0.1){
				torso_velocity_move_y = 0.1;
			}else if(msg->velocity * std_velocity_torso >= 0.1){
				torso_velocity_move_y = msg->velocity * std_velocity_torso;
			}			
		}	
	}
}

void callbackUpdateBody(const pepper_platform::PepperMove::ConstPtr& msg){
	std::cout<<"update body"<<std::endl;
	if(msg->stop == true){ 		// stop message
		if(msg->mode == true){	   // stop oscillation
			body_angle_oscillate = 0.0;
			movosc = false;
		}else{			   // stop movement
			body_move_x = 0.0;
			body_move_y = 0.0;
			newmove = true;
		}	
	}else{
		if(msg->mode == true){ 	// oscillate body
			movosc = true;
			newmovosc = true;
			body_angle_oscillate = msg->theta;
			if(msg->velocity_angular > 1){	// velocity in rad/s between 0.2 and 2.0  (default 1.0)
				velocity_ang = std_velocity_oscillate_body;
			} else if(msg->velocity_angular * std_velocity_oscillate_body < 0.2) {
				velocity_ang = 0.2;
			} else if(msg->velocity_angular * std_velocity_oscillate_body >= 0.2) {
				velocity_ang = msg->velocity_angular * std_velocity_oscillate_body;		
			}
		}
		if(msg->mode == false){ // move body
			positionstart = motion.getRobotPosition(true);
			positioncur = positionstart;
			newmove = true;
			if(msg->velocity_linear > 1){	// velocity in m/s   between 0.1 and 0.55 (default 0.35)
				velocity_lin = std_velocity_move;
			} else if(msg->velocity_linear * std_velocity_move < 0.1) {
				velocity_lin = 0.1;		
			} else if(msg->velocity_linear * std_velocity_move >= 0.1){
				velocity_lin = msg->velocity_linear * std_velocity_move;
			}
			body_move_x = msg->x;
			body_move_y = msg->y;
			
			// calculate angle to move -> std_angle
			if(body_move_x != 0){
				std_angle = positionstart[2] + atan(body_move_y*1.0/body_move_x);
			}else if(body_move_y = 0){
				std_angle = std_angle;
			}else if(body_move_y > 0){
				std_angle = positionstart[2] + M_PI/2.0;
			}else if(body_move_y < 0){
				std_angle = positionstart[2] - M_PI/2.0;
			}
			
			if(std_angle > M_PI){
				std_angle = std_angle - 2*M_PI;			
			}else if(std_angle < -M_PI){
				std_angle = std_angle + 2*M_PI;		
			}
		}
	}	
}
void callbackUpdateEmotion(const pepper_platform::EmotionMessage::ConstPtr& msg){
	// emotions: neutral, angry, happy, sad, fear, content
	// colors:   “white”, “red”, “green”, “blue”, “yellow”, “magenta”, “cyan”
	emotion = msg->emotion.data;
	update_led = true; // emotion has changed
	if(emotion.compare("angry") == 0){
		earintensity = 0.0;
		eyecolor = "red";
		head_angle_pitch = 0.0;
	}else if(emotion.compare("happy") == 0){
		earintensity = 1.0;
		eyecolor = "white";
		head_angle_pitch = -5.0/180.0 * M_PI;	
	}else if(emotion.compare("sad") == 0){
		earintensity = 0.3;
		eyecolor = "blue";
		head_angle_pitch = 20.0/180.0 * M_PI;
	}else if(emotion.compare("fear") == 0){
		earintensity = 1.0;
		eyecolor = "white";
		head_angle_pitch = 10.0/180.0 * M_PI;
	}else{
		earintensity = 1.0;
		eyecolor = "white";
		head_angle_pitch = 0.0;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "pepper_emotion");
	ros::NodeHandle n;
	
	// subscribe and publish	
	pepper_shoulder = n.subscribe("/pepper_shoulder", 2, callbackUpdateShoulder);
	pepper_torso = n.subscribe("/pepper_torso", 2, callbackUpdateTorso);
	pepper_body = n.subscribe("/pepper_body", 2, callbackUpdateBody);
	pepper_emotion = n.subscribe("/change_emotion", 1, callbackUpdateEmotion);
	pepper_info = n.advertise<pepper_platform::PepperInfo>("pepper_platform", 2);

	// set stiffness of the robot to 0.8 (movementts look better)
	std::string stiffname  = "Body";
	float stiffnesses  = 0.8f;
	motion.setStiffnesses(stiffname, stiffnesses);	
	
	// initialize Robot position (set internal position to current position)
	positionstart = motion.getRobotPosition(true);
	positioncur = positionstart;
	std_angle = positionstart[2];
	motion.setMoveArmsEnabled(false, false);

	// initialize angles and leds
	shoulder_angle_left = M_PI * (1.0/2.0 - 10.0/180.0);
	shoulder_angle_right = M_PI * (1.0/2.0 - 10.0/180.0);
	torso_angle_x = -(M_PI * 5.0/180.0);
	torso_angle_y = 0.0;
	head_angle_pitch = 0.0;
	eyecolor = "white";
	earintensity = 1.0;
	
	// set update interval to 5 Hz (effective due to 3 x loop.sleep())
	ros::Rate loop(30);
	
	while(ros::ok){
		// update joint angles
		loop.sleep();
		update_joints = UpdateJoints();
		if(update_joints == true){
			angles = AL::ALValue::array(shoulder_angle_left, shoulder_angle_right, torso_angle_x, torso_angle_y, head_angle_pitch);
			motion.setAngles(jointname, angles, std_velocity_shoulder);

			
		}
		
		// update movement
		loop.sleep();
		update_move = UpdateMovement();
		if(update_move == true){
			if(stop == true){
				motion.stopMove();
				stop = false;
			}else{
				motion.moveToward(velocity_x, velocity_y, velocity_theta);
			}
		}
		
		// update leds
		loop.sleep();
		if(update_led == true){
			led.fadeRGB(eyeled, eyecolor, 0.0);
			led.fade(earled, earintensity, 0.0);
			update_led = false;
		}

		ros::spinOnce();
	}
}

