#pragma once
#include "planeobject.h"
#include "atltypes.h"

class Cball :
	public CPlaneObject
{
public:
	Cball();
	Cball(int index,int type);
	~Cball(void);
	int move(int direction);
	static int LoadImage();
	static CBitmap bmpDraw;
	int draw(CDC* pdc);
	int index;
	int type;
	int move(CPoint p);
	int move();
	CRect getRect(void);
};
