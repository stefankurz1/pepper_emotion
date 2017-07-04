/*
 * EventSurpriseAnalyzer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#include "EventSurpriseAnalyzer.h"

EventSurpriseAnalyzer::EventSurpriseAnalyzer() {
	this->increase_factor = 100.0;
	this->decrease_factor = 2.0;

}

EventSurpriseAnalyzer::~EventSurpriseAnalyzer() {
	// TODO Auto-generated destructor stub
}

/*
 * For surprise should be just one huge slope event in the whole window
 */
float EventSurpriseAnalyzer::analyzeEvent(TypeOfSlope type_of_event, float diff_time){
	this->updatePastEvents(type_of_event);
	int count_occurrences = 0;
	if(type_of_event == huge_positive_slope){
		for(std::list<TypeOfSlope>::iterator it = previous_events.begin(); it != previous_events.end(); ++it){
			if(*it == huge_positive_slope ||*it == large_positive_slope){
				++count_occurrences;
				if(count_occurrences>1){
					break;
				}
			}
		}
	}
	//If there is just one occurrence it should put the intensity to 1, else it should reduce the previous intensity
	if(count_occurrences == 1){
		intensity = intensity + increase_factor*diff_time;
		if(intensity>1){
			intensity = 1;
		}
	}else{
		intensity  = intensity - decrease_factor*diff_time;
		if(intensity<0){
			intensity = 0;
		}
	}
	return intensity;
}
