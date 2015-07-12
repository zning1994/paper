#pragma once
#include "afxwin.h"

// CPlaneObject ÃüÁîÄ¿±ê

class CPlaneObject : public CObject
{
public:
	CPlaneObject();
	virtual ~CPlaneObject();
	CPoint pos;
	int speed;
	CPoint getPosition();
	int setSpeed(int s);
	int setPosition(int x,int y);
};


