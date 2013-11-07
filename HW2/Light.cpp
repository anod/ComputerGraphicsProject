#include "Light.h"

Light::Light(void)
{
	setAmbient(0.4,0.3,0.3,1.0f);
	setDiffuse(0.7,0.5,0.5,1.0f); 
	setSpecular(0.6,0.4,0.4,1.0f); 
	setPosition(0.6,2.0,0.2,0.0f);

	mShininess = 100;
}


Light::~Light(void)
{
}

void Light::enable() {
	// Enable lighting
	glEnable(mLight);

	// {x,y,z,w} w = 0 to create a directional light (x,y,z is the light direction) like the sun
	// light 1 definitions
	float ltamb[4] = {mAmbient.x,mAmbient.y,mAmbient.z,mAmbient.w}; 
	float ltdiff[4] = {mDiffuse.x,mDiffuse.y,mDiffuse.z,mDiffuse.w}; 
	float ltspec[4] = {mSpecular.x,mSpecular.y,mSpecular.z,mSpecular.w}; 
	float ltpos[4] = {mPosition.x,mPosition.y,mPosition.z,mPosition.w}; 

	glLightfv(mLight,GL_AMBIENT,ltamb);
	glLightfv(mLight,GL_DIFFUSE,ltdiff);
	glLightfv(mLight,GL_SPECULAR,ltspec);
	glLightfv(mLight,GL_POSITION,ltpos);
	glLightf(mLight,GL_SHININESS,mShininess);

}