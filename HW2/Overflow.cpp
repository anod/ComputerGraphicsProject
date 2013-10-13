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
	mMenuSelectedItem = MENU_NO_ITEM;
}

void Overflow::setMenuSelectedItem(int item) {
	mMenuSelectedItem = item;
}

int Overflow::getMenuSelectedItem() {
	return mMenuSelectedItem;
}

int Overflow::detectSelectedItem(int x, int y) {
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

void Overflow::draw() {
	int yOffset,xOffset = MENU_ITEM_X;
	PIXEL color;

	color = (mMenuSelectedItem == MENU_ITEM_HILL) ? PIX_WHITE : PIX_PINK;
	yOffset = MENU_ITEM_Y;
	drawHill(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) + (MENU_ITEM_HEIGHT/4) + MENU_ITEM_SPACE, color);
	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);

	color = (mMenuSelectedItem == MENU_ITEM_ROAD) ? PIX_WHITE : PIX_PINK;
	yOffset = 1 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
	drawRoad(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) + MENU_ITEM_SPACE, color);
	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);
	 
	color = (mMenuSelectedItem == MENU_ITEM_VALLEY) ? PIX_WHITE : PIX_PINK;
	yOffset = 2 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
	drawValley(xOffset, yOffset, color);
	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);

	color = (mMenuSelectedItem == MENU_ITEM_TREE) ? PIX_WHITE : PIX_PINK;
	yOffset = 3 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
	drawTree(xOffset, yOffset, color);
	drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);

}

void Overflow::drawHill(int cx, int cy, PIXEL color) {
	float theta = -PI / float(100); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = 4;//we start at angle = 0 
	float y = 0; 
    
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_POLYGON); 
	for(int ii = 0; ii < 100; ii++) 
	{ 
		glVertex3d(x + cx,1,y + cy);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}

void Overflow::drawRoad(int x, int y, PIXEL color) {
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_LINES);

		glVertex3d(x-4,1,y-2);
		glVertex3d(x+4,1,y-2);

		glVertex3d(x-4,1,y+2);
		glVertex3d(x+4,1,y+2);

		glVertex3d(x-4,1,y);
		glVertex3d(x-2,1,y);

		glVertex3d(x-1,1,y);
		glVertex3d(x+1,1,y);

		glVertex3d(x+2,1,y);
		glVertex3d(x+4,1,y);
	glEnd();
}

void Overflow::drawValley(int x, int y, PIXEL color) {

}

void Overflow::drawTree(int x, int y, PIXEL color) {

}

void Overflow::drawItem(int item, int x, int y) {
	mClick.count++;
	
	if (item == MENU_ITEM_HILL) {
//		drawHill(x,y);
		mClick.count = 0;
	} else if (item == MENU_ITEM_VALLEY) {
//		drawValley(x,y);
		mClick.count = 0;
	} else if (item == MENU_ITEM_TREE) {
//		drawTree(x,y);
		mClick.count = 0;
	} else if (item == MENU_ITEM_ROAD) {
		if (mClick.count == 1) {
			mClick.x1 = x;
			mClick.y1 = y;
		} else if (mClick.count == 2) {
			mClick.x2 = x;
			mClick.y2 = y;
//			drawRoad(click.x1,click.y1,click.x2,click.y2);
			mClick.count = 0;
		}
	}
	
}

void Overflow::onMouseClick(int button, int state, int x, int y) {
	//click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int koef = 600/200;
		int gridX = float(x)/koef - 100;
		int gridY = float(y)/koef - 100;

		int item = detectSelectedItem(gridX,gridY);
		if (item == MENU_NO_ITEM) {
		//	drawItem(mMenuSelectedItem, gridX, gridY);
		} else {
			setMenuSelectedItem(item);
			mClick.count = 0;
		}
	}
}

void Overflow::drawSquare(int x1, int y1, int x2, int y2, PIXEL color) {
	
	
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_LINES);
		//   ----
		//
		//
		glVertex3d(x1,1,y1);
		glVertex3d(x2,1,y1);
		//   ----
		//   |
		//
		glVertex3d(x1,1,y1);
		glVertex3d(x1,1,y2);
		//   ----
		//   |
		//   ----
		glVertex3d(x2,1,y2);
		glVertex3d(x1,1,y2);
		//   ----
		//   |  |
		//   ----
		glVertex3d(x2,1,y2);
		glVertex3d(x2,1,y1);

	glEnd();

}
