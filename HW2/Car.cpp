//
//  Car.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#include "Car.h"


Car::Car(void)
{
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	speed = 0;
	mAngleSpeed = 0;
	angle = PI/2;

}


Car::~Car(void)
{
}

void Car::update() {
	// plane
	angle+=mAngleSpeed;
	pos.x+=-speed*sin(angle+PI/2);
	pos.z+=-speed*cos(angle+PI/2);
}

void Car::draw3d() {
	
	// car
	glPushMatrix();
		glTranslated(pos.x,pos.y,pos.z);
		glRotated(angle*180/PI,0,1,0);
		draw();
	glPopMatrix();
	
}



void Car::draw() {

	//front
	glBegin(GL_POLYGON);
	glColor3d(0.6f,0.0f,0.0f);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();
	
	//back
	glBegin(GL_POLYGON);
	glColor3d(0.6f,0.0f,0.0f);
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Left
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glColor3d(0.3f,0.0f,0.0f);
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Left
	glEnd();

	//trunk
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0,0);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d(-2.0f, 1.6f, -3.0f);              // Top Right
		glVertex3d(-2.0f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Bottom Left
	glEnd();

	
	//motor
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0,0);
		glVertex3d( 2.0f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d( 2.0f, 1.6f, 3.0f);              // Bottom Left
	glEnd();

	//top
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
		glVertex3d(-1.5f,2.6f, -3.0f);              // Top Left
		glVertex3d( 1.5f,2.6f, -3.0f);              // Top Right
		glVertex3d( 1.5f,2.6f, 3.0f);              // Bottom Right
		glVertex3d(-1.5f,2.6f, 3.0f);              // Bottom Left
	glEnd();

	// Transparent glasses
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0,0,0,0.6);

	//front glass
	glBegin(GL_POLYGON);
		glVertex3d( 1.5f, 2.6f, -3.0f);              // Top Left
		glVertex3d( 1.5f, 2.6f, 3.0f);              // Top Right
		glVertex3d( 2.0f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d( 2.0f, 1.6f, -3.0f);              // Bottom Left
	glEnd();

	//back glass
	glBegin(GL_POLYGON);
		glVertex3d( -1.5f, 2.6f, -3.0f);              // Top Left
		glVertex3d( -1.5f, 2.6f, 3.0f);              // Top Right
		glVertex3d( -2.0f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d( -2.0f, 1.6f, -3.0f);              // Bottom Left
	glEnd();

	//right glass
	glBegin(GL_POLYGON);
		glVertex3d( -1.5f, 2.6f, 3.0f);              // Top Left
		glVertex3d(  1.5f, 2.6f, 3.0f);              // Top Right
		glVertex3d( 2.0f, 1.6f,  3.0f);              // Bottom Right
		glVertex3d( -2.0f, 1.6f, 3.0f);              // Bottom Left
	glEnd();

	//left glass
	glBegin(GL_POLYGON);
		glVertex3d( -1.5f, 2.6f, -3.0f);              // Top Left
		glVertex3d(  1.5f, 2.6f, -3.0f);              // Top Right
		glVertex3d( 2.0f, 1.6f,  -3.0f);              // Bottom Right
		glVertex3d( -2.0f, 1.6f, -3.0f);              // Bottom Left
	glEnd();

	glDisable(GL_BLEND);

	// Wheels
	glPushMatrix();
		glTranslated(2.5f,1.0f,-3.0f);
		glRotated(90,0,1,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.5f,1.0f,3.0f);
		glRotated(90,0,1,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5f,1.0f,-3.0f);
		glRotated(90,0,1,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5f,1.0f,3.0f);
		glRotated(90,0,1,0);
		drawWheel();
	glPopMatrix();
}

void Car::drawWheel()
{
	double alpha,x,y;
	glColor3d(0,0,0);
	glLineWidth(25.0f);
	glScaled(0,0.5,0.5);
	glBegin(GL_LINE_LOOP);
	for(alpha = 0; alpha<2*PI;alpha+=PI/1000)
	{
		x = 0.7*cos(alpha);
		y = 0.7*sin(alpha);
		glVertex3d(0,x-0.5f,y);
	}
	glEnd();

	//silver
	glColor3d(0.75f,0.75f,0.75f);
	glBegin(GL_LINES);
	for(alpha = 0; alpha<2*PI;alpha+=PI/5)
	{
		x = 0.68*cos(alpha);
		y = 0.68*sin(alpha);
		glVertex3d(0,x-0.5f,y);
		glVertex3d(0,-0.5f,0);
	}
	glEnd();
	glLineWidth(1.0f);

}