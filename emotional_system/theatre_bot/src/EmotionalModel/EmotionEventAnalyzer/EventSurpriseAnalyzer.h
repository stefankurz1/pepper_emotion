/*
 * EventSurpriseAnalyzer.h
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#ifndef EVENTSURPRISEANALYZER_H_
#define EVENTSURPRISEANALYZER_H_

#include "../EventAnalyzer.h"

class EventSurpriseAnalyzer: public EventAnalyzer {
public:
	EventSurpriseAnalyzer();
	virtual ~EventSurpriseAnalyzer();
	float analyzeEvent(TypeOfSlope type_of_event, float diff_time);
};

#endif /* EVENTSURPRISEANALYZER_H_ */
