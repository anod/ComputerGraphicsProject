//
//  Overflow.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#include "Overflow.h"


Overflow::Overflow(void)
{
}


Overflow::~Overflow(void)
{
}

void Overflow::init() {
	mMenuHighlightedItem = MENU_NO_ITEM;
	mMenuSelectedItem = 0;
}

void Overflow::updateMenuHighlightedItem(int x, int y) {
	mMenuHighlightedItem = getMenuHighlightedItem(x, y);
}

void Overflow::setMenuSelectedItem(int item) {
	mMenuSelectedItem = item;
}

int Overflow::getMenuSelectedItem() {
	return mMenuSelectedItem;
}

int Overflow::getMenuHighlightedItem(int x, int y) {
	if (x < MENU_ITEM_X || x > MENU_ITEM_HEIGHT + MENU_ITEM_X) {
		return MENU_NO_ITEM;
	}
	if (y < MENU_ITEM_Y) {
		return MENU_NO_ITEM;
	}
	int last = 3 * MENU_ITEM_HEIGHT + MENU_ITEM_Y +  MENU_ITEM_HEIGHT;
	if (y > last) {
		return MENU_NO_ITEM;
	}
	for (int i = 3; i >= 0 ; i--) {
		int top = i * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
		if (y >= top && y < last) {
			return i;
		}
		last = top;
	}
	return MENU_NO_ITEM;
}

void Overflow::drawMenuSelection() {
	int yOffset,xOffset = MENU_ITEM_X;
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		yOffset = i * MENU_ITEM_HEIGHT + 5;
		if (i != mMenuHighlightedItem) {
			//drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_BROWN);
		}
	}
	
	if (mMenuHighlightedItem != MENU_NO_ITEM) {
		yOffset = mMenuHighlightedItem * MENU_ITEM_HEIGHT + 5;
		//drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_BLACK);
	}
	
	yOffset = mMenuSelectedItem * MENU_ITEM_HEIGHT + 5;
//	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_WHITE);
	
}

void Overflow::drawMenu() {
	
//	drawHill(HILL_RADIUS + 10, HILL_RADIUS + 10 + 2);
//	drawRoad(MENU_ITEM_X + 10, MENU_ITEM_HEIGHT + 10 + MENU_ITEM_SPACE, MENU_ITEM_HEIGHT - 10, (MENU_ITEM_HEIGHT + 10) + MENU_ITEM_HEIGHT - 10);
//	drawValley(HILL_RADIUS + 10, (2 * MENU_ITEM_HEIGHT) + HILL_RADIUS + 10 + 2);
//	drawTree(MENU_ITEM_X + HILL_RADIUS + 5, (3 * MENU_ITEM_HEIGHT) + HILL_RADIUS + 10 + 2);
	
}


void Overflow::drawItem(int item, int x, int y) {
	click.count++;
	
	if (item == MENU_ITEM_HILL) {
//		drawHill(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_VALLEY) {
//		drawValley(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_TREE) {
//		drawTree(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_ROAD) {
		if (click.count == 1) {
			click.x1 = x;
			click.y1 = y;
		} else if (click.count == 2) {
			click.x2 = x;
			click.y2 = y;
//			drawRoad(click.x1,click.y1,click.x2,click.y2);
			click.count = 0;
		}
	}
	
}

void Overflow::onMouseClick(int button, int state, int x, int y) {
	//click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//		int item = getMenuHighlightedItem(x,y);
//		if (item == MENU_NO_ITEM) {
//			drawItem(menuSelectedItem, x, y);
//		} else {
//			setMenuSelectedItem(item);
//			click.count = 0;
//		}
	}
}
