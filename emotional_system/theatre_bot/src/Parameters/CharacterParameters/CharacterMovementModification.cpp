/*
 * CharacterMovementModification.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: julian
 */

#include "CharacterMovementModification.h"

CharacterMovementModification::CharacterMovementModification() {
	this->longness = 1;
	this->amplitude = 1;
	this->bias = 0;
}

CharacterMovementModification::~CharacterMovementModification() {
}

void CharacterMovementModification::setBias(float bias){
	this->bias = bias;
}

void CharacterMovementModification::setAmplitude(float amplitude){
	this->amplitude = amplitude;
}

void CharacterMovementModification::setLongness(float longness){
	this->longness = longness;
}

float CharacterMovementModification::getBias(){
	return this->bias;
}

float CharacterMovementModification::getAmplitude(){
	return this->amplitude;
}

float CharacterMovementModification::getLongness(){
	return this->longness;
}

void CharacterMovementModification::setActionName(std::string action_name){
	this->action_name = action_name;
}

std::string CharacterMovementModification::getActionName(){
	return this->action_name;
}
