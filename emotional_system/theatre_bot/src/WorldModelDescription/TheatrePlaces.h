/*
 * TheatrePlaces.h
 *
 *  Created on: Mar 23, 2015
 *      Author: julian
 */

#ifndef THEATREPLACES_H_
#define THEATREPLACES_H_

class TheatrePlaces {
public:
	TheatrePlaces();
	virtual ~TheatrePlaces();
	void setStageInformation(float maximum_lenght_x, float maximum_lenght_y, float number_rectangles_x, float number_rectangles_y);
	/*
	 * This method returns true if the id exist or false if not
	 * the place_id is the desire place identification and point_x and point_y are two pointers that are going to be changed with the correct position of the place
	 */
	bool getPoinDestination(int place_id, float *point_x, float *point_y);
	float getMaximumLenghtX();
	float getMaximumLenghtY();
	float getNumberRectanglesX();
	float getNumberRectanglesY();
private:
	float maximum_lenght_x;//it should set from file
	float maximum_lenght_y;//it should set from file
	float number_rectangles_x;//it should set from file
	float number_rectangles_y;//it should set from file
	float lenght_rectangle_x; //it is calculated from maximum_lenght/number_rectangles
	float lenght_rectangle_y;
};

#endif /* THEATREPLACES_H_ */
