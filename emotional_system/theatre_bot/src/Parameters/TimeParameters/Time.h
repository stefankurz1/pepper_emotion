///////////////////////////////////////////////////////////
//  Time.h
//  Implementation of the Class Time
//  Created on:      04-dic-2014 04:42:43 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(TIME_H_)
#define TIME_H_

#include "../Parameter.h"

/**
 * parameters where the time plays a role
 */
class Time : public Parameter
{

public:
	Time();
	virtual ~Time();
	void setTime(float time);
	float getTime();
private:
	float time;

};
#endif // !defined(TIME_H_)
