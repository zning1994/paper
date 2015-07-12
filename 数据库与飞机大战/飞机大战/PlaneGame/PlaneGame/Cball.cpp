#include "StdAfx.h"
#include "Cball.h"
#include "Resource.h"
CBitmap Cball::bmpDraw;
Cball::Cball()
{
	speed =40;
	index=0;
}
Cball::Cball(int index,int type)
{
	speed =40;
	this->index=index;
	this->type=type;
}
Cball::~Cball(void)
{
}
int Cball::move(int direction)
{
	if(direction==-1){
		pos.y+=speed;
	}
	else{
		pos.y-=speed;
	}
	return 0;
}
int Cball::move()
{
	if(index%2==1)
	{
		pos.x-=speed-index*8;
		pos.y+=speed;
	}
	else if(index%2==0&&index!=0)
	{
		pos.x+=speed-index*7;
		pos.y+=speed;
	}
	else if(index==0)
		pos.y+=speed;
	return 0;
}
int Cball::LoadImage()
{
	bmpDraw.LoadBitmap(IDB_BALL);//装入DDB
	return 0;
}
int Cball::draw(CDC* pdc)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pdc);//创建DC
	CBitmap* pbmpOld=memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pdc->TransparentBlt(pos.x,pos.y,8,8,&memDC,0,0,8,8,RGB(0,0,0));
	memDC.SelectObject(pbmpOld);//选入原DDB
	return 0;
}

CRect Cball::getRect(void)
{
	return CRect(pos,CPoint(pos.x+8,pos.y+8));
}
int Cball::move(CPoint p)
{
	/*double d;
	if(p.x>pos.x&&p.y>pos.y){
		pos.x+=speed;
		pos.y+=speed;
	}
	if(p.x>pos.x&&p.y<pos.y){
		pos.x+=speed;
		pos.y-=speed;
	}
	if(p.x<pos.x&&p.y>pos.y){
		pos.x-=speed;
		pos.y+=speed;
	}
	if(p.x<pos.x&&p.y<pos.y){
		pos.x-=speed;
		pos.y-=speed;
	}
	type=0;*/
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
	type=0;
	return 0;
}