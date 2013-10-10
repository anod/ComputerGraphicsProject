//
//  Overflow.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef OVERFLOW_H
#define OVERFLOW_H

#include "general.h"

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
	void init();
	void draw();
	void onMouseClick(int button, int state, int x, int y);
private:
	static const int MENU_ITEM_HEIGHT = 10;
	static const int MENU_ITEM_X = -100+2;// GRID_SIZE //0;
	static const int MENU_ITEM_Y = -100+2; //5;
	static const int MENU_NO_ITEM = -1;
	static const int MENU_ITEM_COUNT = 4;
	static const int MENU_ITEM_SPACE = 1;

	static const int MENU_ITEM_HILL = 0;
	static const int MENU_ITEM_ROAD = 1;
	static const int MENU_ITEM_VALLEY = 2;
	static const int MENU_ITEM_TREE = 3;

	int mMenuHighlightedItem;
	int mMenuSelectedItem;

	MOUSE_CLICK mClick;


	void drawItem(int item, int x, int y);
	void updateMenuHighlightedItem(int x, int y);
	int getMenuHighlightedItem(int x, int y);

	void setMenuSelectedItem(int item);
	int getMenuSelectedItem();

	void drawSquare(int x1, int y1, int x2, int y2, PIXEL color);
	void drawHill(int x, int y, PIXEL color);
	void drawRoad(int x, int y, PIXEL color);
	void drawValley(int x, int y, PIXEL color);
	void drawTree(int x, int y, PIXEL color);

};

#endif
