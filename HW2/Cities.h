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
#include <map>

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

	static const int CITY_SIZE = 24;

	void init();
	void setRoad(Road* road) { mRoad = road; };
	void setTerrain(Terrain* terrain) { mTerrain = terrain; };
	bool isOccupied(int gridX, int gridY) {	return mCitiesOccupied[gridX][gridY]; };

	int normalize(int coord) {
		int num = floor(float(coord)/CITY_SIZE);
		return num*CITY_SIZE;
	}
	void add(int gridX, int gridY);
	void draw();
private:
	static const int CITY_INDUSTRIAL = 0;
	static const int CITY_SUBURB = 1;

	Road* mRoad;
	Terrain* mTerrain;
	std::vector<CITY> mCities;
	bool mCitiesOccupied[GRID_SIZE][GRID_SIZE];

	BmpTexture* mBuilding1Texture;
	BmpTexture* mBuilding2Texture;
	BmpTexture* mRoof1Texture;
	BmpTexture* mRoof2Texture;
	BmpTexture* mHouse1Texture;
	BmpTexture* mHouse2Texture;
	BmpTexture* mHouse3Texture;
	BmpTexture* mHouse4Texture;
	BmpTexture* mHouseRoofTexture;

	void connectToNearestCity(CITY city);
	void drawIndustrialCity(CITY city);
	void drawSuburbCity(CITY city);
	void drawBuilding(double leftTopX, double leftTopY, double height, double size, BmpTexture* building, BmpTexture* roof);
	void drawHouse(double leftTopX, double leftTopY, BmpTexture* tex1,  BmpTexture* tex2, BmpTexture* roof);

};

#endif