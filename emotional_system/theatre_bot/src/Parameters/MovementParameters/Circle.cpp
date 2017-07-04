///////////////////////////////////////////////////////////
//  Circle.cpp
//  Implementation of the Class Circle
//  Created on:      04-dic-2014 04:42:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Circle.h"


Circle::Circle(){
	this->radio = 0.0;
}



Circle::~Circle(){

}



float Circle::getRadio(){

	return this->radio;
}


void Circle::setRadio(float radio){
	this->radio = radio;
}
