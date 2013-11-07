//
//  Car.h
//  Home Work 2
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
	void setColor(PIXEL color) { 
		mColor = color;
	};

	void left() { mAngleSpeed+=0.002; };
	void right() { mAngleSpeed-=0.002; };
	void forward() { speed += 0.01; };
	void backward() { speed -= 0.01; };

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