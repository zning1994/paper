// game.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "game.h"


// Cgame �Ի���

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


// Cgame ��Ϣ�������
