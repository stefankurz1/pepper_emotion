/*
 * Quaternion.h
 *
 *  Created on: Jan 21, 2015
 *      Author: julian
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>

class Quaternion {
public:
	Quaternion();
	virtual ~Quaternion();
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setZ(float z);
	float getZ();
	void setW(float w);
	float getW();
	void setQuaternion(float x,float y,float z,float w);
	float getYaw();
	float getPitch();
	float getRoll();

private:
	float x;
	float y;
	float z;
	float w;
};

#endif /* QUATERNION_H_ */
