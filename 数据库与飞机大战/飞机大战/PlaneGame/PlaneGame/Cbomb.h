#pragma once
#include "planeobject.h"

class Cbomb :
	public CPlaneObject
{
public:
	Cbomb(void);
	Cbomb(int type,int index);
	~Cbomb(void);
	int move();
	int move(CPoint p);
	static int LoadImage();
	static CBitmap bmpDraw1,bmpDraw2;
	int draw(CDC* pdc);
	CRect getRect(void);
	int type;
	int index;
};
