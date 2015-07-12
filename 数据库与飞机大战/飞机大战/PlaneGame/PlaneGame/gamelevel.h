#pragma once


// Cgamelevel 对话框

class Cgamelevel : public CDialog
{
	DECLARE_DYNAMIC(Cgamelevel)

public:
	Cgamelevel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cgamelevel();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int level;
};
