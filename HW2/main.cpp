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

double planex=0,planey=0,planez=0;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;

Terrain* terrain;
Car* car;
Camera* camera;
Overflow* overflow;
Road* road;
Cities* cities;

char gMouseLoc[25];
char gCarInfo[25];

//World* world;

void init()
{
	//135-206-250
	glClearColor(0.52,0.8,0.98,0); // set background color
	glEnable(GL_DEPTH_TEST);
	
	srand((unsigned)time(NULL));

	camera = new Camera();	
	car = new Car();

	sprintf(gCarInfo, "%3d, %3d, %3d ( %3d )", car->pos.x, car->pos.y, car->pos.z, car->angle);

	camera->setCar(car);

	road = new Road();

	terrain = new Terrain();
	terrain->init(road);

	road->init(terrain);
	road->add(10,101,190,101);
	road->rebuild();
	
	cities = new Cities();
	cities->setRoad(road);
	cities->setTerrain(terrain);

	overflow = new Overflow();
	overflow->init(terrain, road, cities);
	
}

void drawMousePos() {
	unsigned int i;
	glColor3d(1.0f, 1.0f , 1.0f);

	glPushMatrix();
	glRasterPos3f(25,20,75);
	for (i = 0; i < strlen (gMouseLoc); i++) {
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gMouseLoc[i]);
	}

	glRasterPos3f(-75,20,75);
	for (i = 0; i < strlen (gCarInfo); i++) {
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gCarInfo[i]);
	}
	glPopMatrix();
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

//	terrain->draw();

	cities->draw();

	car->draw3d();

	overflow->draw();

	drawMousePos();

	glutSwapBuffers();
}

void display3D()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);

	gluLookAt(
		camera->pos.x,camera->pos.y,camera->pos.z,
		camera->center.x,camera->center.y,camera->center.z,
		camera->up.x,camera->up.y,camera->up.z
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	terrain->draw();
	
	cities->draw();
	// car
	car->draw3d();

	double aSin = sin(car->angle+PI/2);
	double aCos = cos(car->angle+PI/2);
	double cx = car->pos.x - 0.2f - 5*aSin;
	double cy = car->pos.y + 1.8f;
	double cz = car->pos.z - 0.4f - 5*aCos;
	glPushMatrix();
		glTranslated(cx,cy,cz);
		glRotated(car->angle*180/PI,0,1,0);
		glBegin(GL_POLYGON);
		glColor3d(0.0f,0.7f,0.0f);
			glVertex3d(-0.5f, 0.5f, -0.5f);              // Top Left
			glVertex3d(-0.5f, 0.5f, 0.5f);              // Top Right
			glVertex3d(-0.5f, 0.0f, 0.5f);              // Bottom Right
			glVertex3d(-0.5f, 0.0f, -0.5f);              // Bottom Left
		glEnd();
	glPopMatrix();


	glutSwapBuffers();
}

void idle()
{
	car->update();
	camera->update();
	sprintf(gCarInfo, "%3.2f, %3.2f, %3.2f ( %3.2f )", car->pos.x, car->pos.y, car->pos.z, car->angle);

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

void onSpecialKey(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		camera->left();
		break;
	case GLUT_KEY_RIGHT:
		camera->right();
		break;
	case GLUT_KEY_UP:
		camera->forward();
		break;
	case GLUT_KEY_DOWN:
		camera->backward();
		break;
	case GLUT_KEY_PAGE_UP:
		camera->levelUp(); 
		break;
	case GLUT_KEY_PAGE_DOWN:
		camera->levelDown();
		break;
	case GLUT_KEY_F1:
		camera->setViewMode(Camera::VIEW_DEFAULT);
		glutDisplayFunc(display3D);
		break;
	case GLUT_KEY_F2:
		camera->setViewMode(Camera::VIEW_INSIDE);
		glutDisplayFunc(display3D);
		break;
	case GLUT_KEY_F3:
		glutDisplayFunc(display2D);
		break;
	}
}

void onKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a': // left
			car->left();
			break;
		case 'd':  // right
			car->right();
			break;
		case 'w':  // forward
			car->forward();
			break;
		case 's':   // backward
			car->backward();
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
	glutDisplayFunc(display2D);
	// onTimer
	glutIdleFunc(idle);
	glutMouseFunc(onMouseClick);
	glutPassiveMotionFunc(onMouseMove);
	glutSpecialFunc(onSpecialKey);
	glutKeyboardFunc(onKeyboard);
	
	glutCreateMenu(onMenuSelect);
	glutAddMenuEntry("3D View",2);
	glutAddMenuEntry("2D View",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	init();
	glutMainLoop();
	return 0;
}


