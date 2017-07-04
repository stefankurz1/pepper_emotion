///////////////////////////////////////////////////////////
//  Position.cpp
//  Implementation of the Class Position
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Position.h"


Position::Position(){
	has_pose = false;
}

Position::~Position(){

}

float Position::getYaw(){
	return pose.getYaw();
}

void Position::setHasPose(bool has_pose){
	this->has_pose = has_pose;
}

bool Position::getHasPose(){
	return this->has_pose;
}

void Position::setQuaternionX(float x){
	pose.setX(x);
}

void Position::setQuaternionY(float y){
	pose.setY(y);
}

void Position::setQuaternionZ(float z){
	pose.setZ(z);
}

void Position::setQuaternionW(float w){
	pose.setW(w);
}

void Position::setQuaterion(float x, float y, float z, float w){
	pose.setQuaternion(x,y,z,w);
}

float Position::getQuaterionX(){
	return pose.getX();
}

float Position::getQuaterionY(){
	return pose.getY();
}

float Position::getQuaterionZ(){
	return pose.getZ();
}

float Position::getQuaterionW(){
	return pose.getW();
}

Quaternion Position::getQuaterion(){
	return pose;
}
