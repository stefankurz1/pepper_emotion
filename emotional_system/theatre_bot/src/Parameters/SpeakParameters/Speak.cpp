///////////////////////////////////////////////////////////
//  Speak.cpp
//  Implementation of the Class Speak
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Speak.h"


Speak::Speak(){

}



Speak::~Speak(){

}


void Speak::setText(std::string text){
	this->text = text;
}
std::string Speak::getText(){
	return this->text;
}
