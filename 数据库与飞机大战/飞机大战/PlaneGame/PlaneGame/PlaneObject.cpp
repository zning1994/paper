// PlaneObject.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "PlaneObject.h"


// CPlaneObject
CPlaneObject::CPlaneObject()
{
}

CPlaneObject::~CPlaneObject()
{
}


// CPlaneObject 成员函数



CPoint CPlaneObject::getPosition()
{
	return pos;
}

int CPlaneObject::setSpeed(int s)
{
	speed =s;
	return 0;
}

int CPlaneObject::setPosition(int x,int y)
{
	pos.x=x;
	pos.y=y;
	return 0;
}
