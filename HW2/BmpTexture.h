//
//  BmpTexture.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef BMP_TEXTURE_H
#define BMP_TEXTURE_H

#include "general.h"
#include <stdio.h>

class BmpTexture
{
public:
	BmpTexture(int id);
	~BmpTexture(void);
	void load(char *fname);
	int getId() { return mId; };
private:

	static const int TW = 256;
	static const int TH = 256;

	int mId;
	unsigned char mTexture[TH][TW][4]; // roof texture
	unsigned char* mBmp;

	void readBmp(char *fname);

};

#endif
