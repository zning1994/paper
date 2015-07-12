#pragma once
#include "planeobject.h"
#include "afxwin.h"
#include "atltypes.h"

class Cboss :
	public CPlaneObject
{
public:
	Cboss();
	~Cboss(void);
	static CBitmap bmpDraw;
	static int LoadImage(void);
	CRect getRect(void);
	int draw(CDC* pdc);
	int move();
	int move(CPoint p);
	CPoint point;
};
