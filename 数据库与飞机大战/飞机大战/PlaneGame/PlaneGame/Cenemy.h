#pragma once
#include "planeobject.h"
#include "afxwin.h"

class Cenemy :
	public CPlaneObject
{
public:
	Cenemy(int direction);
	~Cenemy(void);
	int draw(CDC* pdc);
	static CImageList imgList;
	static int LoadImage(void);
	int index;
	int direction;
	int move(int direction);
	CRect getRect(void);
};
