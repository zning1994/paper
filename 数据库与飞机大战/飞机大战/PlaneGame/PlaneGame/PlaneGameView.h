// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once
#include "Cplane.h"
#include "Cbomb.h"
#include "Cenemy.h"
#include "Cball.h"
//#include "level.h"
//#include "gamelevel.h"
//#include "game.h"
#include "explosion.h"
#include "resource.h"
#include "Cboss.h"
#include "levels.h"
class CPlaneGameView : public CView
{
protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

	// ����
public:
	CPlaneGameDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	Cplane plane;
	CRect lpRect;
	Cboss *boss;
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void OnSetlevel();
	int level;
	//afx_msg void On32771();
	//afx_msg void On32772();
	int score;//�÷�
	int lifenum;//����ֵ
	int isPass;//����
	int isPause;//��ͣ
	int bosslife;
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnNandu();
	int shot(void);
	int pass(void);
	int isCtrl;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
{ return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

