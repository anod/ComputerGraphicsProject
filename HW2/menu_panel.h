//
//  menu_panel.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/14/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#ifndef Home_Work_2_menu_panel_h
#define Home_Work_2_menu_panel_h

#include "world.h"

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

extern int menuHighlightedItem;
extern int menuSelectedItem;

void menuInit();
void drawMenuSelection();
void drawMenu();
void updateMenuHighlightedItem(int x, int y);
int getMenuHighlightedItem(int x, int y);

void setMenuSelectedItem(int item);
int getMenuSelectedItem();


#endif
