// PlaneGameDoc.h : CPlaneGameDoc ��Ľӿ�
//


#pragma once


class CPlaneGameDoc : public CDocument
{
protected: // �������л�����
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

// ����
public:
	CObList bomblist1;;//����ս���ӵ�����
	CObList enemylist1,enemylist2;//�����л�����
	CObList balllist1,balllist2;//�����л��ӵ�����
	CObList balllist3;//boss���ӵ�����
	CObList explosionlist;//��ը����
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


