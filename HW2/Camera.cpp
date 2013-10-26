#include "Camera.h"




Camera::Camera(void)
{	
	mViewMode = VIEW_DEFAULT;

	reset();

}

Camera::~Camera(void)
{

}

void Camera::reset() {
	mAngle = PI/2;
	mDirectionAngle=0.0;
	mSpeed = 0.0;
	mLevelY = 0.0;

	if (mViewMode == VIEW_DEFAULT) {

		pos.x = DEF_POS_X;
		pos.y = DEF_POS_Y;
		pos.z = DEF_POS_Z;

		sight.x = 0;
		sight.y = -0.2f;
		sight.z = -1.0f;

	} else {
		

		pos.x = mCar->pos.x+0.1;
		pos.y = mCar->pos.y + 1.8f;
		pos.z = mCar->pos.z-1.0f;

		sight.x = -0.99;
		sight.y = -0.2f;
		sight.z = 0.0f;
	}


	up.x = 0;
	up.y = 1;
	up.z = 0;



}


void Camera::update() {
		mAngle += mDirectionAngle;
		sight.x = sin(mAngle);
		sight.z = cos(mAngle);
		pos.x += sight.x * mSpeed;
		pos.y += mLevelY;
		pos.z += sight.z * mSpeed;
}


