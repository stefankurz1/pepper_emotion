///////////////////////////////////////////////////////////
//  Velocity.h
//  Implementation of the Class Velocity
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(VELOCITY_H_)
#define VELOCITY_H_

#include "Time.h"

class Velocity : public Time
{

public:
	Velocity();
	virtual ~Velocity();

	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);

private:
	float x;
	float y;
	float z;

};
#endif // !defined(VELOCITY_H_)
