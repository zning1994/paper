#include "StdAfx.h"
#include "Cplane.h"
#include "Resource.h"
CBitmap Cplane::bmpDraw;
Cplane::Cplane(void)
{
	pos.x=350;
	pos.y=350;
	speed=10;
}


Cplane::~Cplane(void)
{
}

int Cplane::LoadImage(void)
{
	bmpDraw.LoadBitmap(IDB_MYPLANE);//装入DDB
	return 0;
}

int Cplane::draw(CDC* pdc)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pdc);//创建DC
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pdc->TransparentBlt(pos.x,pos.y,50,60,&memDC,0,0,50,60,RGB(0,0,0));
	memDC.SelectObject(pbmpOld);//选入原DDB
	return 0;
}

int Cplane::move(int direction)
{
	if(direction==1)
		pos.x-=speed;
	if(direction==2)
		pos.x+=speed;
	if(direction==3)
		pos.y-=speed;
	if(direction==4)
		pos.y+=speed;
	return 0;
}

CRect Cplane::getRect(void)
{
	return CRect(pos,CPoint(pos.x+50,pos.y+60));
}
