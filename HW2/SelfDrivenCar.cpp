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
		if (mCityDestination.id == mCityOrigin.id) {
			mCityDestination.id = 0;
		}
		if (mCityDestination.id > 0) {
			if (mCityDestination.x > mCityOrigin.x && mCityDestination.y == mCityOrigin.y) {
				setAngle(PI);
			} else if (mCityDestination.y > mCityOrigin.y && mCityDestination.x == mCityOrigin.x) {
				setAngle(PI/2);
			} else if (mCityDestination.x < mCityOrigin.x && mCityDestination.y == mCityOrigin.y) {
				setAngle(-PI);
			} else if (mCityDestination.y < mCityOrigin.y && mCityDestination.x == mCityOrigin.x) {
				setAngle(-PI/2);
			} 
		}

	}
	if (mCityDestination.id == 0) {
		stop();
		update();
		return;
	}
	double destX = mCityDestination.x - GRID_OFFSET;
	double destZ = mCityDestination.y - GRID_OFFSET;
	if (abs(pos.x - destX) < 0.001f && abs(pos.z - destZ) < 0.001f) {
		stop();
		mCityOrigin = mCityDestination;
		mCityDestination.id = 0;
	} else {
		if (!isMoving()) {
			setSpeed(0.2f);
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