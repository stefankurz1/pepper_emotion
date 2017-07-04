/*
 * ReactiveModelParameters.h
 *
 *  Created on: Mar 25, 2015
 *      Author: julian
 */

#ifndef REACTIVEMODELPARAMETERS_H_
#define REACTIVEMODELPARAMETERS_H_

class ReactiveModelParameters {
public:
	ReactiveModelParameters();
	virtual ~ReactiveModelParameters();
	float getBaseIncrease();
	void setBaseIncrease(float baseIncrease);
	float getDecreaseFactor();
	void setDecreaseFactor(float decreaseFactor);
	float getFactorIncrease();
	void setFactorIncrease(float factorIncrease) ;
	float getIncreaseCoefficient();
	void setIncreaseCoefficient(float increaseCoefficient);
	float getMinimumTimeToImage();
	void setMinimumTimeToImage(float minimumTimeToImage);
	float getSocialBias();
	void setSocialBias(float socialBias);
	int getThreshold();
	void setThreshold(int threshold);
	float getTimeFactorCoefficient();
	void setTimeFactorCoefficient(float timeFactorCoefficient);
private:
	float social_bias;//this is a bias that could be used ... still thinking about it
	float decrease_factor;
	float base_increase;//base to be3 used in the exponential
	float factor_increase;//factor to increase the output of the exponential
	float time_factor_coefficient;
	float increase_coefficient;
	float minimum_time_to_image;//this is the interval to get a new image
	int threshold;

};

#endif /* REACTIVEMODELPARAMETERS_H_ */
