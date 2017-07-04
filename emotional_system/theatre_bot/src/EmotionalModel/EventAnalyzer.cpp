/*
 * EventAnalyzer.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: julian
 */

#include "EventAnalyzer.h"

EventAnalyzer::EventAnalyzer() {
	event_window_size = 0;
	intensity = 0;
}

EventAnalyzer::~EventAnalyzer() {
	// TODO Auto-generated destructor stub
}

void EventAnalyzer::setEventWindowSize(int window_size){
	this->event_window_size = window_size;
}

int EventAnalyzer::getEventWindowSize(){
	return this->event_window_size;
}

void EventAnalyzer::restart(){
	previous_events.clear();
}
/*
 * This method update the vector with all the events, calling this method should be done before any other processing in the analyze event method
 */
void EventAnalyzer::updatePastEvents(TypeOfSlope new_event){
	if(previous_events.size()<event_window_size){
		previous_events.push_front(new_event);
	}else{
		previous_events.pop_back();
		previous_events.push_front(new_event);
	}
}


void EventAnalyzer::setIncreaseFactor(float factor){
	this->increase_factor = factor;
}

void EventAnalyzer::setDecreaseFactor(float factor){
	this->decrease_factor = factor;
}
