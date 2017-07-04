/*
 * NodeKeepon.h
 *
 *  Created on: Jan 23, 2015
 *      Author: julian
 */

#ifndef NODEKEEPON_H_
#define NODEKEEPON_H_

#include "ros/ros.h"
extern "C"{
	#include "lib/libKeepon.h"
}
#include "theatre_bot/KeeponMessage.h"

class NodeKeepon {
public:
	NodeKeepon();
	virtual ~NodeKeepon();
	void setDevice(char * device);
	void setPort(int port);
	void init();

	void callbackActionExecution(const theatre_bot::KeeponMessage::ConstPtr& msg);
	void sendKeeponInformation();
	void setPublisher(ros::Publisher *pub_action_parameter);
private:
	char * device;
	int port;
	float last_tilt;
	float last_pan;
	float last_side;
	float last_pon;
	ros::Publisher *pub_action_parameter;
};

#endif /* NODEKEEPON_H_ */
