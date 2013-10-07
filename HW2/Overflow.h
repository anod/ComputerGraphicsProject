//
//  Overflow.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef OVERFLOW_H
#define OVERFLOW_H

#include "drawable.h"
#include "glut.h"

typedef struct
{
	int count;
	int x1,y1,x2,y2;
} MOUSE_CLICK;

MOUSE_CLICK click;


class Overflow :
	public Drawable
{
public:
	Overflow(void);
	~Overflow(void);
	void onMouseClick();
	void init();
private:
	static const int MENU_ITEM_HEIGHT = 58;
	static const int MENU_ITEM_X = 5;
	static const int MENU_ITEM_Y = 5;
	static const int MENU_NO_ITEM = -1;
	static const int MENU_ITEM_COUNT = 4;
	static const int MENU_ITEM_SPACE = 4;

	static const int MENU_ITEM_HILL = 0;
	static const int MENU_ITEM_ROAD = 1;
	static const int MENU_ITEM_VALLEY = 2;
	static const int MENU_ITEM_TREE = 3;

	int mMenuHighlightedItem;
	int mMenuSelectedItem;

	void drawMenuSelection();
	void drawMenu();
	void Overflow::drawItem(int item, int x, int y);
	void updateMenuHighlightedItem(int x, int y);
	int getMenuHighlightedItem(int x, int y);

	void setMenuSelectedItem(int item);
	int getMenuSelectedItem();
};

#endif
