//
//  RoadTexture.h
//  Final Project
//
//  Created by Alex Gavrishev.
//

#ifndef ROAD_TEXTURE_H
#define ROAD_TEXTURE_H

#include "general.h"

class RoadTexture
{
public:
	RoadTexture(int id);
	~RoadTexture(void);
	int getId() { return mId; };
	void load();
private:
	static const int TW = 256;
	static const int TH = 256;

	int mId;
	unsigned char mTexture[TH][TW][4]; // roof texture

};

#endif
