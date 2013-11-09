//
//  SelfDrivenCar.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef SELFDRIVENCAR_H
#define SELFDRIVENCAR_H

#include "car.h"
#include "Cities.h"

class SelfDrivenCar :
	public Car
{
public:
	SelfDrivenCar(void);
	~SelfDrivenCar(void);

	void drive();
	void setCities(int cityId, Cities* cities) { 
		mCityOrigin = cities->getById(cityId);
		mCities = cities; 
		// set position of the car to the middle of the city
		setPosition(mCityOrigin.x - GRID_OFFSET,0, mCityOrigin.y - GRID_OFFSET);
	};

private:
	CITY mCityOrigin;
	CITY mCityDestination;

	Cities* mCities;

	CITY findCityDest();

};

#endif

