///////////////////////////////////////////////////////////
//  Landmark.h
//  Implementation of the Class Landmark
//  Created on:      04-dic-2014 04:42:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(LANDMARK_H_)
#define LANDMARK_H_

#include "TypeLandmark.h"
#include "Position.h"

/**
 * For the first implementation is going to used just and Id and the system should
 * be know how to use this information
 */
class Landmark : public Position
{

public:
	Landmark();
	virtual ~Landmark();
	int getIdLandmakr();
	void setIdLandmakr(int idLandmakr);
	std::string getObservation();
	void setObservation(std::string observation);
	TypeLandmark getTypeLandmark();
	void setTypeLandmark(TypeLandmark typeLandmark);
private:
	int id_landmakr;
	std::string observation;
	TypeLandmark type_landmark;

};
#endif // !defined(LANDMARK_H_)
