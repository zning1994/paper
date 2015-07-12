#include "StdAfx.h"
#include "Cbomb.h"
#include "Resource.h"
CBitmap Cbomb::bmpDraw1;
CBitmap Cbomb::bmpDraw2;
int x,y;
Cbomb::Cbomb()
: type(0),index(0)
{
	speed=20;
}
Cbomb::Cbomb(int type,int index)
{
	this->type=type;
	speed=20;
	this->index=index;
}

Cbomb::~Cbomb(void)
{
}

int Cbomb::move()
{
	if(type%2==1){
		pos.x-=speed-type*4;
		pos.y-=speed;
	}
	else if(type%2==0&&type!=0){
		pos.x+=speed-type*3;
		pos.y-=speed;
	}
	else if(type==0)
		pos.y-=speed;
	return 0;
}
int Cbomb::LoadImage()
{
	bmpDraw1.LoadBitmap(IDB_BOMB);//装入DDB
	bmpDraw2.LoadBitmap(IDB_BOMB2);
	return 0;
}
int Cbomb::draw(CDC* pdc)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pdc);//创建DC
	CBitmap* pbmpOld;
	if(index==0){
		pbmpOld=memDC.SelectObject(&bmpDraw1);//保存原有DDB，并选入新DDB入DC
	pdc->TransparentBlt(pos.x,pos.y,10,20,&memDC,0,0,10,20,RGB(0,0,0));
	}
	else{
		pbmpOld=memDC.SelectObject(&bmpDraw2);//保存原有DDB，并选入新DDB入DC
	pdc->TransparentBlt(pos.x,pos.y,16,16,&memDC,0,0,16,16,RGB(0,0,0));
	}
	memDC.SelectObject(pbmpOld);//选入原DDB
	return 0;
}
int Cbomb::move(CPoint p)
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
CRect Cbomb::getRect(void)
{
	return CRect(pos,CPoint(pos.x+10,pos.y+20));
}
