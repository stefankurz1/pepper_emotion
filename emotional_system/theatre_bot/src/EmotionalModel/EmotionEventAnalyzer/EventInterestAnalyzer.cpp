/*
 * EventInterestAnalyzer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#include "EventInterestAnalyzer.h"

EventInterestAnalyzer::EventInterestAnalyzer() {
	this->increase_factor = 2.0;
	this->decrease_factor = 1.0;
}

EventInterestAnalyzer::~EventInterestAnalyzer() {
	// TODO Auto-generated destructor stub
}

/*
 * For this one there should be at least three consecutive medium slope events
 */
float EventInterestAnalyzer::analyzeEvent(TypeOfSlope type_of_event, float diff_time){
	this->updatePastEvents(type_of_event);
	bool pattern = this->findConsecutiveEventsInTheWindow();
	if(pattern){
		intensity = intensity + increase_factor*diff_time;
		if(intensity>1){
			intensity = 1;
		}
	}else{
		intensity = intensity - decrease_factor*diff_time;
		if(intensity<0){
			intensity = 0;
		}
	}
	return intensity;
}

bool EventInterestAnalyzer::findConsecutiveEventsInTheWindow(){
	for(std::list<TypeOfSlope>::iterator it = previous_events.begin(); it != previous_events.end(); ++it){
		if(!(*it == medium_positive_slope||*it == small_positive_slope)){
			return false;
		}
	}
	return true;
}
