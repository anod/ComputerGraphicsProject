//
//  Camera.h
//  Final Project
//
//  Created by Alex Gavrishev.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "general.h"
#include "Car.h"

// Handles different 3d camera modes
class Camera
{
public:
	Camera(void);
	~Camera(void);

	static const int VIEW_DEFAULT = 0;
	static const int VIEW_INSIDE = 1;

	void setViewMode(int viewMode) { mViewMode = viewMode; reset(); };
	void setCar(Car* car) { mCar = car; };

	void left() { mDirectionAngle+=0.001; };
	void right() { mDirectionAngle-=0.001; };
	void forward() { mSpeed+=0.01; };
	void backward() { mSpeed-=0.01; };
	void levelUp() { mLevelY+=0.01; };
	void levelDown() { mLevelY-=0.01; };
	
	void update();
	void reset();

	THREE pos; // - represent the camera position
	THREE center; // - represent the camera view direction
	THREE up; // - represent the camera up vector

private:
	static const int DEF_POS_X=-15;
	static const int DEF_POS_Y=10;
	static const int DEF_POS_Z=5;

	double mAngle;
	double mDirectionAngle;
	double mSpeed;
	double mLevelY;

	int mViewMode;
	Car* mCar;
};

#endif //CAMERA_H