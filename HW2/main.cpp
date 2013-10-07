//
//  main.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/7/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#include "main.h"

double angle=PI,dangle=0.0,start=0;
double dx=0,dy=0,dz=0;
double speed = 0;
double planex=0,planey=0,planez=0;
double plane_angle=PI/2,plane_speed=0,plane_ang_speed=0;

Terrain* terrain;
Car* car;
Camera* camera;
Overflow* overflow;
void init()
{
	glClearColor(0.4,0.4,0.4,0); // set background color
	glEnable(GL_DEPTH_TEST);
	
	srand((unsigned)time(NULL));

	overflow = new Overflow();
	camera = new Camera();	
	
	terrain = new Terrain();
	
	terrain->init();
	
	car = new Car();

	//worldInit();

	overflow->init();
	//menuInit();
	//drawMenu();
	
}



void display2D()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,WIDTH,HEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,1,200);
	gluLookAt(
		camera->pos.x,camera->pos.y,camera->pos.z,
		camera->pos.x+camera->sight.x,camera->pos.y+camera->sight.y,camera->pos.z+camera->sight.z,
		camera->up.x,camera->up.y,camera->up.z
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
	
	car->draw2d();
	
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
	glutCreateWindow("HW2");
	
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


