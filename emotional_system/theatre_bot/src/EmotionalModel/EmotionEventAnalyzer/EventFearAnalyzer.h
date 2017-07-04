/*
 * EventFearAnalyzer.h
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#ifndef EVENTFEARANALYZER_H_
#define EVENTFEARANALYZER_H_

#include "../EventAnalyzer.h"

class EventFearAnalyzer: public  EventAnalyzer{
public:
	EventFearAnalyzer();
	virtual ~EventFearAnalyzer();
	float analyzeEvent(TypeOfSlope type_of_event, float diff_time);
private:
	bool findConsecutiveEventsInTheWindow();
};

#endif /* EVENTFEARANALYZER_H_ */
