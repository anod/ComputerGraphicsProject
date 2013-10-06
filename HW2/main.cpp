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

void drawTerrain();
void drawHeightColor(double h);

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
	
	
	terrainInit();
	
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

void drawTerrain() {
		int i,j;
		
		for(i=1;i<GRID_SIZE;i++)
			for(j=1;j<GRID_SIZE;j++)
			{
				//			glBegin(GL_LINE_LOOP);
				glBegin(GL_POLYGON);
				drawHeightColor(grid[i][j]);
				glVertex3d(j-GRID_SIZE/2,grid[i][j],i-GRID_SIZE/2);
				drawHeightColor(grid[i][j-1]);
				glVertex3d(j-1-GRID_SIZE/2,grid[i][j-1],i-GRID_SIZE/2);
				drawHeightColor(grid[i-1][j-1]);
				glVertex3d(j-1-GRID_SIZE/2,grid[i-1][j-1],i-1-GRID_SIZE/2);
				drawHeightColor(grid[i-1][j]);
				glVertex3d(j-GRID_SIZE/2,grid[i-1][j],i-1-GRID_SIZE/2);
				glEnd();
			}
		
		// water
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0,0,0.5,0.7);
		glBegin(GL_POLYGON);
		glVertex3d(-GRID_SIZE/2,0,-GRID_SIZE/2);
		glVertex3d(GRID_SIZE/2,0,-GRID_SIZE/2);
		glVertex3d(GRID_SIZE/2,0,GRID_SIZE/2);
		glVertex3d(-GRID_SIZE/2,0,GRID_SIZE/2);
		glEnd();
		glDisable(GL_BLEND);

}

void drawHeightColor(double h)
{
	if(h>-5)
	{
		h=fabs(h);
		if(h>0 && h<0.4) // sand
			glColor3d(0.8,0.8,0.5);
		else if(h<5)
			glColor3d(0.2+h/30,(5-h)/6,0);
		else glColor3d(h/11,h/11,h/10);
	}
	else glColor3d(0,0,0);
}

void DrawPlane()
{
	// front
	glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(2.3,0.3,0);
	glVertex3d(1.5,0.3,0.4);
	glVertex3d(1.5,0.5,0);
	glEnd();
	glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(2.3,0.3,0);
	glVertex3d(1.5,0.3,-0.4);
	glVertex3d(1.5,0.5,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(1,1,1);
	glVertex3d(3.2,0,0);
	glColor3d(0.7,0.7,0.7);
	glVertex3d(1.5,0,0.5);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(1.5,0.3,0.4);
	glVertex3d(2.3,0.3,0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3d(1,1,1);
	glVertex3d(3.2,0,0);
	glColor3d(0.7,0.7,0.7);
	glVertex3d(1.5,0,-0.5);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(1.5,0.3,-0.4);
	glVertex3d(2.3,0.3,0);
	glEnd();
	// middle
	glBegin(GL_POLYGON);
	glColor3d(0.7,0.7,0.7);
	glVertex3d(1.5,0,0.5);
	glColor3d(0.8,0.8,0.8);
	glVertex3d(1.5,0.3,0.4);
	glColor3d(0.5,0.5,0.5);
	glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(0.8,0.8,0.8);
	glVertex3d(1.5,0.3,0.4);
	glColor3d(0.5,0.5,0.8);
	glVertex3d(1.5,0.5,0);
	glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(0.7,0.7,0.7);
	glVertex3d(1.5,0,-0.5);
	glColor3d(0.8,0.8,0.8);
	glVertex3d(1.5,0.3,-0.4);
	glColor3d(0.5,0.5,0.5);
	glVertex3d(-3.5,0,0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(0.8,0.8,0.8);
	glVertex3d(1.5,0.3,-0.4);
	glColor3d(0.5,0.5,0.8);
	glVertex3d(1.5,0.5,0);
	glVertex3d(-3.5,0,0);
	glEnd();
	// wings
	glBegin(GL_POLYGON);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(1.5,0.2,0);
	glVertex3d(-0.5,0.2,2.5);
	glVertex3d(-1,0.2,2.5);
	glVertex3d(-0.5,0.1,0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(1.5,0.2,0);
	glVertex3d(-0.5,0.2,-2.5);
	glVertex3d(-1,0.2,-2.5);
	glVertex3d(-0.5,0.1,0);
	glEnd();
	// back

	glBegin(GL_POLYGON);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(-1,0,0);
	glColor3d(0.6,0.6,1);
	glVertex3d(-3.3,1,0);
	glVertex3d(-3.6,1,0);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(-3.2,0,0);
	glEnd();
	// back wings
	glBegin(GL_POLYGON);
	glColor3d(0.6,0.6,0.6);
	glVertex3d(-1.5,0,0);
	glVertex3d(-2.5,0,1);
	glVertex3d(-2.7,0,1);
	glVertex3d(-2.7,0,-1);
	glVertex3d(-2.5,0,-1);
	glEnd();



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
	
	drawTerrain();
	
	
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
	
	drawTerrain();
	
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


