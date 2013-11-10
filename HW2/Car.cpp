//
//  Car.cpp
//  Final Project
//
//  Created by Alex Gavrishev.
//

#include "Car.h"


Car::Car(void)
{
	pos.x = 10.0f;
	pos.y = 0;
	pos.z = -17.0f;

	speed = 0;
	mAngleSpeed = 0;
	mDistDiff = 0;
	mAngleWheelX = 0;
	angle = PI;

}


Car::~Car(void)
{
}

void Car::update() {
	// Calcualte new position
	angle+=mAngleSpeed;
	double newX = pos.x + (-speed*sin(angle+PI/2));
	double newZ = pos.z + (-speed*cos(angle+PI/2));

	int gridX = newX + GRID_OFFSET;
	int gridY = newZ + GRID_OFFSET;
	// Check that car on the road
	if (!mRoad->isRoad(gridY, gridX)) {
		return;
	}
	// Calclate travelled distance
	mDistDiff = sqrt ( pow((newX-pos.x), 2) + pow((newZ-pos.z), 2) );

	pos.x = newX;
	pos.z = newZ;
}

void Car::draw3d() {
	
	// car
	glPushMatrix();
		glTranslated(pos.x,pos.y,pos.z);
		glRotated(angle*180/PI,0,1,0);
		draw();
	glPopMatrix();
	
	/* draw view target
	double aSin = sin(carUser->angle+PI/2);
	double aCos = cos(carUser->angle+PI/2);
	double cx = carUser->pos.x - 0.2f - 5*aSin;
	double cy = carUser->pos.y + 1.8f;
	double cz = carUser->pos.z - 0.4f - 5*aCos;
	glPushMatrix();
		glTranslated(cx,cy,cz);
		glRotated(carUser->angle*180/PI,0,1,0);
		glBegin(GL_POLYGON);
		glColor3d(0.0f,0.7f,0.0f);
			glVertex3d(-0.5f, 0.5f, -0.5f);              // Top Left
			glVertex3d(-0.5f, 0.5f, 0.5f);              // Top Right
			glVertex3d(-0.5f, 0.0f, 0.5f);              // Bottom Right
			glVertex3d(-0.5f, 0.0f, -0.5f);              // Bottom Left
		glEnd();
	glPopMatrix();
	*/
}



void Car::draw() {
	PIXEL dk;
	dk.red = mColor.red * 0.9f;
	dk.green = mColor.green * 0.9f;
	dk.blue = mColor.red * 0.9f;

	glColor3d(dk.red/255.0f,dk.green/255.0f,dk.blue/255.0f);

	//front
	glBegin(GL_POLYGON);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();
	
	//back
	glBegin(GL_POLYGON);
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();
	
	glColor3d(mColor.red/255.0f,mColor.green/255.0f,mColor.blue/255.0f);

	//left
	glBegin(GL_POLYGON);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Bottom Left
	glEnd();

	//right
	glBegin(GL_POLYGON);
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Left
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
		glVertex3d(-4.5f, 0.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 0.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 0.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 0.6f, 3.0f);              // Bottom Left
	glEnd();

	//trunk
	glBegin(GL_POLYGON);
		glVertex3d(-4.5f, 1.6f, -3.0f);              // Top Left
		glVertex3d(-2.0f, 1.6f, -3.0f);              // Top Right
		glVertex3d(-2.0f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d(-4.5f, 1.6f, 3.0f);              // Bottom Left
	glEnd();
	
	//motor
	glBegin(GL_POLYGON);
		glVertex3d( 2.0f, 1.6f, -3.0f);              // Top Left
		glVertex3d( 4.5f, 1.6f, -3.0f);              // Top Right
		glVertex3d( 4.5f, 1.6f, 3.0f);              // Bottom Right
		glVertex3d( 2.0f, 1.6f, 3.0f);              // Bottom Left
	glEnd();

	//top
	glBegin(GL_POLYGON);
		glVertex3d(-1.5f,2.6f, -3.0f);              // Top Left
		glVertex3d( 1.5f,2.6f, -3.0f);              // Top Right
		glVertex3d( 1.5f,2.6f, 3.0f);              // Bottom Right
		glVertex3d(-1.5f,2.6f, 3.0f);              // Bottom Left
	glEnd();

	//glEnable(GL_COLOR_MATERIAL);
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


	/* Rotate wheels:
		1. find the circumference of the wheel. Circumference = 2 * pi * radius
		2. Each frame, calculate the distance traveled this frame (in Update function).
		Magnitude of the vector that points from the position during the previous frame to the position during this frame. Vector from A to B = B - A
		3. Divide this distance by the circumference to find the fraction of a full rotation.
		4. Multiply by 360 to convert to degrees.
		5. Rotate wheel by that much.
	*/

	double circumference = 2 * PI * 0.7f;
	double rotAngle = (mDistDiff/circumference) * 360;
	mAngleWheelX-=rotAngle;

	// Wheels
	glPushMatrix();
		glTranslated(2.5f,0.7f,-3.1f);
		glRotated(90,0,1,0);
		glRotated(mAngleWheelX,1,0,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(2.5f,0.7f,3.1f);
		glRotated(90,0,1,0);
		glRotated(mAngleWheelX,1,0,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5f,0.7f,-3.1f);
		glRotated(90,0,1,0);
		glRotated(mAngleWheelX,1,0,0);
		drawWheel();
	glPopMatrix();

	glPushMatrix();
		glTranslated(-2.5f,0.7f,3.1f);
		glRotated(90,0,1,0);
		glRotated(mAngleWheelX,1,0,0);
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
		glVertex3d(0,x,y);
	}
	glEnd();

	//silver
	glColor3d(0.75f,0.75f,0.75f);
	glBegin(GL_LINES);
	for(alpha = 0; alpha<2*PI;alpha+=PI/4)
	{
		x = 0.68*cos(alpha);
		y = 0.68*sin(alpha);
		glVertex3d(0,x,y);
		glVertex3d(0,0,0);
	}
	glEnd();
	glLineWidth(1.0f);

}