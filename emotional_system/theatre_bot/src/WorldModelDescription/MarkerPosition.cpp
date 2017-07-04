/*
 * MarkerPosition.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: julian
 */

#include "MarkerPosition.h"

MarkerPosition::MarkerPosition() {
	id = -1;
	x  = 0.0;
	y = 0.0;
	yaw = 0.0;
	roll = 0.0;
	pitch = 0.0;
}

MarkerPosition::~MarkerPosition() {
	// TODO Auto-generated destructor stub
}


void MarkerPosition::setMarkerID(int id){
	this->id = id;
}

int MarkerPosition::getMarkerID(){
	return id;
}

void MarkerPosition::setMarkerX(float x){
	this->x = x;
}

float MarkerPosition::getMarkerX(){
	return x;
}

void MarkerPosition::setMarkerY(float y){
	this->y = y;
}

float MarkerPosition::getMarkerY(){
	return y;
}

void MarkerPosition::setMarkerYaw(float yaw){
	this->yaw = yaw;
}

float MarkerPosition::getMarkerYaw(){
	return yaw;
}

void MarkerPosition::setMarkerRoll(float roll){
	this->roll = roll;
}
float MarkerPosition::getMarkerRoll(){
	return this->roll;
}
void MarkerPosition::setMarkerPitch(float pitch){
	this->pitch = pitch;
}
float MarkerPosition::getMarkerPitch(){
	return pitch;
}

