/*
 * EventReliefAnalyzer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#include "EventReliefAnalyzer.h"

EventReliefAnalyzer::EventReliefAnalyzer() {
	// TODO Auto-generated constructor stub
	consecutive_events = 3;
	this->increase_factor = 2.0;
	this->decrease_factor = 1.0;
}

EventReliefAnalyzer::~EventReliefAnalyzer() {
	// TODO Auto-generated destructor stub
}

/*
 * For relief should be at least 3 consecutive negative events in the time window
 */
float EventReliefAnalyzer::analyzeEvent(TypeOfSlope type_of_event, float diff_time){
	this->updatePastEvents(type_of_event);
	bool pattern_detected = this->findConsecutiveEventsInTheWindow();
	if(pattern_detected){
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


bool EventReliefAnalyzer::findConsecutiveEventsInTheWindow(){
	for(std::list<TypeOfSlope>::iterator it = previous_events.begin(); it != previous_events.end(); ++it){
		if(!(*it == medium_negative_slope ||*it ==large_negative_slope||*it ==huge_negative_slope)){
			return false;
		}
	}
	return true;
}

/**
 * This method find consecutive events in a dynamic window over a window of events. however, it also moves in all the events
 */
bool EventReliefAnalyzer::findConsecutiveEvents(){
	int half = static_cast<int>(consecutive_events/2);
	int left = 0;
	int right = 0;
	int count = 0;
	std::list<TypeOfSlope>::iterator it;
	for(int i = half; i < previous_events.size() - (consecutive_events-half-1); ++i){
		left = i - half;
		right = consecutive_events -half +i;
		count = 0;
		for(int j = left; j<right; ++j){
			it = previous_events.begin();
			std::advance(it,j);
			if(*it == medium_negative_slope ||*it ==large_negative_slope||*it ==huge_negative_slope){
				++count;
			}else{
				break;
			}
		}
		if(count == consecutive_events){
			return true;
		}
	}
	return false;
}
