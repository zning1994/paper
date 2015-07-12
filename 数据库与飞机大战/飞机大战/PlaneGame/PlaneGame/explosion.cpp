// explosion.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "explosion.h"


// Cexplosion
CImageList Cexplosion::imgList;
Cexplosion::Cexplosion()
: index(0)
{
}
Cexplosion::Cexplosion(int x,int y)
: index(0)
{
	pos.x=x;
	pos.y=y;
}

Cexplosion::~Cexplosion()
{
}


// Cexplosion 成员函数

int Cexplosion::draw(CDC* pdc)
{
	if(index>=8)
	{
		index=0;
		return 0;
	}
	imgList.Draw(pdc,index,pos,ILD_TRANSPARENT);
	index++;
	return 1;
}

int Cexplosion::LoadImage(void)
{
	CBitmap bmp;
	if(!bmp.LoadBitmap(IDB_EXPLOSION))
		return 0;
	if(!imgList.Create(66,66,ILC_COLOR24|ILC_MASK,0,0))
		return 0;
	imgList.Add(&bmp,RGB(0,0,0));
	return 1;
	return 0;
}
