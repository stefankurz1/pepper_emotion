///////////////////////////////////////////////////////////
//  Landmark.cpp
//  Implementation of the Class Landmark
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Landmark.h"


Landmark::Landmark(){
	this->id_landmakr = -1;
	this->observation = "";
	this->type_landmark = Unknown_Landmark;
}



Landmark::~Landmark(){

}



int Landmark::getIdLandmakr() {
	return this->id_landmakr;
}

void Landmark::setIdLandmakr(int idLandmakr) {
	this->id_landmakr = idLandmakr;
}

std::string Landmark::getObservation()  {
	return this->observation;
}

void Landmark::setObservation(const std::string observation) {
	this->observation = observation;
}

TypeLandmark Landmark::getTypeLandmark()  {
	return this->type_landmark;
}

void Landmark::setTypeLandmark(TypeLandmark typeLandmark) {
	this->type_landmark = typeLandmark;
}


