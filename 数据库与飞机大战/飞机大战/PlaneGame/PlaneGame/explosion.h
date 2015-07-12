#pragma once
#include "afxwin.h"
#include "atltypes.h"

// Cexplosion ÃüÁîÄ¿±ê

class Cexplosion : public CObject
{
public:
	Cexplosion();
	Cexplosion(int x,int y);
	virtual ~Cexplosion();
	int draw(CDC* pdc);
	static CImageList imgList;
	static int LoadImage(void);
	int index;
	CPoint pos;
};


