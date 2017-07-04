/*
 * MarkerPosition.h
 *
 *  Created on: Jul 3, 2015
 *      Author: julian
 */

#ifndef MARKERPOSITION_H_
#define MARKERPOSITION_H_

/*
 * This class store the information for the marked used as a landmarks
 */
class MarkerPosition {
public:
	MarkerPosition();
	virtual ~MarkerPosition();
	void setMarkerID(int id);
	int getMarkerID();
	void setMarkerX(float x);
	float getMarkerX();
	void setMarkerY(float y);
	float getMarkerY();
	void setMarkerYaw(float yaw);
	float getMarkerYaw();
	void setMarkerRoll(float roll);
	float getMarkerRoll();
	void setMarkerPitch(float pitch);
	float getMarkerPitch();
private:
	int id;
	float x;
	float y;
	float yaw;
	float pitch;
	float roll;
};

#endif /* MARKERPOSITION_H_ */
