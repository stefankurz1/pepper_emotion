///////////////////////////////////////////////////////////
//  Time.cpp
//  Implementation of the Class Time
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Time.h"


Time::Time(){
	this->time = 0;
}



Time::~Time(){

}


void Time::setTime(float time){
	this->time = time;
}

float Time::getTime(){
	return this->time;
}
