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
	bmpDraw.LoadBitmap(IDB_MYPLANE);//װ��DDB
	return 0;
}

int Cplane::draw(CDC* pdc)
{
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pdc);//����DC
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
	pdc->TransparentBlt(pos.x,pos.y,50,60,&memDC,0,0,50,60,RGB(0,0,0));
	memDC.SelectObject(pbmpOld);//ѡ��ԭDDB
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
