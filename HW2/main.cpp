//
//  main.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/7/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "general.h"

#include <stdio.h>

#include "Camera.h"
#include "Overflow.h"

#include "Road.h"
#include "Terrain.h"
#include "Car.h"

double angle=PI,dangle=0.0,start=0;
double dx=0,dy=0,dz=0;
double speed = 0;
double planex=0,planey=0,planez=0;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;

Terrain* terrain;
Car* car;
Camera* camera;
Overflow* overflow;
Road* road;

char gMouseLoc[25];

//World* world;

void init()
{
	glClearColor(0.4,0.4,0.4,0); // set background color
	glEnable(GL_DEPTH_TEST);
	
	srand((unsigned)time(NULL));

	camera = new Camera();	
	
	 sprintf(gMouseLoc, "%3d, %3d", 0, 0 );

	road = new Road();
	terrain = new Terrain();
	terrain->init(road);
	road->init(terrain);
	road->add(10,100,190,100);

	car = new Car();

	overflow = new Overflow();
	overflow->init(terrain, road);
	
}

void drawMousePos() {
    unsigned int i;
	glColor3d(1.0f, 1.0f , 1.0f);

    glRasterPos3f(40,0,95);
	for (i = 0; i < strlen (gMouseLoc); i++) {
         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gMouseLoc[i]);
	}
}

void display2D()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);

	gluLookAt(0,100,0,0,0,0,0,0,-1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawMousePos();

	overflow->draw();
	terrain->draw2d();

	glutSwapBuffers();
}

void display3D()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);

	// eyex,eyey,eyez - represent the camera position
	// sightx,sighty,sightz - represent the camera view direction
	// 0,1,0 represent the camera up vector
	gluLookAt(
		camera->pos.x,camera->pos.y,camera->pos.z,
		camera->pos.x+camera->sight.x,camera->pos.y+camera->sight.y,camera->pos.z+camera->sight.z,
		camera->up.x,camera->up.y,camera->up.z
	);
	
	glMatrixMode(GL_MODELVIEW);

	terrain->draw3d();
	
	glTranslated(planex,planey, planez);
	//glRotated(plane_angle*180/PI,0,1,0);
	//glRotated(-plane_ang_speed*2000,1,0,0);
	
	car->draw3d();
	
	glutSwapBuffers();
}

void idle()
{

	glutPostRedisplay();
}

void onMouseMove(int x, int y) {
	int gridX = float(x)/GRID_KOEF;
	int gridY = float(y)/GRID_KOEF;
	sprintf(gMouseLoc, "%3d (%3d), %3d (%3d)", x, gridX, y, gridY );
}

void onMouseClick(int button, int state, int x, int y) {
	//click
	overflow->onMouseClick(button, state, x, y);
}

void onMenuSelect(int option)
{
	switch(option)
	{
		case 1:
			glutDisplayFunc(display2D);
			break;
		case 2:
			glutDisplayFunc(display3D);
			break;
	}
}


int main(int argc, char * argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("HW2");
	
	// onPaint
	glutDisplayFunc(display3D);
	// onTimer
	glutIdleFunc(idle);
	glutMouseFunc(onMouseClick);
	glutPassiveMotionFunc(onMouseMove);
	//glutSpecialFunc(SpecialKey);
	//glutKeyboardFunc(Keyboard);
	
	glutCreateMenu(onMenuSelect);
	glutAddMenuEntry("3D View",2);
	glutAddMenuEntry("2D View",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	init();
	glutMainLoop();
	return 0;
}


