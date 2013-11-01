#include "Light.h"


Light::Light(void)
{
}


Light::~Light(void)
{
}

void Light::init() {

	// light 1 definitions
float ltamb1[4] = {0.4,0.3,0.3,0}; 
float ltdiff1[4] = {0.7,0.5,0.5,0}; 
float ltspec1[4] = {.6,.4,.4,0}; 
float ltpos1[4] = {0.6,2,0.2,0}; // 0 means directional light
	
									// 1 means positional
}

void Light::enable() {

//	glLightfv(GL_LIGHT0,GL_AMBIENT,ltamb1);
//	glLightfv(GL_LIGHT0,GL_DIFFUSE,ltdiff1);
//	glLightfv(GL_LIGHT0,GL_SPECULAR,ltspec1);
//	glLightfv(GL_LIGHT0,GL_POSITION,ltpos1);
//	glLightf(GL_LIGHT0,GL_SHININESS,100);

}