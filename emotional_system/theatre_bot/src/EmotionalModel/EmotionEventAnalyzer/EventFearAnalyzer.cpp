/*
 * EventFearAnalyzer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#include "EventFearAnalyzer.h"

EventFearAnalyzer::EventFearAnalyzer() {
	increase_factor = 2.0;
	decrease_factor = 1.0;
}

EventFearAnalyzer::~EventFearAnalyzer() {
	// TODO Auto-generated destructor stub
}


/*
 * Cases for fear are:
 * huge_slope
 */
float EventFearAnalyzer::analyzeEvent(TypeOfSlope type_of_event, float diff_time){
	this->updatePastEvents(type_of_event);
	int count_occurences = 0;
	if(type_of_event == large_positive_slope){
		++count_occurences;
	}
	bool pattern = this->findConsecutiveEventsInTheWindow();
	if(count_occurences ==1 || pattern){
		intensity = intensity + increase_factor*diff_time;
		if(intensity >1){
			intensity = 1;
		}
	}else{
		intensity = intensity - decrease_factor*diff_time;
		if(intensity<0){
			intensity = 0;
		}
	}
	//Analyze event
	return intensity;
}

bool EventFearAnalyzer::findConsecutiveEventsInTheWindow(){
	for(std::list<TypeOfSlope>::iterator it = previous_events.begin(); it != previous_events.end(); ++it){
		if(!(*it == large_positive_slope || *it == huge_positive_slope)){
			return false;
		}
	}
	return true;
}
