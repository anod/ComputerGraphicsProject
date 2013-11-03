//
//  Overflow.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef OVERFLOW_H
#define OVERFLOW_H

#include "general.h"
#include "Terrain.h"
#include "Road.h"
#include "Cities.h"

typedef struct
{
	int count;
	int x1,y1,x2,y2;
} MOUSE_CLICK;

class Overflow{
public:
	Overflow(void);
	~Overflow(void);
	void onMouseClick();
	void init(Terrain* terrain, Road* road, Cities* cities);
	void draw2d();
	void onMouseClick(int button, int state, int x, int y);
	void onMouseMove(int x, int y);
private:
	static const int MENU_ITEM_HEIGHT = 10;
	static const int MENU_ITEM_X = -(GRID_SIZE/2)+2;// GRID_SIZE //0;
	static const int MENU_ITEM_Y = -(GRID_SIZE/2)+2; //5;
	static const int MENU_NO_ITEM = -1;
	static const int MENU_ITEM_COUNT = 4;
	static const int MENU_ITEM_SPACE = 1;

	static const int MENU_ITEM_HILL = 0;
	static const int MENU_ITEM_VALLEY = 1;
	static const int MENU_ITEM_ROAD = 2;
	static const int MENU_ITEM_CITY = 3;

	int mMenuSelectedItem;

	MOUSE_CLICK mClick;

	Terrain* mTerrain;
	Road* mRoad;
	Cities* mCities;

	THREE mMousePos;

	void drawItem(int item, int x, int y);

	void setMenuSelectedItem(int item);
	int getMenuSelectedItem();
	int detectSelectedItem(int x, int y);

	void drawSquare(int x1, int y1, int x2, int y2, PIXEL color);
	void drawHill(int x, int y, PIXEL color);
	void drawRoad(int x, int y, PIXEL color);
	void drawValley(int cx, int cy, PIXEL color);
	void drawPie(int cx, int cy, double deg, int seg, PIXEL color);
	void drawCity(int x, int y, PIXEL color);
	void highlightCityArea();
};

#endif
