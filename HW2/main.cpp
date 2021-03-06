//
//  main.cpp
//  Final Project
//
//  Created by Alex Gavrishev
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//
// The Project Goal
// Write an OpenGL 3D game based on work done in classes.
//  * Generated terrain that can be modified in building mode (F3)
//  * Create hills, valleys, roads and cities
//  * User-driven and self-driven cars
//  * Different camera modes (F1 - global camera, F2 - driver view)


#include "general.h"

#include <stdio.h>

#include "Camera.h"
#include "Overflow.h"
#include "Light.h"

#include "Road.h"
#include "Terrain.h"
#include "Car.h"
#include "SelfDrivenCarCollection.h"

Terrain* terrain;
Car* carUser;
Camera* camera;
Overflow* overflow;
Road* road;
Cities* cities;
Light* light;
SelfDrivenCarCollection* carCollection;

char gMouseLoc[25];
char gCarInfo[25];

/**
 * Initialize all component
 */
void init()
{
	//135-206-250
	glClearColor(0.52f,0.8f,0.98f,0); // set background color

	srand((unsigned)time(NULL));

	// Handles camera position
	camera = new Camera();	
	// Store road infromation
	road = new Road();

	// Generate and draws terrain
	terrain = new Terrain();
	terrain->init(road);

	road->init(terrain);
	road->add(10,84,190,84);
	road->rebuild();

	// Handles cities
	cities = new Cities();
	cities->init();
	cities->setTerrain(terrain);
	cities->setRoad(road);

	// Handles self driven cars
	carCollection = new SelfDrivenCarCollection();
	carCollection->init(road, cities);

	cities->setCarCollection(carCollection);

	// Add initial 4 cities
	cities->addSpecType(Cities::CITY_SIZE+1,Cities::CITY_SIZE+1,Cities::CITY_INDUSTRIAL);
	cities->addSpecType(Cities::CITY_SIZE+1,3 * Cities::CITY_SIZE + 1,Cities::CITY_SUBURB);
	cities->addSpecType(GRID_SIZE - 2*Cities::CITY_SIZE - 1,3 * Cities::CITY_SIZE + 1,Cities::CITY_SUBURB);
	cities->addSpecType(GRID_SIZE - 2*Cities::CITY_SIZE - 1,GRID_SIZE - 2 * Cities::CITY_SIZE - 1,Cities::CITY_INDUSTRIAL);

	// Car that driven by the user
	carUser = new Car();
	carUser->setRoad(road);
	carUser->setColor(PIX_GREEN_YELLOW);

	sprintf(gCarInfo, "%3d, %3d, %3d ( %3d )", carUser->pos.x, carUser->pos.y, carUser->pos.z, carUser->angle);

	camera->setCar(carUser);

	// Overflow menu fro bulding mode
	overflow = new Overflow();
	overflow->init(terrain, road, cities);
	
	// Scene light
	light = new Light();
	light->setLight(GL_LIGHT0);
}

// Draw mouse & car position on the screen for debug purposes
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

// Display scene in 2d mode - view from the top
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
	carUser->draw3d();
	carCollection->draw3d();

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

// Display scene in 3d mode
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
	carUser->draw3d();
	carCollection->draw3d();

	glutSwapBuffers();
}

// Idle function
void idle()
{
	carUser->update();
	carCollection->drive();

	camera->update();
	sprintf(gCarInfo, "%3.2f, %3.2f, %3.2f ( %3.2f )", carUser->pos.x, carUser->pos.y, carUser->pos.z, carUser->angle);

	glutPostRedisplay();
}

// Mouse cursor move handler
void onMouseMove(int x, int y) {
	int gridX0 = float(x)/GRID_KOEF;
	int gridY0 = float(y)/GRID_KOEF;

	int gridX = cities->normalize(float(x)/GRID_KOEF);
	int gridY = cities->normalize(float(y)/GRID_KOEF);

	//sprintf(gMouseLoc, "%3d (%3d), %3d (%3d)", x, gridX, y, gridY );

	sprintf(gMouseLoc, "%3d (%3d), %3d (%3d)", gridX0, gridX, gridY0, gridY );


	overflow->onMouseMove(x, y);
}

// Mouse click handler
void onMouseClick(int button, int state, int x, int y) {
	//click
	overflow->onMouseClick(button, state, x, y);
}

// Right click menu handler
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

// Special keyboard key press handlert
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

// Keyboard key press handler
void onKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a': // left
			carUser->left();
			break;
		case 'd':  // right
			carUser->right();
			break;
		case 'w':  // forward
			carUser->forward();
			break;
		case 's':   // backward
			carUser->backward();
			break;
	}
}

// Entry point
int main(int argc, char * argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Computer Graphics project @ Afeka College of Engineering");
	
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


