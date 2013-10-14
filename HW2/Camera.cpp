#include "Camera.h"


Camera::Camera(void)
{
	pos.x = 0;
	pos.y = 10;
	pos.z = 15;
	
	sight.x = 0;
	sight.y = -0.2f;
	sight.z = -1.0f;
	
	up.x = 0;
	up.y = 1;
	up.z = 0;
}


Camera::~Camera(void)
{

}
