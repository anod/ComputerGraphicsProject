#include "SelfDrivenCar.h"
#include "Cities.h"


SelfDrivenCar::SelfDrivenCar(void)
{
	mCityDestination.id = 0;
	mCityOrigin.id = 0;
}


SelfDrivenCar::~SelfDrivenCar(void)
{
}

void SelfDrivenCar::setCities(int cityId, Cities* cities) { 
		mCityOrigin = cities->getById(cityId);
		mLastWaypoint.x = mCityOrigin.x;
		mLastWaypoint.y = mCityOrigin.y;
		mCities = cities; 
		// set position of the car to the middle of the city
		setPosition(mCityOrigin.x - GRID_OFFSET,0, mCityOrigin.y - GRID_OFFSET);
};

void SelfDrivenCar::drive()
{
	if (mCityDestination.id == 0) {
		mCityDestination = findCityDest();
		if (mCityDestination.id > 0) {
			// No turns on the road -> next waypoint will be destination
			if (isEqual(mCityDestination.x,mCityOrigin.x,0.1f) || isEqual(mCityDestination.y,mCityOrigin.y,0.1f)) {
				mNextWaypoint.x = mCityDestination.x;
				mNextWaypoint.y = mCityDestination.y;
			} else {

				mNextWaypoint.x = mCityOrigin.x; 
				mNextWaypoint.y = mCityDestination.y; 
			}
			adjustAngle();
		}

	}
	if (mCityDestination.id == 0) {
		stop();
		update();
		return;
	}
	double destX = mNextWaypoint.x - GRID_OFFSET;
	double destZ = mNextWaypoint.y - GRID_OFFSET;
	if (isEqual(pos.x,destX,0.01f) && isEqual(pos.z,destZ,0.01f)) {
		if (isEqual(mNextWaypoint.x,mCityDestination.x,0.1f) && isEqual(mNextWaypoint.y,mCityDestination.y,0.1f)) {
			stop();
			mCityOrigin = mCityDestination;
			mLastWaypoint.x = mCityOrigin.x;
			mLastWaypoint.y = mCityOrigin.y;
			setPosition(mCityOrigin.x - GRID_OFFSET,0, mCityOrigin.y - GRID_OFFSET);
			mCityDestination.id = 0;
		} else {
			mLastWaypoint = mNextWaypoint;
			mNextWaypoint.x = mCityDestination.x;
			mNextWaypoint.y = mCityDestination.y;
			setPosition(mNextWaypoint.x - GRID_OFFSET,0, mNextWaypoint.y - GRID_OFFSET);
			adjustAngle();
		}
	} else {
		if (!isMoving()) {
			setSpeed(0.2f);
		}
	}

	update();
}

bool SelfDrivenCar::isEqual(double a, double b, double precision) {
	return abs(a-b) < precision;
}

void SelfDrivenCar::adjustAngle()
{
		if (mNextWaypoint.x > mLastWaypoint.x && mNextWaypoint.y == mLastWaypoint.y) {
			setAngle(PI);
		} else if (mNextWaypoint.y > mLastWaypoint.y && mNextWaypoint.x == mLastWaypoint.x) {
			setAngle(PI/2);
		} else if (mNextWaypoint.x < mLastWaypoint.x && mNextWaypoint.y == mLastWaypoint.y) {
			setAngle(0);
		} else if (mNextWaypoint.y < mLastWaypoint.y && mNextWaypoint.x == mLastWaypoint.x) {
			setAngle(-PI/2);
		} 

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

	CityList others;
	for (CityList::iterator it = list.begin(); it != list.end(); ++it) {
		CITY other = *it;
		if (other.id != mCityOrigin.id) {
			others.push_back(other);
		}
	}
	size = others.size();
	if (size == 1) {
		return others[0];
	}
	int newDestIdx = rand() % size;
	return others[newDestIdx];
}