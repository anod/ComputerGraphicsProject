//
//  Car.h
//  Final Project
//
//  Created by Alex Gavrishev.
//

#ifndef CAR_H
#define CAR_H

#include "general.h"
#include "Road.h"

class Car
{
public:
	Car(void);
	~Car(void);

	void setRoad(Road* road) { mRoad = road; };
	void setColor(PIXEL color) { mColor = color; };
	void setPosition(float x, float y, float z) { pos.x = x; pos.y = y; pos.z = z; };
	void setAngle(double value) { angle = value; };
	void setSpeed(double value) { speed = value; };

	void left() { mAngleSpeed+=0.002; };
	void right() { mAngleSpeed-=0.002; };
	void forward() { speed += 0.01; };
	void backward() { speed -= 0.01; };
	bool isMoving() { return (speed > 0); };
	void stop() { speed = 0; };

	void draw3d();
	void update();

	THREE pos;
	double speed;
	double angle;
private:
	Road* mRoad;
	PIXEL mColor;

	void draw();
	void drawWheel();

	double mDistDiff;
	double mAngleSpeed;
	double mAngleWheelX;
};

#endif //CAR_H