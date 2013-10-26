//
//  Terrain.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#include "Terrain.h"

Terrain::Terrain(void)
{
}

Terrain::~Terrain(void)
{
}


void Terrain::init(Road* road) {
	int i,j;

	mRoad = road;

	for(i=0;i<GRID_SIZE;i++) {
		for(j=0;j<GRID_SIZE;j++)
		{
			mGrid[i][j] = 0.1;
		}
	}
	/*
	for(i=1;i<200;i++) {
		generate3();
	}
	for(i=1;i<400;i++) {
		generate1();
	}
	for(i=1;i<50;i++) {
		generate2();
	}
	smooth();
	for(i=1;i<5;i++) {
		generate2();
	}*/
}

bool Terrain::isWater(int i, int j) {
	return mGrid[i][j] <= 0;
}


void Terrain::draw3d() {
	int i,j;

	glPushMatrix();

	for(i=1;i<GRID_SIZE;i++) {
		for(j=1;j<GRID_SIZE;j++)
		{
			//			glBegin(GL_LINE_LOOP);
			glBegin(GL_POLYGON);
			drawHeightColor(mGrid[i][j]);
			glVertex3d(j-GRID_OFFSET,mGrid[i][j],i-GRID_OFFSET);
			drawHeightColor(mGrid[i][j-1]);
			glVertex3d(j-1-GRID_OFFSET,mGrid[i][j-1],i-GRID_OFFSET);
			drawHeightColor(mGrid[i-1][j-1]);
			glVertex3d(j-1-GRID_OFFSET,mGrid[i-1][j-1],i-1-GRID_OFFSET);
			drawHeightColor(mGrid[i-1][j]);
			glVertex3d(j-GRID_OFFSET,mGrid[i-1][j],i-1-GRID_OFFSET);
			glEnd();
		}
	}

	// water
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0,0,0.5,0.7);
	glBegin(GL_POLYGON);
		glVertex3d(-GRID_OFFSET,0,-GRID_OFFSET);
		glVertex3d(GRID_OFFSET,0,-GRID_OFFSET);
		glVertex3d(GRID_OFFSET,0,GRID_OFFSET);
		glVertex3d(-GRID_OFFSET,0,GRID_OFFSET);
	glEnd();
	glDisable(GL_BLEND);

	glPopMatrix();


	glPushMatrix();
	for(i=1;i<GRID_SIZE;i++) {
		for(j=1;j<GRID_SIZE;j++)
		{
			bool isRoad = mRoad->isRoad(i,j);
			if (!isRoad) {
				continue;
			}
			PIXEL roadColor = (mRoad->isBridge(i,j)) ? PIX_LT_GREY : PIX_DK_GREY;

			glBegin(GL_POLYGON);
			glColor3d(roadColor.red/255.0f,roadColor.green/255.0f,roadColor.blue/255.0f);
				glVertex3d(j-GRID_OFFSET,0.2f,i-GRID_OFFSET);
				glVertex3d(j-1-GRID_OFFSET,0.2f,i-GRID_OFFSET);
				glVertex3d(j-1-GRID_OFFSET,0.2f,i-1-GRID_OFFSET);
				glVertex3d(j-GRID_OFFSET,0.2f,i-1-GRID_OFFSET);
			glEnd();
		}
	}
	glPopMatrix();
}

void Terrain::draw2d() {
	int i,j;

	for(i=1;i<GRID_SIZE;i++) {
		for(j=1;j<GRID_SIZE;j++)
		{
			bool isRoad = mRoad->isRoad(i,j);
			PIXEL roadColor = (mRoad->isBridge(i,j)) ? PIX_LT_GREY : PIX_DK_GREY;
			glBegin(GL_POLYGON);
					drawHeightColor2d(mGrid[i][j],isRoad,roadColor);
				glVertex3d(j-GRID_OFFSET,0,i-GRID_OFFSET);
					drawHeightColor2d(mGrid[i][j-1],isRoad,roadColor);
				glVertex3d(j-1-GRID_OFFSET,0,i-GRID_OFFSET);
					drawHeightColor2d(mGrid[i-1][j-1],isRoad,roadColor);
				glVertex3d(j-1-GRID_OFFSET,0,i-1-GRID_OFFSET);
					drawHeightColor2d(mGrid[i-1][j],isRoad,roadColor);
				glVertex3d(j-GRID_OFFSET,0,i-1-GRID_OFFSET);
			glEnd();
		}
	}

}


void Terrain::drawHeightColor(double h)
{
	if(h>-5)
	{
		h=fabs(h);
		if(h>0 && h<0.4) { // sand
			glColor3d(0.8,0.8,0.5);
		} else if(h<5) {
			glColor3d(0.2+h/30,(5-h)/6,0);
		} else {
			glColor3d(h/11,h/11,h/10);
		}
	} else {
		glColor3d(0,0,0);
	}
}

void Terrain::drawHeightColor2d(double h,bool isRoad,PIXEL roadColor)
{
	if (isRoad) {
		glColor3d(roadColor.red/255.0f,roadColor.green/255.0f,roadColor.blue/255.0f);
		return;
	}

	if(h > 0)
	{
		h=fabs(h);
		if(h > 0 && h < 0.4) { // sand
			glColor3d(0.8,0.8,0.5);
		} else if(h < 5) {
			glColor3d(0.2+h/30,(5-h)/6,0);
		} else { 
			glColor3d(h/11,h/11,h/10);
		}
	}
	else
	{
		glColor3d(0,0,1);
	}
}

// low-pass filter
void Terrain::smooth()
{
	double tmp[GRID_SIZE][GRID_SIZE] = {0};
	int i,j;
	for(i=1;i<GRID_SIZE-1;i++) {
		for(j=1;j<GRID_SIZE-1;j++)
		{
			tmp[i][j] = (mGrid[i-1][j-1] + mGrid[i -1][j] +mGrid[i-1][j+1] +
						 mGrid[i][j-1] + 4*mGrid[i][j] +mGrid[i][j+1]+
						 mGrid[i+1][j-1] + mGrid[i+1][j] +mGrid[i+1][j+1])/12;
		}
	}
	
	for(i=1;i<GRID_SIZE-1;i++) {
		for(j=1;j<GRID_SIZE-1;j++) {
			mGrid[i][j] = tmp[i][j];
		}
	}
}



void Terrain::generate1()
{
	double a,b,delta = 0.1;
	int x1,x2,y1,y2,x,y;
	
	x1 = rand()% GRID_SIZE;
	y1 = rand()% GRID_SIZE;
	x2 = rand()% GRID_SIZE;
	y2 = rand()% GRID_SIZE;
	
	if(rand()%2==0) {
		delta = -delta;
	}
	
	if(x1!=x2)
	{
		a = (y2-y1)/(double)(x2-x1) ;
		b = y1 - a*x1;
		for(y=0;y<GRID_SIZE;y++) {
			for(x=0;x<GRID_SIZE;x++)
			{
				if(y>a*x+b) {
					mGrid[y][x]+=delta;
				}
				else
				{
					mGrid[y][x] -= delta;
				}
			}
		}
	}
}

void Terrain::generate2()
{
	int x1,y1,points = 1500,direction;
	double delta = 0.1;
	x1 = rand() % GRID_SIZE;
	y1 = rand() % GRID_SIZE;
	if(rand()%2==0) {
		delta = -delta;
	}

	while(points>0)
	{
		mGrid[y1][x1] += delta;
		direction = rand()%4;
		switch(direction)
		{
			case 0: // up
				y1--;
				break;
			case 1: // right
				x1++;
				break;
			case 2: // down
				y1++;
				break;
			case 3: // left
				x1--;
				break;
		}
		x1 = (x1+GRID_SIZE) % GRID_SIZE;
		y1 = (y1+GRID_SIZE) % GRID_SIZE;
		points--;
	}
}

void Terrain::generate3()
{
	int x,y,r;
	int i,j;
	double dist,alpha;
	double delta = 1;
	
	x = rand()% GRID_SIZE;
	y = rand()% GRID_SIZE;
	r = 1 +rand()%30 ;
	if(rand()%2==0) {
		delta = -delta;
	}

	for(i=y-r;i<=y+r;i++)
		for(j = x-r;j<=x+r;j++)
		{
			if(i>=0 && j>=0 && i<GRID_SIZE && j<GRID_SIZE)
			{
				dist = sqrt(((double)x-j)*(x-j) + (i-y)*(i-y));
				if(dist<r)
				{
					alpha = acos(dist/r);
					mGrid[i][j] += delta * 0.03* r*sin(alpha);
				}
			}
		}
	
}

void Terrain::drawHill(int x, int y) {
	int i,j,r=HILL_RADIUS;
	double dist, ca, alpha, h;
 
	for(i=y-r+1; i<y+r; i++)
	{
		for(j=x-r+1; j<x+r; j++)
		{
			if(i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE)
			{
				dist = sqrt(double(x-j) * (x-j) + (y-i)*(y-i) );
				if(dist < r)
				{
					ca = dist/r;
					alpha = acos(ca);
					h = r * sin(alpha);

					h = (h/3);
					if(mGrid[i][j] + h < 10)
					{
						updateGrid(i,j, mGrid[i][j] + h);
					}
				}
			}
		}
	}

	mRoad->rebuild();
}

void Terrain::drawValley(int x,int y) {
	int i,j,r=VALLEY_RAIUS;
	double dist, ca, alpha, h;
 
	for(i=y-r+1; i<y+r; i++)
	{
		for(j=x-r+1; j<x+r; j++)
		{
			if(i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE)
			{
				dist = sqrt(double(x-j) * (x-j) + (y-i)*(y-i) );
				if(dist < r)
				{
					ca = dist/r;
					alpha = acos(ca);
					h = r * sin(alpha);

					h = (h/3);
					if(h > -5)
					{
						updateGrid(i,j, mGrid[i][j] - h);
					}
				}
			}
		}
	}
	mRoad->rebuild();
}

void Terrain::updateGrid(int i, int j, int height) {
	mGrid[i][j] = height;
}

void Terrain::onRoadAdd(int x, int y) {
	if (mGrid[y][x] > 0) {
		mGrid[y][x] = 0.1;
	}
}



