///////////////////////////////////////////////////////////
//  Velocity.cpp
//  Implementation of the Class Velocity
//  Created on:      04-dic-2014 04:42:44 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Velocity.h"


Velocity::Velocity(){
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}



Velocity::~Velocity(){

}





float Velocity::getX(){

	return this->x;
}


float Velocity::getY(){

	return this->y;
}


float Velocity::getZ(){

	return this->z;
}


void Velocity::setX(float x){
	this->x = x;
}


void Velocity::setY(float y){
	this->y = y;
}


void Velocity::setZ(float z){
	this->z = z;
}
