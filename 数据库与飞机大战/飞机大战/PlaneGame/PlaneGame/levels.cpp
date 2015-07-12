// levels.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "levels.h"


// Clevels 对话框

IMPLEMENT_DYNAMIC(Clevels, CDialog)

Clevels::Clevels(CWnd* pParent /*=NULL*/)
	: CDialog(Clevels::IDD, pParent)
	, level(0)
{

}

Clevels::~Clevels()
{
}

void Clevels::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, level);
	DDV_MinMaxInt(pDX, level, 1, 5);
}


BEGIN_MESSAGE_MAP(Clevels, CDialog)
END_MESSAGE_MAP()


// Clevels 消息处理程序
