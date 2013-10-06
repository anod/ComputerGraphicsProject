//
//  menu_panel.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/14/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "menu_panel.h"

int menuHighlightedItem;
int menuSelectedItem;

void menuInit() {
	menuHighlightedItem = MENU_NO_ITEM;
	menuSelectedItem = 0;
}

void updateMenuHighlightedItem(int x, int y) {
	menuHighlightedItem = getMenuHighlightedItem(x, y);
}

void setMenuSelectedItem(int item) {
	menuSelectedItem = item;
}

int getMenuSelectedItem() {
	return menuSelectedItem;
}


int getMenuHighlightedItem(int x, int y) {
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

void drawMenuSelection() {
	int yOffset,xOffset = MENU_ITEM_X;
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		yOffset = i * MENU_ITEM_HEIGHT + 5;
		if (i != menuHighlightedItem) {
			drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_BROWN);
		}
	}
	
	if (menuHighlightedItem != MENU_NO_ITEM) {
		yOffset = menuHighlightedItem * MENU_ITEM_HEIGHT + 5;
		drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_BLACK);
	}
	
	yOffset = menuSelectedItem * MENU_ITEM_HEIGHT + 5;
	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, PIX_WHITE);
	
}

void drawMenu() {
	
	drawHill(HILL_RADIUS + 10, HILL_RADIUS + 10 + 2);
	drawRoad(MENU_ITEM_X + 10, MENU_ITEM_HEIGHT + 10 + MENU_ITEM_SPACE, MENU_ITEM_HEIGHT - 10, (MENU_ITEM_HEIGHT + 10) + MENU_ITEM_HEIGHT - 10);
	drawValley(HILL_RADIUS + 10, (2 * MENU_ITEM_HEIGHT) + HILL_RADIUS + 10 + 2);
	drawTree(MENU_ITEM_X + HILL_RADIUS + 5, (3 * MENU_ITEM_HEIGHT) + HILL_RADIUS + 10 + 2);
	
}
