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
#include "Terrain.h"
#include "Road.h"
#include "BmpTexture.h"

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
	void init();
	void setRoad(Road* road) { mRoad = road; };
	void setTerrain(Terrain* terrain) { mTerrain = terrain; };

	void add(int x, int y);
	void draw();
private:
	static const int CITY_INDUSTRIAL = 0;
	static const int CITY_SLEEP = 1;

	Road* mRoad;
	Terrain* mTerrain;
	std::vector<CITY> mCities;

	BmpTexture* mBuilding1Texture;
	BmpTexture* mBuilding2Texture;
	BmpTexture* mRoof1Texture;
	BmpTexture* mRoof2Texture;


	void connectToNearestCity(CITY city);
	void drawIndustrialCity(CITY city);
	void drawSleepCity(CITY city);
	void drawBuilding(double leftTopX, double leftTopY, double height, double size);

};

#endif