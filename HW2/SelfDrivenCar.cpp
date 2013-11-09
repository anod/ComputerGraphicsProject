#include "SelfDrivenCar.h"


SelfDrivenCar::SelfDrivenCar(void)
{
	mCityDestination.id = 0;
	mCityOrigin.id = 0;
}


SelfDrivenCar::~SelfDrivenCar(void)
{
}


void SelfDrivenCar::drive()
{
	if (mCityDestination.id == 0) {
		mCityDestination = findCityDest();

	}
	if (mCityDestination.id == 0) {
		stop();
		update();
		return;
	}
	double destX = mCityDestination.x - GRID_OFFSET;
	double destZ = mCityDestination.y - GRID_OFFSET;
	if (pos.x == destX && pos.z == destZ) {
		stop();
		mCityOrigin = mCityDestination;
		mCityDestination.id = 0;
	} else {
		if (!isMoving()) {
			speed = 0.2f;
//			forward();
		}
	}

	update();
}

CITY SelfDrivenCar::findCityDest()
{
	CITY empty;
	empty.id = 0;
	if (mCityOrigin.id == 0) {
		return empty;
	}
	CityList list = mCities->getMappedCities(mCityOrigin.id);
	int size = list.size();
	if (size == 0) {
		return empty;
	}
	if (size == 1) {
		return list[0];
	}
	int newDestIdx = rand() % size;
	return list[newDestIdx];
}