/*
 * EventAnalyzer.h
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#ifndef EVENTANALYZER_H_
#define EVENTANALYZER_H_

#include "TypeOfSlope.h"
#include <list>
/**
 * This class is the base to generate different emotion analyzers, this class has an abstract function that should implemented
 * the idea is to generate a class for each of emotion that it is pretended to identify.
 * the window size is the amount of events that is going to consider the analyzer
 */

class EventAnalyzer {
public:
	EventAnalyzer();
	virtual ~EventAnalyzer();
	void setEventWindowSize(int window_size);
	int getEventWindowSize();
	void setIncreaseFactor(float factor);
	void setDecreaseFactor(float factor);
	void restart();//Cleans the events
	/*
	 * In this action is generated the intensity of each emotion. the difference of time is necessary to calculate the correct intensity
	 * If the difference of time is big, the increase and decrease should be proportional to this.
	 */
	float virtual analyzeEvent(TypeOfSlope type_of_event, float diff_time) = 0;
protected:
	int event_window_size; //number of events that is going to be consider
	float increase_factor;
	float decrease_factor;
	std::list<TypeOfSlope> previous_events;
	float intensity; //Intensity in the action
	void updatePastEvents(TypeOfSlope new_event); //This method update the vector with all the events, calling this method should be done before any other processing in the analyze event method
};

#endif /* EVENTANALYZER_H_ */
