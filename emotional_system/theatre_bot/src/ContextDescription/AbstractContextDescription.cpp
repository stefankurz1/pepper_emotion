///////////////////////////////////////////////////////////
//  AbstractContextDescription.cpp
//  Implementation of the Class AbstractContextDescription
//  Created on:      04-dic-2014 04:41:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "AbstractContextDescription.h"


AbstractContextDescription::AbstractContextDescription(){
	this->context_priority = UnknownContextPriority;
	this->predecessor = 0;
	this->is_primary = false;
	this->is_emotional = false;
}


void AbstractContextDescription::setIsPrimaryContext(bool is_primary_context){
	this->is_primary = is_primary_context;
}

bool AbstractContextDescription::getIsPrimaryContext(){
	return this->is_primary;
}

AbstractContextDescription::~AbstractContextDescription(){

}

void AbstractContextDescription::setPredecessor(AbstractContextDescription *predecessor){
	this->predecessor = predecessor;
}

AbstractContextDescription * AbstractContextDescription::getPredecessor(){
	return this->predecessor;
}

void AbstractContextDescription::setIsEmotional(bool is_emotional){
	this->is_emotional = is_emotional;
}


bool AbstractContextDescription::getIsEmotional(){
	return is_emotional;
}
