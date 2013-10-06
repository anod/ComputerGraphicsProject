//
//  main.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/7/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "main.h"

typedef struct
{
	int count;
	int x1,y1,x2,y2;
} MOUSE_CLICK;

MOUSE_CLICK click;

typedef struct {
	double x,y,z;
} THREE;

// eyex,eyey,eyez - represent the camera position
// sightx,sighty,sightz - represent the camera view direction
// 0,1,0 represent the camera up vector
typedef struct {
	THREE pos; //represent the camera position
	THREE sight; // - represent the camera view direction
	THREE up; //epresent the camera up vector
} CAMERAPOINTS;


CAMERAPOINTS camera;
double angle=PI,dangle=0.0,start=0;
double dx=0,dy=0,dz=0;
double speed = 0;
double planex=0,planey=0,planez=0;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;

Terrain* terrain;

void init()
{
	int i;
	glClearColor(0.4,0.4,0.4,0); // set background color
	glEnable(GL_DEPTH_TEST);
	
	camera.pos.x = 0;
	camera.pos.y = 10;
	camera.pos.z = 15;
	
	camera.sight.x = 0;
	camera.sight.y = -0.2f;
	camera.sight.z = -1.0f;
	
	camera.up.x = 0;
	camera.up.y = 1;
	camera.up.z = 0;
	
	srand((unsigned)time(NULL));
	
	terrain = new Terrain();
	
	terrain->init();
	
	//worldInit();
	//menuInit();
	//drawMenu();
	
	for(i=1;i<200;i++) {
		//UpdateTerrain3();
	}
	for(i=1;i<400;i++) {
		//UpdateTerrain1();
	}
	for(i=1;i<50;i++) {
		//UpdateTerrain2();
	}
//	Smooth();
	for(i=1;i<5;i++) {
		//UpdateTerrain2();
	}
	
}

void DrawCar() {

	//front
	glBegin(GL_POLYGON);
	glColor3d(0.0f,0.4f,1.0f);
	glVertex3d(-4.5f, 1.0f, -3.0f);              // Top Left
	glVertex3d(-4.5f, 1.0f, 3.0f);              // Top Right
	glVertex3d(-4.5f,-1.0f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f,-1.0f, -3.0f);              // Bottom Left
    glEnd();
	
	//back
	glBegin(GL_POLYGON);
	glColor3d(0.0f,0.4f,1.0f);
	glVertex3d( 4.5f, 1.0f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.0f, 3.0f);              // Top Right
	glVertex3d( 4.5f,-1.0f, 3.0f);              // Bottom Right
	glVertex3d( 4.5f,-1.0f, -3.0f);              // Bottom Left
    glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glColor3d(0.2f,0.6f,1.0f);
	glVertex3d(-4.5f, 1.0f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.0f, -3.0f);              // Top Right
	glVertex3d( 4.5f,-1.0f, -3.0f);              // Bottom Right
	glVertex3d(-4.5f,-1.0f, -3.0f);              // Bottom Left
    glEnd();

	//right
	glBegin(GL_POLYGON);
	glColor3d(0.2f,0.6f,1.0f);
	glVertex3d(-4.5f, 1.0f, 3.0f);              // Top Left
	glVertex3d( 4.5f, 1.0f, 3.0f);              // Top Right
	glVertex3d( 4.5f,-1.0f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f,-1.0f, 3.0f);              // Bottom Left
    glEnd();
	
	//bottom
	glBegin(GL_POLYGON);
	glColor3d(0.0f,0.0f,1.0f);
	glVertex3d(-4.5f,-1.0f, -3.0f);              // Top Left
	glVertex3d( 4.5f,-1.0f, -3.0f);              // Top Right
	glVertex3d( 4.5f,-1.0f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f,-1.0f, 3.0f);              // Bottom Left
    glEnd();

	//trunk
	glBegin(GL_POLYGON);
	glColor3d(1,0,0);
	glVertex3d(-4.5f, 1.0f, -3.0f);              // Top Left
	glVertex3d(-2.0f, 1.0f, -3.0f);              // Top Right
	glVertex3d(-2.0f, 1.0f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f, 1.0f, 3.0f);              // Bottom Left
    glEnd();

	
	//motor
	glBegin(GL_POLYGON);
	glColor3d(1,0,0);
	glVertex3d( 2.0f, 1.0f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.0f, -3.0f);              // Top Right
	glVertex3d( 4.5f, 1.0f, 3.0f);              // Bottom Right
	glVertex3d( 2.0f, 1.0f, 3.0f);              // Bottom Left
    glEnd();
}



void display2D()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,WIDTH,HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(
		camera.pos.x,camera.pos.y,camera.pos.z,
		camera.pos.x+camera.sight.x,camera.pos.y+camera.sight.y,camera.pos.z+camera.sight.z,
		camera.up.x,camera.up.y,camera.up.z
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	terrain->draw2d();
	
	// plane
	glPushMatrix();
	
	glTranslated(planex,planey, planez);
	//glRotated(plane_angle*180/PI,0,1,0);  // yaw
	//glRotated(-plane_ang_speed*2000,1,0,0); // roll
	//glRotated(pitch*180/PI,0,0,1);
	//DrawPlane();
	
	DrawCar();
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void display3D()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//drawMenuSelection();
	
	//glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,pix);
	
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	// eyex,eyey,eyez - represent the camera position
	// sightx,sighty,sightz - represent the camera view direction
	// 0,1,0 represent the camera up vector
	gluLookAt(
		camera.pos.x,camera.pos.y,camera.pos.z,
		camera.pos.x+camera.sight.x,camera.pos.y+camera.sight.y,camera.pos.z+camera.sight.z,
		camera.up.x,camera.up.y,camera.up.z
	);
	
	terrain->draw3d();
	
	glTranslated(planex,planey, planez);
	//glRotated(plane_angle*180/PI,0,1,0);
	//glRotated(-plane_ang_speed*2000,1,0,0);
	
	DrawCar();
	//DrawPlane();
	
	glutSwapBuffers();
}

void idle()
{

	glutPostRedisplay();
}

void drawItem(int item, int x, int y) {
	click.count++;
	
	if (item == MENU_ITEM_HILL) {
		drawHill(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_VALLEY) {
		drawValley(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_TREE) {
		drawTree(x,y);
		click.count = 0;
	} else if (item == MENU_ITEM_ROAD) {
		if (click.count == 1) {
			click.x1 = x;
			click.y1 = y;
		} else if (click.count == 2) {
			click.x2 = x;
			click.y2 = y;
			drawRoad(click.x1,click.y1,click.x2,click.y2);
			click.count = 0;
		}
	}
	
}

void onMouseClick(int button, int state, int x, int y) {
	//click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int item = getMenuHighlightedItem(x,y);
		if (item == MENU_NO_ITEM) {
			drawItem(menuSelectedItem, x, y);
		} else {
			setMenuSelectedItem(item);
			click.count = 0;
		}
	}
}

void onMenuSelect(int option)
{
	switch(option)
	{
		case 1:
			glutDisplayFunc(display3D);
			break;
		case 2:
			glutDisplayFunc(display2D);
			break;
	}
}


int main(int argc, char * argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Example");
	
	// onPaint
	glutDisplayFunc(display3D);
	// onTimer
	glutIdleFunc(idle);
	glutMouseFunc(onMouseClick);
	//glutSpecialFunc(SpecialKey);
	//glutKeyboardFunc(Keyboard);
	
	glutCreateMenu(onMenuSelect);
	glutAddMenuEntry("3D View",1);
	glutAddMenuEntry("2D View",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	init();
	glutMainLoop();
    return 0;
}


