#include "Light.h"


Light::Light(void)
{
}


Light::~Light(void)
{
}

void Light::enable() {
	// Enable lighting
	glEnable(GL_LIGHT0);

	// {x,y,z,w} w = 0 to create a directional light (x,y,z is the light direction) like the sun
	// light 1 definitions
	float ltamb1[4] = {0.4,0.3,0.3,0}; 
	float ltdiff1[4] = {1.0,1.0,1.0,0}; 
	float ltspec1[4] = {.6,.4,.4,0}; 
	float ltpos1[4] = {0.6,2,0.2,0};

	glLightfv(GL_LIGHT0,GL_AMBIENT,ltamb1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,ltdiff1);
	glLightfv(GL_LIGHT0,GL_SPECULAR,ltspec1);
	glLightfv(GL_LIGHT0,GL_POSITION,ltpos1);
	glLightf(GL_LIGHT0,GL_SHININESS,100);

}