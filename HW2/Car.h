//
//  Car.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef CAR_H
#define CAR_H

#include "drawable.h"
#include "glut.h"

class Car :
	public Drawable
{
public:
	Car(void);
	~Car(void);
	virtual void draw3d();
	virtual void draw2d();
private:
	void draw();
};

#endif //CAR_H