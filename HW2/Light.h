//
//  Light.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "general.h"

typedef struct
{
	float x,y,z,w;
} LIGHT_VALUE;

class Light
{
public:
	Light(void);
	~Light(void);
	
	void setLight(GLenum light) { mLight = light; };
	void setAmbient(double x,double y,double z,double w) {
		mAmbient.x = x;
		mAmbient.y = y;
		mAmbient.z = z;
		mAmbient.w = w;
	};
	void setDiffuse(double x,double y,double z,double w) {
		mDiffuse.x = x;
		mDiffuse.y = y;
		mDiffuse.z = z;
		mDiffuse.w = w;
	};
	void setSpecular(double x,double y,double z,double w) {
		mSpecular.x = x;
		mSpecular.y = y;
		mSpecular.z = z;
		mSpecular.w = w;
	};
	void setPosition(double x,double y,double z,double w) {
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
		mPosition.w = w;
	};
	void setShininess(int value) {
		mShininess = value;
	}
	void enable();
protected:
	GLenum mLight;
	LIGHT_VALUE mAmbient;
	LIGHT_VALUE mDiffuse;
	LIGHT_VALUE mSpecular;
	LIGHT_VALUE mPosition;
	int mShininess;
};

#endif