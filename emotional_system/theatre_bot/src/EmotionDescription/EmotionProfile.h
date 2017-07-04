/*
 * EmotionProfile.h
 *
 *  Created on: Dec 5, 2014
 *      Author: julian
 */

#ifndef EMOTIONPROFILE_H_
#define EMOTIONPROFILE_H_

#include "ActionChanges.h"
#include "EmotionType.h"

class EmotionProfile {
public:
	EmotionProfile();
	virtual ~EmotionProfile();

	string getEmotionProfileName();
	void setEmotionProfileName(string emotion_profile_name);
	string getEmotionProfileAction();
	void setEmotionProfileAction(string emotion_profile_action);
	string getEmotionProfileEmotion();
	void setEmotionProfileEmotion(string emotion_profile_emotion);
	string getEmotionProfileDescription();
	void setEmotionProfileDescription(string emotion_profile_description);

	void setTypeActionEmotion(EmotionType type_action_emotion);
	EmotionType getTypeActionEmotion();

	void addActionChanges(ActionChanges * action);
	vector<ActionChanges *> getActionChanges();
private:
	/**
	 * it is the name of the emotion that is described in this profile
	 */
	string emotion_profile_name;
	/**
	 * this is the name of the action for the current emotion
	 */
	string emotion_profile_action;
	/**
	 * This is the base action used in this profile
	 */
	string emotion_profile_emotion;
	/**
	 *this could be used to add some additional information that could be help to understand the current profile
	 */
	string emotion_profile_description;
	/*This tells which kind of emotion parameter is. At the moment I just have implemented emotion movement parameter, but
	 * it could be also added the emotion speak parameter
	 * */
	EmotionType emotion_type;
	vector<ActionChanges *> emotion_profile_actions;
};

#endif /* EMOTIONPROFILE_H_ */
