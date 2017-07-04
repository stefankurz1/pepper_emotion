///////////////////////////////////////////////////////////
//  Position.h
//  Implementation of the Class Position
//  Created on:      04-dic-2014 04:42:42 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(POSITION_H_)
#define POSITION_H_

#include "../Parameter.h"
#include "Quaternion.h"

class Position : public Parameter
{

public:
	Position();
	virtual ~Position();

	void setQuaternionX(float x);
	void setQuaternionY(float y);
	void setQuaternionZ(float z);
	void setQuaternionW(float w);
	void setQuaterion(float x, float y, float z, float w);

	float getQuaterionX();
	float getQuaterionY();
	float getQuaterionZ();
	float getQuaterionW();

	Quaternion getQuaterion();

	float getYaw();

	void setHasPose(bool has_pose);
	bool getHasPose();
protected:
	//This variable says if there was a pose introduced in the parameters
	bool has_pose;
	Quaternion pose;

};
#endif // !defined(POSITION_H_)
