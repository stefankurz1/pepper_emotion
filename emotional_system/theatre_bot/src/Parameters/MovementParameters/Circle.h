///////////////////////////////////////////////////////////
//  Circle.h
//  Implementation of the Class Circle
//  Created on:      04-dic-2014 04:42:41 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(CIRCLE_H_)
#define CIRCLE_H_

#include "Point.h"

class Circle : public Point
{

public:
	Circle();
	virtual ~Circle();

	float getRadio();
	void setRadio(float radio);

private:
	float radio;

};
#endif // !defined(CIRCLE_H_)
