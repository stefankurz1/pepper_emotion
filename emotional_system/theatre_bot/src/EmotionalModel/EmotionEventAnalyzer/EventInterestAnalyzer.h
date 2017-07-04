/*
 * EventInterestAnalyzer.h
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#ifndef EVENTINTERESTANALYZER_H_
#define EVENTINTERESTANALYZER_H_

#include "../EventAnalyzer.h"

class EventInterestAnalyzer: public EventAnalyzer {
public:
	EventInterestAnalyzer();
	virtual ~EventInterestAnalyzer();
	float analyzeEvent(TypeOfSlope type_of_event, float diff_time);
private:
	bool findConsecutiveEventsInTheWindow();
};

#endif /* EVENTINTERESTANALYZER_H_ */
