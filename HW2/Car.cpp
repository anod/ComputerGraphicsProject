//
//  Car.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#include "Car.h"


Car::Car(void)
{
}


Car::~Car(void)
{
}

void Car::draw3d() {
	draw();
}

void Car::draw2d() {
	draw();
}


void Car::draw() {

	//front
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
	glVertex3d(-4.5f, 1.2f, -3.0f);              // Top Left
	glVertex3d(-4.5f, 1.2f, 3.0f);              // Top Right
	glVertex3d(-4.5f, 0.2f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f, 0.2f, -3.0f);              // Bottom Left
    glEnd();
	
	//back
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
	glVertex3d( 4.5f, 1.2f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.2f, 3.0f);              // Top Right
	glVertex3d( 4.5f, 0.2f, 3.0f);              // Bottom Right
	glVertex3d( 4.5f, 0.2f, -3.0f);              // Bottom Left
    glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
	glVertex3d(-4.5f, 1.2f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.2f, -3.0f);              // Top Right
	glVertex3d( 4.5f, 0.2f, -3.0f);              // Bottom Right
	glVertex3d(-4.5f, 0.2f, -3.0f);              // Bottom Left
    glEnd();

	//right
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
	glVertex3d(-4.5f, 1.2f, 3.0f);              // Top Left
	glVertex3d( 4.5f, 1.2f, 3.0f);              // Top Right
	glVertex3d( 4.5f, 0.2f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f, 0.2f, 3.0f);              // Bottom Left
    glEnd();
	
	//bottom
	glBegin(GL_POLYGON);
	glColor3d(0.6f,0.6f,0.6f);
	glVertex3d(-4.5f, 0.2f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 0.2f, -3.0f);              // Top Right
	glVertex3d( 4.5f, 0.2f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f, 0.2f, 3.0f);              // Bottom Left
    glEnd();

	//trunk
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0,0);
	glVertex3d(-4.5f, 1.2f, -3.0f);              // Top Left
	glVertex3d(-2.0f, 1.2f, -3.0f);              // Top Right
	glVertex3d(-2.0f, 1.2f, 3.0f);              // Bottom Right
	glVertex3d(-4.5f, 1.2f, 3.0f);              // Bottom Left
    glEnd();

	
	//motor
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0,0);
	glVertex3d( 2.0f, 1.2f, -3.0f);              // Top Left
	glVertex3d( 4.5f, 1.2f, -3.0f);              // Top Right
	glVertex3d( 4.5f, 1.2f, 3.0f);              // Bottom Right
	glVertex3d( 2.0f, 1.2f, 3.0f);              // Bottom Left
    glEnd();

	//top
	glBegin(GL_POLYGON);
	glColor3d(1.0f,0.0f,0.0f);
	glVertex3d(-1.5f,2.2f, -3.0f);              // Top Left
	glVertex3d( 1.5f,2.2f, -3.0f);              // Top Right
	glVertex3d( 1.5f,2.2f, 3.0f);              // Bottom Right
	glVertex3d(-1.5f,2.2f, 3.0f);              // Bottom Left
    glEnd();

	// Transparent glasses
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0,0,0,0.6);

	//front glass
	glBegin(GL_POLYGON);
	glVertex3d( 1.5f, 2.2f, -3.0f);              // Top Left
	glVertex3d( 1.5f, 2.2f, 3.0f);              // Top Right
	glVertex3d( 2.0f, 1.2f, 3.0f);              // Bottom Right
	glVertex3d( 2.0f, 1.2f, -3.0f);              // Bottom Left
    glEnd();

	//back glass
	glBegin(GL_POLYGON);
	glVertex3d( -1.5f, 2.2f, -3.0f);              // Top Left
	glVertex3d( -1.5f, 2.2f, 3.0f);              // Top Right
	glVertex3d( -2.0f, 1.2f, 3.0f);              // Bottom Right
	glVertex3d( -2.0f, 1.2f, -3.0f);              // Bottom Left
    glEnd();

	//right glass
	glBegin(GL_POLYGON);
	glVertex3d( -1.5f, 2.2f, 3.0f);              // Top Left
	glVertex3d(  1.5f, 2.2f, 3.0f);              // Top Right
	glVertex3d( 2.0f, 1.2f,  3.0f);              // Bottom Right
	glVertex3d( -2.0f, 1.2f, 3.0f);              // Bottom Left
    glEnd();

	//left glass
	glBegin(GL_POLYGON);
	glVertex3d( -1.5f, 2.2f, -3.0f);              // Top Left
	glVertex3d(  1.5f, 2.2f, -3.0f);              // Top Right
	glVertex3d( 2.0f, 1.2f,  -3.0f);              // Bottom Right
	glVertex3d( -2.0f, 1.2f, -3.0f);              // Bottom Left
    glEnd();

	glDisable(GL_BLEND);


}
