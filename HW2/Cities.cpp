#include "Cities.h"


Cities::Cities(void)
{
}


Cities::~Cities(void)
{
}

void Cities::add(int x, int y) {
	CITY city;
	city.id = mCities.size() + 1;
	city.connectedTo = 0;
	city.x = x;
	city.y = y;
	city.type = rand() % 2;
	mCities.push_back(city);

	if (mCities.size() > 0) {

	}
}

