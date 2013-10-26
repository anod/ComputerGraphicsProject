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

		center.x = pos.x;
		center.y = pos.y-0.2f;
		center.z = pos.z-1.0f;

	} else {
		double aSin = sin(mCar->angle+PI/2);
		double aCos = cos(mCar->angle+PI/2);

		pos.x = mCar->pos.x - 0.2f + 2*aSin;
		pos.y = mCar->pos.y + 2.0f;
		pos.z = mCar->pos.z + 2.0f + 2*aCos;

		center.x = pos.x - 0.99f + 3*aSin,
		center.y = pos.y - 0.2f;
		center.z = pos.z + 3*aCos;

	}

	up.x = 0;
	up.y = 1;
	up.z = 0;


}


void Camera::update() {


	if (mViewMode == VIEW_INSIDE) {
		double aSin = sin(mCar->angle+PI/2);
		double aCos = cos(mCar->angle+PI/2);

		pos.x = mCar->pos.x - 0.2f + 2*aSin;
		pos.y = mCar->pos.y + 2.0f;
		pos.z = mCar->pos.z + 2.0f + 2*aCos;

		center.x = mCar->pos.x - 0.2f + 3*aSin,
		center.y = mCar->pos.y + 1.8f;
		center.z = mCar->pos.z + 2.0f + 3*aCos;

	} else {
		mAngle += mDirectionAngle;
		double sight_x = sin(mAngle);
		double sight_z = cos(mAngle);
		pos.x += sight_x * mSpeed;
		pos.y += mLevelY;
		pos.z += sight_z * mSpeed;

		center.x = pos.x + sight_x;
		center.z = pos.z + sight_z;
	}
}


