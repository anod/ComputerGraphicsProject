//
//  SelfDrivenCar.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef SELFDRIVENCAR_H
#define SELFDRIVENCAR_H

#include "car.h"
class Cities;

class SelfDrivenCar :
	public Car
{
public:
	SelfDrivenCar(void);
	~SelfDrivenCar(void);

	void drive();
	void setCities(int cityId, Cities* cities);

private:
	CITY mCityOrigin;
	CITY mCityDestination;
	THREE mNextWaypoint;
	THREE mLastWaypoint;

	WayPoints mWayPoints;

	Cities* mCities;

	CITY findCityDest();
	void adjustAngle();
	bool isEqual(double a, double b, double precision);
};

#endif

