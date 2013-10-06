//
//  world.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/14/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "world.h"

PIXEL pix[HEIGHT][WIDTH];
GROUND ground[HEIGHT][WIDTH];

PIXEL heightPixel[HEIGHT_RANGE];

void worldInit() {
	int i,j;
	
	for(i=0;i<HEIGHT;i++) {
		for(j=0;j<WIDTH;j++) {
			ground[i][j].height = 0;
			ground[i][j].isRoad = false;
			drawPixel(j,i,PIX_BROWN);
		}
	}
	
	
	// Init color for height
	for(i=0;i<HEIGHT_RANGE; i++) {
		if (i == 0) {
			heightPixel[i] = PIX_DK_BLUE;
		} else if (i < HILL_RADIUS) {
			heightPixel[i] = gradientPixel(PIX_BROWN, PIX_GREEN, i, HILL_RADIUS);
		} else {
			heightPixel[i] = gradientPixel(PIX_DK_BROWN, PIX_BROWN, i - HILL_RADIUS, HILL_RADIUS);
		}
	}
	
	// heightPixelTest
	//for(i=100;i<120;i++) {
	//	for(j=100;j<100+HEIGHT_RANGE;j++) {
	//		drawPixel(j,i,heightPixel[j-100]);
	//	}
	//}

}


PIXEL gradientPixel(PIXEL from, PIXEL to, int level, int maxLevel) {
	PIXEL r;
	r.red = gradientValue(from.red, to.red, level, maxLevel);
	r.green = gradientValue(from.green, to.green, level, maxLevel);
	r.blue = gradientValue(from.blue, to.blue, level, maxLevel);
	return r;
}

int gradientValue(int from, int to, int level, int maxLevel) {
	double p = double(level) / maxLevel;
	return from * p + to * (1-p);
}



void drawTree(int x, int y) {
	
	int x1 = x - HILL_RADIUS;
	int y1 = y - HILL_RADIUS;
	int x2 = x + HILL_RADIUS;
	int y2 = y + HILL_RADIUS;
	
	fillSquare(x1, y1, x2, y2, PIX_DK_GREEN);
	
}

void fillSquare(int x1, int y1, int x2, int y2, PIXEL color) {
	for (int i = x1; i < x2; i++) {
		for (int j = y1; j < y2; j++) {
			drawPixel(i,j,color);
		}
	}
}


void drawRoads() {
	for(int i=0;i<HEIGHT;i++) {
		for(int j=0;j<WIDTH;j++) {
			if (!ground[i][j].isRoad) {
				continue;
			}
			int ny = HEIGHT - i;
			int h = ground[ny][j].height;
			if (h < 0) {
				// Bridge
				drawPixel(j,i,PIX_LT_GREY);
			} else if (h < HILL_RADIUS / 2) {
				// Regular
				drawPixel(j,i,PIX_GREY);
			} else {
				//
				drawPixel(j,i,PIX_DK_GREY);
			}
		}
	}
}

void drawRoad(int x1, int y1, int x2, int y2) {
	setRoadLine(x1, y1, x2, y2);
	onGroundChange();
}

void onGroundChange() {
	drawRoads();
}

void drawSquare(int x1, int y1, int x2, int y2, PIXEL color) {
	
	int width = x2-x1;
	
	drawColorLine(x1, y1, width + x1, y1, color);
	drawColorLine(x1, y1, x1, y2, color);
	drawColorLine(x2, y1, x2, y2, color);
	drawColorLine(x1, y2, width + x1, y2, color);
	
}

// draws line on matrix pix
void drawColorLine(int x1, int y1, int x2, int y2, PIXEL color) {
	double a,b;
	int x,y;
	int start,stop;
	
	
	if (x1==x2 && y1==y2) {
		drawPixel(x1,y1,color);
		return;
	}
	
	if (x2 == x1) {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			drawPixel(x1,y,color);
		}
		return;
	}
	
	a = (y2-y1)/double(x2-x1);
	b = y1 - a * x1;
	
	if (fabs(a)<=1)
	{
		if (x1 > x2) {
			start = x2;
			stop = x1;
		} else {
			start = x1;
			stop = x2;
		}
		
		for(x = start; x <= stop; x++) {
			y = a*x+b;
			drawPixel(x,y,color);
		}
	} else {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			x = (y-b)/a;
			drawPixel(x,y,color);
		}
	}
}

void setHeight(int height, int x, int y) {
	int ny = HEIGHT - y;
	int newHeight = ground[ny][x].height + height;
	if (newHeight > HILL_RADIUS) {
		newHeight = HILL_RADIUS;
	} else if (newHeight < -1 * HILL_RADIUS) {
		newHeight = -1 * HILL_RADIUS;
	}
	ground[ny][x].height = newHeight;
	drawPixel(x,y,heightPixel[newHeight + HILL_RADIUS]);
	
}




void drawValley(int x,int y) {
	int i,j,radius = HILL_RADIUS;
	double dist, angleAlpha, cosAlpha, height;
	
	for(i=y-radius+1;i<y+radius;i++) {
		for(j=x-radius+1;j<x+radius;j++) {
			if (i>=0 && i<HEIGHT && j>=0 && j<WIDTH) {
				dist = sqrt(double(x-j)*(x-j)+(y-i)*(y-i));
				if (dist < radius) {
					cosAlpha = dist/radius;
					angleAlpha = acos(cosAlpha);
					height = radius * sin(angleAlpha);
					setHeight(-1 * height, j, i);
				}
			}
		}
	}
	onGroundChange();
}

void drawHill(int x, int y) {
	int i,j,radius = HILL_RADIUS;
	double dist, angleAlpha, cosAlpha, height;
	
	for(i=y-radius+1;i<y+radius;i++) {
		for(j=x-radius+1;j<x+radius;j++) {
			if (i>=0 && i<HEIGHT && j>=0 && j<WIDTH) {
				dist = sqrt(double(x-j)*(x-j)+(y-i)*(y-i));
				if (dist < radius) {
					cosAlpha = dist/radius;
					angleAlpha = acos(cosAlpha);
					height = radius * sin(angleAlpha);
					setHeight(height, j, i);
				}
			}
		}
	}
	onGroundChange();
}

void setRoad(int x, int y, bool isRoad) {
	int x0 = x - 5;
	int x1 = x + 5;
	x0 = (x0 < 0) ? 0 : x0;
	x1 = (x1 >= WIDTH) ? WIDTH : x1;
	int y0 = y - 5;
	int y1 = y + 5;
	y0 = (y0 < 0) ? 0 : y0;
	y1 = (y1 >= HEIGHT) ? HEIGHT : y1;
	
	for (int i = x0; i < x1; i++) {
		for (int j = y0; j < y1; j++) {
			ground[j][i].isRoad = isRoad;
		}
	}
}

void setRoadLine(int x1, int y1, int x2, int y2) {
	double a,b;
	int x,y;
	int start,stop;
	
	if (x1==x2 && y1==y2) {
		setRoad(x1,y1,true);
		return;
	}
	
	if (x2 == x1) {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			setRoad(x1,y,true);
		}
		return;
	}
	
	a = (y2-y1)/double(x2-x1);
	b = y1 - a * x1;
	
	if (fabs(a)<=1)
	{
		if (x1 > x2) {
			start = x2;
			stop = x1;
		} else {
			start = x1;
			stop = x2;
		}
		
		for(x = start; x <= stop; x++) {
			y = a*x+b;
			setRoad(x,y,true);
		}
	} else {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			x = (y-b)/a;
			setRoad(x,y,true);
		}
	}
}


void drawPixel(int x, int y, PIXEL color) {
	int ny = HEIGHT - y - 1;
	pix[ny][x].red=color.red;
	pix[ny][x].green=color.green;
	pix[ny][x].blue=color.blue;
}
