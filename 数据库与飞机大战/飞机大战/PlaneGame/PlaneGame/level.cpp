// level.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "level.h"


// Clevel �Ի���

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


// Clevel ��Ϣ�������

void Clevel::OnCbnSelchangeLevel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

