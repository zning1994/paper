// gamelevel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "gamelevel.h"


// Cgamelevel �Ի���

IMPLEMENT_DYNAMIC(Cgamelevel, CDialog)

Cgamelevel::Cgamelevel(CWnd* pParent /*=NULL*/)
	: CDialog(Cgamelevel::IDD, pParent)
	, level(0)
{

}

Cgamelevel::~Cgamelevel()
{
}

void Cgamelevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, level);
	//DDV_MinMaxInt(pDX, level, 1, 5);
}


BEGIN_MESSAGE_MAP(Cgamelevel, CDialog)
END_MESSAGE_MAP()


// Cgamelevel ��Ϣ�������
