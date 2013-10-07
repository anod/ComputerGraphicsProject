//
//  World.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/14/13.
//

#ifndef WORLD_H
#define WORLD_H

#include <math.h>
#include "ground.h"
#include "pixel.h"

class World {
public:

	void init();
	void drawRoads();
	void drawRoad(int x1, int y1, int x2, int y2);
	void drawPixel(int x, int y, PIXEL color);
	void drawHill(int x, int y);
	void drawValley(int x,int y);
	void drawColorLine(int x1, int y1, int x2, int y2, PIXEL color);
	void drawSquare(int x1, int y1, int x2, int y2, PIXEL color);
	void drawTree(int x,int y);

private:
	static const int WIDTH = 600;
	static const int HEIGHT = 600;

	PIXEL mPix[HEIGHT][WIDTH];
	GROUND mGround[HEIGHT][WIDTH];
	PIXEL mHeightPixel[HEIGHT_RANGE];

	void onGroundChange();
	void setRoadLine(int x1, int y1, int x2, int y2);
	void fillSquare(int x1, int y1, int x2, int y2, PIXEL color);
	PIXEL gradientPixel(PIXEL from, PIXEL to, int level, int maxLevel);
	int gradientValue(int from, int to,int level, int maxLevel);


#endif
