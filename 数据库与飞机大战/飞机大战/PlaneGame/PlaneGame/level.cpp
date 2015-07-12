// level.cpp : 实现文件
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "level.h"


// Clevel 对话框

IMPLEMENT_DYNAMIC(Clevel, CDialog)

Clevel::Clevel(CWnd* pParent /*=NULL*/)
	: CDialog(Clevel::IDD, pParent)
	, level(1)
{

}

Clevel::~Clevel()
{
}

void Clevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_LEVEL, level);
	//DDV_MinMaxInt(pDX, level, 1, 5);
}


BEGIN_MESSAGE_MAP(Clevel, CDialog)
	//ON_CBN_SELCHANGE(IDC_LEVEL, &Clevel::OnCbnSelchangeLevel)
END_MESSAGE_MAP()


// Clevel 消息处理程序

void Clevel::OnCbnSelchangeLevel()
{
	// TODO: 在此添加控件通知处理程序代码
}

