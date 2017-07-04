/*
 * Amplitude.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#include "Amplitude.h"

Amplitude::Amplitude() {
	x = 0;
	y = 0;
	z = 0;
}

Amplitude::~Amplitude() {
	// TODO Auto-generated destructor stub
}

void Amplitude::setDistanceX(float x){
	this->x = x;
}

void Amplitude::setDistanceY(float y){
	this->y = y;
}

void Amplitude::setDistanceZ(float z){
	this->z = z;
}

float Amplitude::getDistanceX(){
	return x;
}

float Amplitude::getDistanceY(){
	return y;
}

float Amplitude::getDistanceZ(){
	return z;
}


