#pragma once


// Clevel �Ի���

class Clevel : public CDialog
{
	DECLARE_DYNAMIC(Clevel)

public:
	Clevel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Clevel();

// �Ի�������
	enum { IDD = IDD_SETLEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int level;
	afx_msg void OnCbnSelchangeLevel();
};
