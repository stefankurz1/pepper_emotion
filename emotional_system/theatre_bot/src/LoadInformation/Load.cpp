///////////////////////////////////////////////////////////
//  Load.cpp
//  Implementation of the Class Load
//  Created on:      04-dic-2014 04:42:19 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "Load.h"


Load::Load(){

}



Load::~Load(){

}


void Load::setDirectoryPath(std::string path){
	this->directory_path = path;
}

std::string Load::getDirectoryPath(){
		return this->directory_path;
}


void Load::LoadInformation(){

}

bool Load::has_suffix(const std::string& s, const std::string& suffix) {
	return (s.size() >= suffix.size())
			&& equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}
