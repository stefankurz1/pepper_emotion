///////////////////////////////////////////////////////////
//  Square.h
//  Implementation of the Class Square
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(SQUARE_H_)
#define SQUARE_H_

#include "Point.h"

class Square : public Point
{

public:
	Square();
	virtual ~Square();

	float getDeletaX();
	float getDeltaY();
	void setDeltaX(float delta_x);
	void setDeltaY(float delta_y);

private:
	float delta_x;
	float delta_y;

};
#endif // !defined(SQUARE_H_)
