// game.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "game.h"


// Cgame 对话框

IMPLEMENT_DYNAMIC(Cgame, CDialog)

Cgame::Cgame(CWnd* pParent /*=NULL*/)
	: CDialog(Cgame::IDD, pParent)
	, level(0)
{

}

Cgame::~Cgame()
{
}

void Cgame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, level);
	DDV_MinMaxInt(pDX, level, 1, 5);
}


BEGIN_MESSAGE_MAP(Cgame, CDialog)
END_MESSAGE_MAP()


// Cgame 消息处理程序
