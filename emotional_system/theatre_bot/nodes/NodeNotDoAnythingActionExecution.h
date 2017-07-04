/*
 * NodeNotDoAnythingActionExecution.h
 *
 *  Created on: Jan 22, 2015
 *      Author: julian
 */

#ifndef NODENOTDOANYTHINGACTIONEXECUTION_H_
#define NODENOTDOANYTHINGACTIONEXECUTION_H_

#include "ros/ros.h"
#include "ros/time.h"
#include "theatre_bot/ActionExecutionMessage.h"
#include "../src/json/json/json.h"

class NodeNotDoAnythingActionExecution {
public:
	NodeNotDoAnythingActionExecution();
	virtual ~NodeNotDoAnythingActionExecution();

	void callbackNewActionParameters(const theatre_bot::ActionExecutionMessage::ConstPtr& msg);

	void executeTime(float time);
	void setPublisherActionSynch(ros::Publisher *pub_message);

	bool getIsExecuting();
	void isActionFinish();
	void synchEmotion();
private:
	ros::Publisher *pub_action_synch;
	std::string action_name;
	float time_to_wait;
	ros::Time action_strated_at_time;
	ros::Time emotinal_strated_at_time;
	ros::Time current_time;
	ros::Duration difference;
	float emotional_time_to_wait;
	bool repeat_emotional;
	bool is_executing;
	bool emotinal_messsage;
};

#endif /* NODENOTDOANYTHINGACTIONEXECUTION_H_ */
