#pragma once


// Clevel 对话框

class Clevel : public CDialog
{
	DECLARE_DYNAMIC(Clevel)

public:
	Clevel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Clevel();

// 对话框数据
	enum { IDD = IDD_SETLEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int level;
	afx_msg void OnCbnSelchangeLevel();
};
