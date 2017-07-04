///////////////////////////////////////////////////////////
//  Square.cpp
//  Implementation of the Class Square
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Square.h"


Square::Square(){
	this->delta_x = 0.0;
	this->delta_y = 0.0;
}



Square::~Square(){

}


float Square::getDeletaX(){

	return this->delta_x;
}


float Square::getDeltaY(){

	return this->delta_y;
}


void Square::setDeltaX(float delta_x){
	this->delta_x = delta_x;
}


void Square::setDeltaY(float delta_y){
	this->delta_y = delta_y;
}
