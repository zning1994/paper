#pragma once


// Clevels �Ի���

class Clevels : public CDialog
{
	DECLARE_DYNAMIC(Clevels)

public:
	Clevels(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Clevels();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
