//
//  Camera.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
	double x,y,z;
} THREE;

class Camera
{
public:
	Camera(void);
	~Camera(void);

// eyex,eyey,eyez - represent the camera position
// sightx,sighty,sightz - represent the camera view direction
// 0,1,0 represent the camera up vector
	THREE pos; //represent the camera position
	THREE sight; // - represent the camera view direction
	THREE up; //epresent the camera up vector
};

#endif //CAMERA_H