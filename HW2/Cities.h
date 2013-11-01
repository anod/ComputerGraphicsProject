//
//  Cities.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef CITIES_H
#define CITIES_H

#include "general.h"
#include <vector>

typedef struct
{
	int id;
	int x,y;
	int type;
	int connectedTo;
} CITY;


class Cities
{
public:
	Cities(void);
	~Cities(void);

	void add(int x, int y);

private:
	static const int CITY_WORK = 0;
	static const int CITY_SLEEP = 1;

	std::vector<CITY> mCities;
};

#endif