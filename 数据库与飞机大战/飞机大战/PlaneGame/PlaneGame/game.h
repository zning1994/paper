#pragma once


// Cgame �Ի���

class Cgame : public CDialog
{
	DECLARE_DYNAMIC(Cgame)

public:
	Cgame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cgame();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
