//
//  Car.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef CAR_H
#define CAR_H

#include "general.h"

class Car
{
public:
	Car(void);
	~Car(void);
	virtual void draw3d();
	virtual void draw2d();

	THREE pos;
	double speed;
	double angle;
private:
	void draw();
	void drawWheel();
};

#endif //CAR_H