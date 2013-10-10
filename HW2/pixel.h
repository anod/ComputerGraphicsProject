//
//  Pixel.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef PIXEL_H_
#define PIXEL_H_

typedef struct
{
	// 0 - 255
	unsigned char red,green,blue;
} PIXEL;

static const PIXEL PIX_BROWN = {153,101,52};
static const PIXEL PIX_PINK = {255,20,147};
static const PIXEL PIX_WHITE = {255,255,255};
static const PIXEL PIX_BLACK = {  0,  0,  0};
static const PIXEL PIX_DK_GREEN  = {0,99,0};
static const PIXEL PIX_GREEN  = {3,150,0};
static const PIXEL PIX_DK_BLUE  = {0,53,102};
static const PIXEL PIX_DK_BROWN = {64,42,22};

static const PIXEL PIX_GREY  = {105,103,98};
static const PIXEL PIX_LT_GREY  = {204,204,204};
static const PIXEL PIX_DK_GREY  = {61,56,54};


#endif //PIXEL_H_