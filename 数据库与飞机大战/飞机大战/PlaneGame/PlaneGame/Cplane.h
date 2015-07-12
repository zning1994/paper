#pragma once
#include "planeobject.h"

class Cplane :
	public CPlaneObject
{
public:
	Cplane(void);
	~Cplane(void);
	static int LoadImage(void);
	static CBitmap bmpDraw;
	int draw(CDC* pdc);
	int move(int direction);
	CRect getRect(void);
};
