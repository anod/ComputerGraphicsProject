#include "RoadTexture.h"


RoadTexture::RoadTexture(int id)
{
	mId = id;
}


RoadTexture::~RoadTexture(void)
{
}

void RoadTexture::load() {
	int k = 0;
	for(int i=0;i<TH;i++) {
		for(int j=0;j<TW;j++)
		{
			if((j<TW/3 || j>2*TW/3)&& i >= TH/2-10 && i<=TH/2+10)
			{
				mTexture[i][j][0] = 220; // red
				mTexture[i][j][1] = 220; // green
				mTexture[i][j][2] = 220; // blue
				mTexture[i][j][3] = 0; // alpha
			}
			else
			{
				k = -10+rand()%20;
				mTexture[i][j][0] = 100+k; // red
				mTexture[i][j][1] = 100+k; // green
				mTexture[i][j][2] = 100+k; // blue
				mTexture[i][j][3] = 0; // alpha
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D,mId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,4,TW,TH,0,GL_RGBA,GL_UNSIGNED_BYTE,mTexture);
}
