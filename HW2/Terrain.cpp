//
//  terrain.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/21/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "terrain.h"


double grid[GRID_SIZE][GRID_SIZE]={0};

void terrainInit() {
	int i;
	
	for(i=1;i<200;i++) {
		terrainGenerate3();
	}
	for(i=1;i<400;i++) {
		terrainGenerate1();
	}
	for(i=1;i<50;i++) {
		terrainGenerate2();
	}
	terrainSmooth();
	for(i=1;i<5;i++) {
		terrainGenerate2();
	}
}

// low-pass filter
void terrainSmooth()
{
	double tmp[GRID_SIZE][GRID_SIZE] = {0};
	int i,j;
	for(i=1;i<GRID_SIZE-1;i++) {
		for(j=1;j<GRID_SIZE-1;j++)
		{
			tmp[i][j] = (grid[i-1][j-1] + grid[i -1][j] +grid[i-1][j+1] +
						 grid[i][j-1] + 4*grid[i][j] +grid[i][j+1]+
						 grid[i+1][j-1] + grid[i+1][j] +grid[i+1][j+1])/12;
		}
	}
	
	for(i=1;i<GRID_SIZE-1;i++) {
		for(j=1;j<GRID_SIZE-1;j++) {
			grid[i][j] = tmp[i][j];
		}
	}
}



void terrainGenerate1()
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
					grid[y][x]+=delta;
				}
				else
				{
					grid[y][x] -= delta;
				}
			}
		}
	}
}

void terrainGenerate2()
{
	int x1,y1,points = 1500,direction;
	double delta = 0.1;
	x1 = rand()% GRID_SIZE;
	y1 = rand()% GRID_SIZE;
	if(rand()%2==0) delta = -delta;
	
	while(points>0)
	{
		grid[y1][x1] += delta;
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

void terrainGenerate3()
{
	int x,y,r;
	int i,j;
	double dist,alpha;
	double delta = 1;
	
	x = rand()% GRID_SIZE;
	y = rand()% GRID_SIZE;
	r = 1 +rand()%30 ;
	if(rand()%2==0) delta = -delta;
	
	for(i=y-r;i<=y+r;i++)
		for(j = x-r;j<=x+r;j++)
		{
			if(i>=0 && j>=0 && i<GRID_SIZE && j<GRID_SIZE)
			{
				dist = sqrt(((double)x-j)*(x-j) + (i-y)*(i-y));
				if(dist<r)
				{
					alpha = acos(dist/r);
					grid[i][j] += delta * 0.03* r*sin(alpha);
				}
			}
		}
	
	
}