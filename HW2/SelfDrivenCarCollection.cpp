#include "SelfDrivenCarCollection.h"


SelfDrivenCarCollection::SelfDrivenCarCollection(void)
{
	mColorIdx = 0;
}


SelfDrivenCarCollection::~SelfDrivenCarCollection(void)
{
}

void SelfDrivenCarCollection::add(int cityId) {
	SelfDrivenCar* car = new SelfDrivenCar();
	car->setRoad(mRoad);
	car->setColor(CAR_COLORS[mColorIdx]);
	car->setAngle(PI/2);
	car->setCities(cityId, mCities);
	mCars.push_back(car);
	mColorIdx++;
	if (mColorIdx >= CARS_COLORS_SIZE) {
		mColorIdx = 0;
	}
}

void SelfDrivenCarCollection::draw3d() {
	for (std::vector<SelfDrivenCar*>::iterator it = mCars.begin(); it != mCars.end(); ++it) {
		SelfDrivenCar* other = *it;
		other->draw3d();
	}
}

void SelfDrivenCarCollection::drive() {
	for (std::vector<SelfDrivenCar*>::iterator it = mCars.begin(); it != mCars.end(); ++it) {
		SelfDrivenCar* other = *it;
		other->drive();
	}
}