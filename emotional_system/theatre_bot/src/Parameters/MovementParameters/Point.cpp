///////////////////////////////////////////////////////////
//  Point.cpp
//  Implementation of the Class Point
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Point.h"


Point::Point(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}



Point::~Point(){

}


float Point::getX(){

	return this->x;
}


float Point::getY(){

	return this->y;
}


float Point::getZ(){

	return this->z;
}


void Point::setX(float x){
	this->x = x;
}


void Point::setY(float y){
	this->y = y;
}


void Point::setZ(float z){
	this->z = z;
}
