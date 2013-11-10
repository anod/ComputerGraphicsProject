//
//  SelfDrivenCarCollection.h
//  Final Project
//
//  Created by Alex Gavrishev.
//
#ifndef SELFDRIVENCARCOLLECTION_H
#define SELFDRIVENCARCOLLECTION_H

#include "SelfDrivenCar.h"

static const int CARS_COLORS_SIZE = 6;
static PIXEL CAR_COLORS[CARS_COLORS_SIZE] = {
	PIX_CYAN,
	PIX_DEEP_PINK,
	PIX_RED,
	PIX_WHITE,
	PIX_GREEN,
	PIX_LT_GREY
};

// Collection of Self-Driven cars
class SelfDrivenCarCollection
{
public:
	SelfDrivenCarCollection(void);
	~SelfDrivenCarCollection(void);

	void init(Road* road, Cities* cities) {
		mRoad = road;
		mCities = cities;
	}
	void add(int cityId);
	void draw3d();
	void drive();

private:
	Road* mRoad;
	Cities* mCities;
	int mColorIdx;

	std::vector<SelfDrivenCar*> mCars;
};

#endif