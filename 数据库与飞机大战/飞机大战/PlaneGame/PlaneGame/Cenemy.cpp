#include "StdAfx.h"
#include "Cenemy.h"
#include "Resource.h"
CImageList Cenemy::imgList;
Cenemy::Cenemy(int direction)
{
	this->direction=direction;
	pos.x=rand()%1000;
	if(direction==-1)//控制敌机速度方向敌机向下飞
	{
		pos.y = 0;
		index=0;
	}
	else//敌机向上飞
	{
		pos.y = 400;
		index = 1;
	}
	speed=10;
}
Cenemy::~Cenemy(void)
{
}


int Cenemy::draw(CDC* pdc)
{
	imgList.Draw(pdc,index,pos,ILD_TRANSPARENT);
	return 0;
}


int Cenemy::LoadImage(void)
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_ENEMY);
	imgList.Create(35,35,ILC_COLOR24|ILC_MASK,0,0);
	imgList.Add(&bmp,RGB(0,0,0));
	return 0;
}

int Cenemy::move(int direction)
{
	if(direction==-1){
		pos.y+=speed;
	}
	else{
		pos.y-=speed;
	}
	return 0;
}

CRect Cenemy::getRect(void)
{
	return CRect(pos,CPoint(pos.x+35,pos.y+35));
}
