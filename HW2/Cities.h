//
//  Cities.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef CITIES_H
#define CITIES_H

#include "general.h"

#include "Terrain.h"
#include "Road.h"
#include "BmpTexture.h"
class SelfDrivenCarCollection;

class Cities
{
public:
	static const int CITY_INDUSTRIAL = 0;
	static const int CITY_SUBURB = 1;
	static const int CITY_SIZE = 24;

	Cities(void);
	~Cities(void);

	void init();
	void setRoad(Road* road) { mRoad = road; };
	void setTerrain(Terrain* terrain) { mTerrain = terrain; };
	void setCarCollection(SelfDrivenCarCollection* carCollection) { mCarCollection = carCollection; };
	bool isOccupied(int gridX, int gridY) {	return mCitiesOccupied[gridX][gridY]; };

	int normalize(int coord) {
		int num = floor(float(coord)/CITY_SIZE);
		return num*CITY_SIZE;
	}
	int add(int gridX, int gridY);
	int addSpecType(int gridX, int gridY, int type);
	CITY getById(int id) { return mCities[(id - 1)]; };
	CityList getMappedCities(int id) { return mCityMap[id]; };
	WayPoints getWayPoints(int fromId, int toId) { return mCitiesWaypoints[fromId][toId]; };
	void draw();

private:

	Road* mRoad;
	Terrain* mTerrain;
	SelfDrivenCarCollection* mCarCollection;

	CityList mCities;
	CityMap mCityMap;
	CitiesWayPoints mCitiesWaypoints;

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