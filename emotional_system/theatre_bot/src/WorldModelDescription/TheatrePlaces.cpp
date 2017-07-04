/*
 * TheatrePlaces.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: julian
 */

#include "TheatrePlaces.h"

TheatrePlaces::TheatrePlaces() {
	maximum_lenght_x = 0.0;//it should set from file
	maximum_lenght_y = 0.0;//it should set from file
	number_rectangles_x = 0.0;//it should set from file
	number_rectangles_y = 0.0;//it should set from file
	lenght_rectangle_x = 0.0; //it is calculated from maximum_lenght/number_rectangles
	lenght_rectangle_y = 0.0;
}

TheatrePlaces::~TheatrePlaces() {
	// TODO Auto-generated destructor stub
}


void TheatrePlaces::setStageInformation(float maximum_lenght_x, float maximum_lenght_y, float number_rectangles_x, float number_rectangles_y){
	this->maximum_lenght_x = maximum_lenght_x;//it should set from file
	this->maximum_lenght_y = maximum_lenght_y;//it should set from file
	this->number_rectangles_x = number_rectangles_x;//it should set from file
	this->number_rectangles_y = number_rectangles_y;//it should set from file
	this->lenght_rectangle_x = maximum_lenght_x/number_rectangles_x; //it is calculated from maximum_lenght/number_rectangles
	this->lenght_rectangle_y = maximum_lenght_y/number_rectangles_y;
}


bool TheatrePlaces::getPoinDestination(int place_id, float *point_x, float *point_y){
	if(place_id >= number_rectangles_x*number_rectangles_y){
		*point_x = 0.0;
		*point_y = 0.0;
		return false;
	}
	int n,m;
	if(place_id>number_rectangles_y){
		n = static_cast<int>(place_id/number_rectangles_y);
		m = place_id%static_cast<int>(number_rectangles_y);
	}else{
		n = 0;
		m = place_id;
	}
	*point_x = lenght_rectangle_x*n + lenght_rectangle_x/2.0;
	*point_y = lenght_rectangle_y*m + lenght_rectangle_y/2.0;
	return true;
}


float TheatrePlaces::getMaximumLenghtX(){
	return this->maximum_lenght_x;
}
float TheatrePlaces::getMaximumLenghtY(){
	return this->maximum_lenght_y;
}
float TheatrePlaces::getNumberRectanglesX(){
	return this->number_rectangles_x;
}
float TheatrePlaces::getNumberRectanglesY(){
	return this->number_rectangles_y;
}
