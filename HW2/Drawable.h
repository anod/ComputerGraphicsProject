//
//  Drawable.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/21/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
public:
	virtual void draw3d() = 0;
	virtual void draw2d() = 0;
	virtual ~Drawable(void)	{}
};

#endif
