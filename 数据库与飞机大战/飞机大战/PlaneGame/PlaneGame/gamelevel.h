#pragma once


// Cgamelevel �Ի���

class Cgamelevel : public CDialog
{
	DECLARE_DYNAMIC(Cgamelevel)

public:
	Cgamelevel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cgamelevel();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
