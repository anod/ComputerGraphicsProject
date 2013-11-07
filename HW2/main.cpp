//
//  main.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/7/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

// TODO:
//
// * Render road by polygons
// * Check car/road boudaries
// * Auto-driving
// * Light on car
//

#include "general.h"

#include <stdio.h>

#include "Camera.h"
#include "Overflow.h"
#include "Light.h"

#include "Road.h"
#include "Terrain.h"
#include "Car.h"

Terrain* terrain;
Car* car;
Camera* camera;
Overflow* overflow;
Road* road;
Cities* cities;
Light* light;

char gMouseLoc[25];
char gCarInfo[25];

//World* world;

void init()
{
	//135-206-250
	glClearColor(0.52,0.8,0.98,0); // set background color

	srand((unsigned)time(NULL));

	camera = new Camera();	
	road = new Road();

	terrain = new Terrain();
	terrain->init(road);

	road->init(terrain);
	road->add(10,84,190,84);
	road->rebuild();


	car = new Car();
	car->setRoad(road);
	car->setColor(PIX_GREEN_YELLOW);

	sprintf(gCarInfo, "%3d, %3d, %3d ( %3d )", car->pos.x, car->pos.y, car->pos.z, car->angle);

	camera->setCar(car);

	cities = new Cities();
	cities->init();
	cities->setRoad(road);
	cities->setTerrain(terrain);
	cities->addSpecType(Cities::CITY_SIZE+1,Cities::CITY_SIZE+1,Cities::CITY_INDUSTRIAL);
	cities->addSpecType(Cities::CITY_SIZE+1,3 * Cities::CITY_SIZE + 1,Cities::CITY_SUBURB);
	cities->addSpecType(GRID_SIZE - 2*Cities::CITY_SIZE - 1,3 * Cities::CITY_SIZE + 1,Cities::CITY_SUBURB);
	cities->addSpecType(GRID_SIZE - 2*Cities::CITY_SIZE - 1,GRID_SIZE - 2 * Cities::CITY_SIZE - 1,Cities::CITY_INDUSTRIAL);

	overflow = new Overflow();
	overflow->init(terrain, road, cities);
	
	light = new Light();
	light->setLight(GL_LIGHT0);
}

void drawMousePos() {
	unsigned int i;
	glColor3d(1.0f, 1.0f , 1.0f);

	glPushMatrix();
	glRasterPos3f(40,90,0);
	for (i = 0; i < strlen (gMouseLoc); i++) {
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gMouseLoc[i]);
	}

	glRasterPos3f(-90,90,0);
	for (i = 0; i < strlen (gCarInfo); i++) {
		 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gCarInfo[i]);
	}
	glPopMatrix();
}

void display2D()
{
	// Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 3D
	// enable lighting, z-test, etc
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// set active matrix mode to projection
	glMatrixMode(GL_PROJECTION);
	// load identity and establish a perspective projection
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);

	// set active matrix mode back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw everything 3D
	gluLookAt(0,100,0,0,0,0,0,0,-1);
	light->enable();
	terrain->draw();
	cities->draw();
	car->draw3d();

	// 2D
	// disable lighting, z-test, etc
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// set active matrix mode to projection
	glMatrixMode(GL_PROJECTION);
	// load identity and establish an ortogonal projection
	glLoadIdentity();
	gluOrtho2D(-100, 100, 100, -100);

	// set active matrix mode back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw everything 2D
	overflow->draw2d();

	drawMousePos();

	// swap buffers

	glutSwapBuffers();
}

void display3D()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 3D
	// enable lighting, z-test, etc
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// set active matrix mode to projection
	glMatrixMode(GL_PROJECTION);
	// load identity and establish a perspective projection
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);

	// set active matrix mode back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw everything 3D
	gluLookAt(
		camera->pos.x,camera->pos.y,camera->pos.z,
		camera->center.x,camera->center.y,camera->center.z,
		camera->up.x,camera->up.y,camera->up.z
	);

	light->enable();

	terrain->draw();
	cities->draw();
	car->draw3d();

	/*
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
	*/

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
	int gridX0 = float(x)/GRID_KOEF;
	int gridY0 = float(y)/GRID_KOEF;

	int gridX = cities->normalize(float(x)/GRID_KOEF);
	int gridY = cities->normalize(float(y)/GRID_KOEF);

	//sprintf(gMouseLoc, "%3d (%3d), %3d (%3d)", x, gridX, y, gridY );

	sprintf(gMouseLoc, "%3d (%3d), %3d (%3d)", gridX0, gridX, gridY0, gridY );


	overflow->onMouseMove(x, y);
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


