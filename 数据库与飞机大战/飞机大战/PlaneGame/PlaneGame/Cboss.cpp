#include "StdAfx.h"
#include "Cboss.h"
#include "Resource.h"
CBitmap Cboss::bmpDraw;
Cboss::Cboss()
{
	pos.x=rand()%1000;
	pos.y=rand()%100;
}

Cboss::~Cboss(void)
{
}

int Cboss::LoadImage(void)
{
	bmpDraw.LoadBitmap(IDB_BOSS);//装入DDB
	return 0;
}

CRect Cboss::getRect(void)
{
	return CRect(pos,CPoint(pos.x+96,pos.y+125));
}

int Cboss::draw(CDC* pdc)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pdc);//创建DC
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pdc->TransparentBlt(pos.x,pos.y,96,125,&memDC,0,0,96,125,RGB(0,0,0));//黑色的地方设为透明
	memDC.SelectObject(pbmpOld);//选入原DDB
	return 0;
}

int Cboss::move()
{
	pos.y+=5;
	return 0;
}
int Cboss::move(CPoint p)
{
	double d;
	if(p.y>pos.y){
		if(p.x==pos.x){
			pos.y+=speed;
		}
		else if(p.x>pos.x){
			d = abs((p.x-pos.x)/(p.y-pos.y));
			pos.x+=d*speed;
			pos.y+=speed;
		}
		else if(p.x<pos.x){
			d = abs((p.x-pos.x)/(p.y-pos.y));
			pos.x-=d*speed;
			pos.y+=speed;
		}
	}
	else if(p.y<pos.y){
		if(p.x==pos.x){
			p.y-=speed;
		}
		else if(p.x>pos.x){
			d = abs((p.x-pos.x)/(p.y-pos.y));
			pos.x+=d*speed;
			pos.y-=speed;
		}
		else if(p.x<pos.x){
			d = abs((p.x-pos.x)/(p.y-pos.y));
			pos.x-=d*speed;
			pos.y-=speed;
		}
	}
	else if(p.x>pos.x){
		pos.x+=speed;
	}
	else
		pos.x-=speed;
	return 0;
}