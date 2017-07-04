/*
 * Amplitude.h
 *
 *  Created on: Dec 6, 2014
 *      Author: julian
 */

#ifndef AMPLITUDE_H_
#define AMPLITUDE_H_

#include "Position.h"

class Amplitude : public Position{
public:
	Amplitude();
	virtual ~Amplitude();

	void setDistanceX(float x);
	void setDistanceY(float y);
	void setDistanceZ(float z);
	float getDistanceX();
	float getDistanceY();
	float getDistanceZ();
private:
	float x;
	float y;
	float z;
};

#endif /* AMPLITUDE_H_ */
