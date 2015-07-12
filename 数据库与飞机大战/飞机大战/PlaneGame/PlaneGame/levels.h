#pragma once


// Clevels 对话框

class Clevels : public CDialog
{
	DECLARE_DYNAMIC(Clevels)

public:
	Clevels(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Clevels();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
