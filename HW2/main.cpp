//
//  main.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/7/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "main.h"

static const int WIDTH = 600;
static const int HEIGHT = 600;

double angle=PI,dangle=0.0,start=0;
double dx=0,dy=0,dz=0;
double speed = 0;
double planex=0,planey=0,planez=0;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;

Terrain* terrain;
Car* car;
Camera* camera;
Overflow* overflow;
//World* world;

void init()
{
	glClearColor(0.4,0.4,0.4,0); // set background color
	glEnable(GL_DEPTH_TEST);
	
	srand((unsigned)time(NULL));

	camera = new Camera();	
	
	terrain = new Terrain();
	terrain->init();
	
	car = new Car();

	overflow = new Overflow();
	overflow->init();
	
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

	overflow->draw();
	terrain->draw2d();

	glutSwapBuffers();
}

void display3D()
{
	// fill the buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,pix);
	
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
	
	terrain->draw3d();
	
	glTranslated(planex,planey, planez);
	//glRotated(plane_angle*180/PI,0,1,0);
	//glRotated(-plane_ang_speed*2000,1,0,0);
	
	car->draw3d();
	//DrawPlane();
	
	glutSwapBuffers();
}

void idle()
{

	glutPostRedisplay();
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
	glutDisplayFunc(display2D);
	// onTimer
	glutIdleFunc(idle);
	glutMouseFunc(onMouseClick);
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


