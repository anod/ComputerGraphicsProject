#include "BmpTexture.h"


BmpTexture::BmpTexture(int id)
{
	mId = id;
}


BmpTexture::~BmpTexture(void)
{
}

void BmpTexture::load(char *fname)
{
	readBmp(fname);
	int k=0;
	for(int i=0;i<TH;i++) {
		for(int j=0;j<TW;j++) {
			mTexture[i][j][0] = mBmp[k+2]; //red
			mTexture[i][j][1] = mBmp[k+1];  // green
			mTexture[i][j][2] = mBmp[k];    // blue
			mTexture[i][j][3] = 0;
			k+=3;
		}
	}

	glBindTexture(GL_TEXTURE_2D,mId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,4,TW,TH,0,GL_RGBA,GL_UNSIGNED_BYTE,mTexture);
}

void BmpTexture::readBmp(char *fname)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	int size;
	FILE* pf;
	pf = fopen(fname,"rb");

	fread(&bf,sizeof(BITMAPFILEHEADER),1,pf);
	fread(&bi,sizeof(BITMAPINFOHEADER),1,pf);
	size = bi.biWidth*bi.biHeight*3;
	mBmp = (unsigned char*) malloc(size);
	fread(mBmp,1,size,pf);

	fclose(pf);
}
