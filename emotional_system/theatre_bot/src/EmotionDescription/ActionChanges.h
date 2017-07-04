/*
 * ActionChanges.h
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#ifndef ACTIONCHANGES_H_
#define ACTIONCHANGES_H_

#include <cstdlib>
#include <vector>

#include "../Parameters/EmotionalParameters/EmotionParameter.h"


using std::string;
using std::vector;
/**
 * this class containts the changes that should be done to a specific action to
 * show emotion in a general action. For example to show the happines for move, it
 * is necessary to changes several actios as: oscillateshoulder, oscillatemove, etc
 *
 * first change, is should be added two new vectors of emotion parameters: one for y and z.
 * this was done because there are platforms that have more degrees of freedom that just in one axis (e.g. Keepon)
 */
class ActionChanges {
public:
	ActionChanges();
	virtual ~ActionChanges();

	/*
	 * It gives the JSON with all the parameters
	 * */
	string getJSONParameters();
	void setActionThatModyfies(string action_name);
	string getActionThatModyfies();
	//X axis
	vector<EmotionParameter *> copyVectorParameters();
	vector<EmotionParameter *> getVectorParameters();
	void setVectorParameters(vector<EmotionParameter *> parameters);
	void addEmotionParameter(EmotionParameter *parameter);
	//Y axis
	vector<EmotionParameter *> copyVectorParametersY();
	vector<EmotionParameter *> getVectorParametersY();
	void setVectorParametersY(vector<EmotionParameter *> parameters);
	void addEmotionParameterY(EmotionParameter *parameter);
	//Z axis
	vector<EmotionParameter *> copyVectorParametersZ();
	vector<EmotionParameter *> getVectorParametersZ();
	void setVectorParametersZ(vector<EmotionParameter *> parameters);
	void addEmotionParameterZ(EmotionParameter *parameter);
	//General info
	void setReference(float reference);
	void setRepetition(bool repeat);
	float getReference();
	bool getRepetition();
	void clearVectorsParameters();
	void clearVectorParameters();
	void clearVectorParametersY();
	void clearVectorParametersZ();

private:
	//Action that should be modify
	string action_that_changes;
	//list of parameters associated to this action
	vector<EmotionParameter *> action_emotion_parameters;//X

	vector<EmotionParameter *> action_emotion_parameters_y;//Y

	vector<EmotionParameter *> action_emotion_parameters_z;//Z
	//Bool this tells if the changes in the action should be repeated
	bool repeat;
	//This says the intervals to repeat the action
	float reference;
};

#endif /* ACTIONCHANGES_H_ */
