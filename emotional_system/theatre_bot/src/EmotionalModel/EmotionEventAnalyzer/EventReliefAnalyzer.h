/*
 * EventReliefAnalyzer.h
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#ifndef EVENTRELIEFANALYZER_H_
#define EVENTRELIEFANALYZER_H_

#include "../EventAnalyzer.h"

class EventReliefAnalyzer: public EventAnalyzer {
public:
	EventReliefAnalyzer();
	virtual ~EventReliefAnalyzer();
	float analyzeEvent(TypeOfSlope type_of_event, float diff_time);
private:
	//Consecutive events necessary to trigger addition in the emotion
	int consecutive_events;
	bool findConsecutiveEventsInTheWindow();
	/**
	 * This method find consecutive events in a dynamic window over a window of events. however, it also moves in all the events
	 */
	bool findConsecutiveEvents();
};

#endif /* EVENTRELIEFANALYZER_H_ */
