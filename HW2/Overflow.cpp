//
//  Overflow.cpp
//  Final Project
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

void Overflow::init(Terrain* terrain, Road* road, Cities* cities) {
	mMenuSelectedItem = MENU_NO_ITEM;
	mTerrain = terrain;
	mRoad = road;
	mCities = cities;
	mMousePos.x = 0;
	mMousePos.y = 0;
	mMousePos.z = 0;

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
	int last = MENU_ITEM_COUNT * MENU_ITEM_HEIGHT + MENU_ITEM_Y +  MENU_ITEM_HEIGHT;
	if (y > last) {
		return MENU_NO_ITEM;
	}
	for (int i = MENU_ITEM_COUNT; i >= 0 ; i--) {
		int top = i * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
		if (y >= top && y < last) {
			return i;
		}
		last = top;
	}
	return MENU_NO_ITEM;
}

void Overflow::draw2d() {
	int yOffset,xOffset = MENU_ITEM_X;
	PIXEL color;

	if (mMenuSelectedItem == MENU_ITEM_CITY) {
		highlightCityArea();
	}

	glPushMatrix();
		glTranslated(MENU_ITEM_X-2,MENU_ITEM_X-2,0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0,0,0,0.6);

		//front glass
		glBegin(GL_POLYGON);
			glVertex3d( 0, 0, 0);              // Top Left
			glVertex3d( MENU_ITEM_HEIGHT + 4, 0, 0);              // Top Right
			glVertex3d( MENU_ITEM_HEIGHT + 4 , MENU_ITEM_COUNT * MENU_ITEM_HEIGHT + MENU_ITEM_SPACE * MENU_ITEM_HEIGHT, 0);              // Bottom Right
			glVertex3d( 0, MENU_ITEM_COUNT * MENU_ITEM_HEIGHT + MENU_ITEM_SPACE * MENU_ITEM_HEIGHT, 0);              // Bottom Left
		glEnd();

		glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
		color = (mMenuSelectedItem == MENU_ITEM_HILL) ? PIX_WHITE : PIX_PINK;
		yOffset = MENU_ITEM_Y;
		drawHill(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) + (MENU_ITEM_HEIGHT/4) + MENU_ITEM_SPACE, color);
		drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);
	 
		color = (mMenuSelectedItem == MENU_ITEM_VALLEY) ? PIX_WHITE : PIX_PINK;
		yOffset = 1 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
		drawValley(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) - (MENU_ITEM_HEIGHT/4) + MENU_ITEM_SPACE, color);
		drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);

		color = (mMenuSelectedItem == MENU_ITEM_ROAD) ? PIX_WHITE : PIX_PINK;
		yOffset = 2 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
		drawRoad(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) + MENU_ITEM_SPACE, color);
		drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);

		color = (mMenuSelectedItem == MENU_ITEM_CITY) ? PIX_WHITE : PIX_PINK;
		yOffset = 3 * MENU_ITEM_HEIGHT + MENU_ITEM_Y;
		drawCity(xOffset + (MENU_ITEM_HEIGHT/2), yOffset + (MENU_ITEM_HEIGHT/2) + MENU_ITEM_SPACE, color);
		drawSquare(xOffset, yOffset+MENU_ITEM_SPACE, MENU_ITEM_HEIGHT + xOffset, yOffset + MENU_ITEM_HEIGHT, color);
	glPopMatrix();

}

void Overflow::drawCity(int x, int y, PIXEL color) {
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_POLYGON);
		glVertex3d(x-3,y-1,0);
		glVertex3d(x-1,y-1,0);
		glVertex3d(x-1,y+3,0);
		glVertex3d(x-3,y+3,0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(x-1,y-3,0);
		glVertex3d(x+1,y-3,0);
		glVertex3d(x+1,y+3,0);
		glVertex3d(x-1,y+3,0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(x+1,y-2,0);
		glVertex3d(x+3,y-2,0);
		glVertex3d(x+3,y+3,0);
		glVertex3d(x+1,y+3,0);
	glEnd();
}

void Overflow::drawHill(int cx, int cy, PIXEL color) {
	 drawPie(cx,cy,-PI,100,color);
}

void Overflow::drawRoad(int x, int y, PIXEL color) {
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_LINES);

		glVertex3d(x-4,y-2,0);
		glVertex3d(x+4,y-2,0);

		glVertex3d(x-4,y+2,0);
		glVertex3d(x+4,y+2,0);

		glVertex3d(x-4,y,0);
		glVertex3d(x-2,y,0);

		glVertex3d(x-1,y,0);
		glVertex3d(x+1,y,0);

		glVertex3d(x+2,y,0);
		glVertex3d(x+4,y,0);
	glEnd();
}

void Overflow::drawValley(int cx, int cy, PIXEL color) {
	 drawPie(cx,cy,PI,1000,color);

}

void Overflow::drawPie(int cx, int cy, double deg, int seg, PIXEL color) {
	float theta = deg / float(seg); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = 4;//we start at angle = 0 
	float y = 0; 
	
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_POLYGON); 
	for(int ii = 0; ii < seg; ii++) 
	{ 
		glVertex3d(x + cx,y + cy,0);//output vertex 
		
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd();
}

void Overflow::drawItem(int item, int x, int y) {
	mClick.count++;

	if (item == MENU_ITEM_HILL) {
		mTerrain->drawHill(x,y);
		mClick.count = 0;
	} else if (item == MENU_ITEM_VALLEY) {
		mTerrain->drawValley(x,y);
		mClick.count = 0;
	} else if (item == MENU_ITEM_ROAD) {
		if (mClick.count == 1) {
			mClick.x1 = x;
			mClick.y1 = y;
		} else if (mClick.count == 2) {
			mClick.x2 = x;
			mClick.y2 = y;
			mRoad->add(mClick.x1,mClick.y1,mClick.x2,mClick.y2);
			mClick.count = 0;
		}
	} else if (item == MENU_ITEM_CITY) {
		//TODO
		mCities->add(x,y);
		mClick.count = 0;
	}
	
}

void Overflow::onMouseClick(int button, int state, int x, int y) {
	//click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int gridX = float(x)/GRID_KOEF;
		int gridY = float(y)/GRID_KOEF;

		int item = detectSelectedItem(gridX - GRID_OFFSET,gridY - GRID_OFFSET);
		if (item == MENU_NO_ITEM) {
			drawItem(mMenuSelectedItem, gridX, gridY);
		} else {
			setMenuSelectedItem(item);
			mClick.count = 0;
		}
	}
}

void Overflow::onMouseMove(int x, int y) {

	mMousePos.x = x;
	mMousePos.y = y;

}

void Overflow::highlightCityArea() {
	int gridX = mCities->normalize(float(mMousePos.x)/GRID_KOEF);
	int gridY = mCities->normalize(float(mMousePos.y)/GRID_KOEF);

	PIXEL color = (mCities->isOccupied(gridX, gridY)) ? PIX_RED : PIX_GREEN;

	glPushMatrix();
		glTranslated(-GRID_OFFSET,-GRID_OFFSET,0.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(color.red/255.0f, color.green/255.0f , color.blue/255.0f, 0.8f);

		//front glass
		glBegin(GL_POLYGON);
			glVertex3d( gridX, gridY, 0.0f);              // Top Left
			glVertex3d( gridX, gridY + Cities::CITY_SIZE, 0.0f);              // Top Right
			glVertex3d( gridX + Cities::CITY_SIZE, gridY + Cities::CITY_SIZE, 0.0f);              // Bottom Right
			glVertex3d( gridX + Cities::CITY_SIZE, gridY, 0.0f);              // Bottom Left
		glEnd();

		glDisable(GL_BLEND);
	glPopMatrix();

}

void Overflow::drawSquare(int x1, int y1, int x2, int y2, PIXEL color) {
	
	
	glColor3d(color.red/255.0f, color.green/255.0f , color.blue/255.0f);

	glBegin(GL_LINES);
		//   ----
		//
		//
		glVertex3d(x1,y1,0);
		glVertex3d(x2,y1,0);
		//   ----
		//   |
		//
		glVertex3d(x1,y1,0);
		glVertex3d(x1,y2,0);
		//   ----
		//   |
		//   ----
		glVertex3d(x2,y2,0);
		glVertex3d(x1,y2,0);
		//   ----
		//   |  |
		//   ----
		glVertex3d(x2,y2,0);
		glVertex3d(x2,y1,0);

	glEnd();

}
