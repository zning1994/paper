// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"


#include <math.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView
int height,width;
IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_TIMER()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_ERASEBKGND()
	//ON_COMMAND(ID_SETLEVEL, &CPlaneGameView::OnSetlevel)
	//ON_COMMAND(32771, &CPlaneGameView::On32771)
	//ON_COMMAND(ID_32772, &CPlaneGameView::On32772)
	ON_COMMAND(ID_FILE_NEW, &CPlaneGameView::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CPlaneGameView::OnFileOpen)
	ON_COMMAND(ID_NANDU, &CPlaneGameView::OnNandu)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView()
: level(1)
, score(0)
,lifenum(100)
, isPass(0)
, isPause(0)
, bosslife(50)
, isCtrl(0)
{
	// TODO: 在此处添加构造代码

}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	this->GetClientRect(&lpRect);//取得当前的窗口大小
	//加载图片背景
	CBitmap bitmap_BackGround;
	bitmap_BackGround.LoadBitmap(IDB_BACKGROUND);
	BITMAP bimap2;//位图图像
	bitmap_BackGround.GetBitmap(&bimap2);
	CDC cdc_BackGround;//定义一个兼容的DC
	cdc_BackGround.CreateCompatibleDC(pDC);//创建DC
	CBitmap*Old=cdc_BackGround.SelectObject(&bitmap_BackGround);
	//定义一个位图对象
	//双缓冲
	CBitmap MemBitmap;
	CDC MemDC;
	//这时还不能绘图，因为没有位图的设备描述表是不能绘图的
	//只有选入了位图的设备描述表才有地方绘图，画到指定的位图上
	MemDC.CreateCompatibleDC(pDC);
	//下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图
	MemBitmap.CreateCompatibleBitmap(pDC,lpRect.right,lpRect.bottom);
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	//将位图选入到内存设备描述表
	MemDC.StretchBlt(0,0,lpRect.Width(),lpRect.Height(),&cdc_BackGround,0,0,bimap2.bmWidth,bimap2.bmHeight,SRCCOPY);
	//绘图完成后的清理
	plane.draw(&MemDC);
	//画战机的子弹
	POSITION pos,position;
	Cbomb *bombomb1;
	for(pos=pDoc->bomblist1.GetHeadPosition(); pos!=NULL;)
	{
		bombomb1=(Cbomb*)pDoc->bomblist1.GetNext(pos);
		bombomb1->draw(&MemDC);
	}
	//画敌机
	Cenemy *enemy1,*enemy2;
	for(pos=pDoc->enemylist1.GetHeadPosition(); pos!=NULL;)
	{
		enemy1=(Cenemy*)pDoc->enemylist1.GetNext(pos);
		enemy1->draw(&MemDC);
	}
	for(pos=pDoc->enemylist2.GetHeadPosition(); pos!=NULL;)
	{
		enemy2=(Cenemy*)pDoc->enemylist2.GetNext(pos);
		enemy2->draw(&MemDC);
	}
	//画敌机的子弹
	Cball *ball1,*ball2;
	for(pos=pDoc->balllist1.GetHeadPosition(); pos!=NULL;)
	{
		ball1=(Cball*)pDoc->balllist1.GetNext(pos);
		ball1->draw(&MemDC);
	}
	for(pos=pDoc->balllist2.GetHeadPosition(); pos!=NULL;)
	{
		ball2=(Cball*)pDoc->balllist2.GetNext(pos);
		ball2->draw(&MemDC);
	}
	//画爆炸
	Cexplosion *explosion;
	for(pos=pDoc->explosionlist.GetHeadPosition(); pos!=NULL;)
	{
		position=pos;
		explosion=(Cexplosion*)pDoc->explosionlist.GetNext(pos);
		if(explosion->draw(&MemDC)==0){
			pDoc->explosionlist.RemoveAt(position);
			delete explosion;
		}
	}
	//画boss和boss的子弹
	if(level>=4){
		if(boss!=NULL){
			boss->draw(&MemDC);
		}
		Cball *balllist3;
		for(pos=pDoc->balllist3.GetHeadPosition(); pos!=NULL;)
		{
			balllist3=(Cball*)pDoc->balllist3.GetNext(pos);
			balllist3->draw(&MemDC);
		}
	}
	CString t;
	wchar_t ttt[100],tt[100],tttt[100],ttttt[100];
	wsprintf(ttt,L"当前得分:%d",score);
	wsprintf(tt,L"当前生命值:%d",lifenum);
	wsprintf(tttt,L"当前关卡:%d",level);
	wsprintf(ttttt,L"当前boss生命值:%d",bosslife);
	t.SetString(tttt);
	SetBkMode(MemDC,TRANSPARENT);
	SetTextColor(MemDC,RGB(255,255,255));
	MemDC.TextOut(0,0,t);
	t.SetString(tt);
	MemDC.TextOut(0,20,tt);
	CPen pen(PS_SOLID,3,RGB(255,0,0)),*pOldPen;
	CBrush brush(RGB(255,0,0)),*pOldBrush;
	pOldBrush=(CBrush*)pDC->SelectObject(&brush);
	pOldPen=(CPen*)pDC->SelectObject(&pen);
	MemDC.Rectangle(120,20,120+lifenum,40);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	t.SetString(ttttt);
	MemDC.TextOut(0,40,t);
	MemDC.Rectangle(130,40,130+bosslife,60);
	t.SetString(ttt);
	MemDC.Rectangle(90,60,90+score,80);
	MemDC.TextOut(0,60,t);
	pDC->BitBlt(lpRect.left,lpRect.top,lpRect.right,lpRect.bottom,&MemDC,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序

//void CPlaneGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}

void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	if(AfxMessageBox(L"查看游戏说明请点击“是”，若直接进入游戏请点击“否”！",MB_YESNO)==6)
	{
		OnFileOpen();
	}
	this->GetClientRect(&lpRect);
	height=lpRect.bottom;
	width=lpRect.right;
	plane.setPosition(lpRect.right/2-50,lpRect.bottom-100);
	boss=new Cboss;
	//boss->setPosition(rand()%500,rand()%500);
	//boss->setPosition(lpRect.right/2-63,lpRect.top);
	//加载图片
	Cplane::LoadImage();
	Cbomb::LoadImage();
	Cenemy::LoadImage();
	Cball::LoadImage();
	Cexplosion::LoadImage();
	Cboss::LoadImage();
	//设置定时器
	this->SetTimer(1,100,0);
	this->SetTimer(2,60,0);
	this->SetTimer(3,50,0);
	this->SetTimer(4,500,0);
	// TODO: 在此添加专用代码和/或调用基类
}

void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->KillTimer(1);
	this->KillTimer(2);
	this->KillTimer(3);
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->enemylist1.RemoveAll();
	pDoc->enemylist2.RemoveAll();
	pDoc->bomblist1.RemoveAll();
	pDoc->balllist1.RemoveAll();
	pDoc->balllist2.RemoveAll();
	// TODO: 在此处添加消息处理程序代码
}

void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(level>=4&&boss==NULL){
		boss = new Cboss;
	}
	plane.setSpeed(level*5);
	if(GetKeyState(VK_LEFT)<0&&isPause==0)
	{
		if(plane.getPosition().x>lpRect.left)
		{
			plane.move(1);
		}
	}
	if(GetKeyState(VK_RIGHT)<0&&isPause==0)
	{
		if(plane.getPosition().x+50<lpRect.right)
		{
			plane.move(2);
		}
	}
	if(GetKeyState(VK_UP)<0&&isPause==0)
	{
		if(plane.getPosition().y>lpRect.top)
		{
			plane.move(3);
		}
	}
	if(GetKeyState(VK_DOWN)<0&&isPause==0)
	{
		if(plane.getPosition().y+100<lpRect.bottom)
		{
			plane.move(4);
		}
	}
	if(GetKeyState('Z')<0){//暂停
		isPause=1;
	}
	if(GetKeyState('S')<0){//开始
		isPause=0;
	}
	if(isPause == 0)
	{
		CPoint point =plane.getPosition();
		switch(nIDEvent)
		{
		case 1:
			{
				//战机发射子弹
				if(GetKeyState(VK_SPACE)<0)
				{
					Cbomb *bomb1 = new Cbomb();
					Cbomb *bomb2 = new Cbomb();
					bomb1->setPosition(plane.pos.x,plane.pos.y);
					bomb2->setPosition(plane.pos.x+40,plane.pos.y);
					pDoc->bomblist1.AddHead(bomb1);
					pDoc->bomblist1.AddHead(bomb2);
				}
				if(GetKeyState('X')<0)
				{
					Cbomb *bomb1 = new Cbomb(0,1);
					bomb1->setPosition(plane.pos.x+25,plane.pos.y-60);
					pDoc->bomblist1.AddHead(bomb1);
				}
				if(GetKeyState(VK_CONTROL)<0&&level>=4)
				{
					for(int i=0;i<3;i++){
						Cbomb *bomb1 = new Cbomb(i,0);
						bomb1->setPosition(plane.pos.x+20,plane.pos.y);
						pDoc->bomblist1.AddHead(bomb1);
					}
				}
				if(GetKeyState(VK_SHIFT)<0&&level==5)
				{
					for(int i=0;i<5;i++){
						Cbomb *bomb1 = new Cbomb(i,0);
						bomb1->setPosition(plane.pos.x+20,plane.pos.y);
						pDoc->bomblist1.AddHead(bomb1);
						//PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
					}
				}
				//战机子弹移动
				POSITION pos,position;
				Cbomb *bomb1;
				int i=0;
				for(pos=pDoc->bomblist1.GetHeadPosition(); pos!=NULL;)
				{
					position=pos;
					bomb1=(Cbomb*)pDoc->bomblist1.GetNext(pos);
					if((bomb1->getPosition().y)>lpRect.top){
						if(GetKeyState('X')<0){
							POSITION pos1,tpos,tpos2;
							double min=999999,d;
							Cenemy *enemy1=new Cenemy(-1);
							for(pos1=pDoc->enemylist1.GetHeadPosition();pos1!=NULL;){
								tpos=pos1;tpos2=pDoc->enemylist1.GetHeadPosition();
								enemy1=(Cenemy*)pDoc->enemylist1.GetNext(pos1);
								d=(enemy1->getPosition().x-bomb1->getPosition().x)*(enemy1->getPosition().x-bomb1->getPosition().x)+(enemy1->getPosition().y-bomb1->getPosition().y)*(enemy1->getPosition().y-bomb1->getPosition().y) ;
							    d=sqrt(d);
								if (d<min)
								{
									min=d;
									tpos2=tpos;
								}
								bomb1->move(((Cenemy*)pDoc->enemylist1.GetNext(tpos2))->getPosition());
							}
						}
						else
							bomb1->move();
					}
					else
					{
						if(pDoc->bomblist1.GetHeadPosition()==position){
							pDoc->bomblist1.RemoveHead();
 							delete bomb1;
						}
						else if(pDoc->bomblist1.GetTailPosition()==position){
							pDoc->bomblist1.RemoveTail();
							delete bomb1;
						}
						else if(pDoc->bomblist1.GetAt(position)!=NULL)
						{
							pDoc->bomblist1.RemoveAt(position);
							delete bomb1;
						}
					}

				}
				this->Invalidate(TRUE);
				break;
			}
		case 2:
			{
				//产生敌机
				POSITION pos1,position1;
				int direction1=-1,direction2=1;
				Cenemy *enemy1 = new Cenemy(direction1);
				Cenemy *enemy2 = new Cenemy(direction2);
				enemy1->setPosition(rand()%1000,lpRect.top+35);
				enemy2->setPosition(rand()%1000,lpRect.bottom-35);
				if(level<=2){
					if(pDoc->enemylist1.GetCount()<5*level&&rand()%10==level)
					{
						enemy1->setSpeed(1+2*level);
						pDoc->enemylist1.AddHead(enemy1);
					}
					if(pDoc->enemylist2.GetCount()<5*level&&rand()%10==level)
					{
						enemy2->setSpeed(1+2*level);
						pDoc->enemylist2.AddHead(enemy2);
					}
				}
				else{
					if(pDoc->enemylist1.GetCount()<10&&rand()%10==level)
					{
						enemy1->setSpeed(5);
						pDoc->enemylist1.AddHead(enemy1);
					}
					if(pDoc->enemylist2.GetCount()<10&&rand()%10==level)
					{
						enemy2->setSpeed(5);
						pDoc->enemylist2.AddHead(enemy2);
					}
				}
				//产生敌机的子弹，敌机移动
				for(pos1=pDoc->enemylist1.GetHeadPosition(); pos1!=NULL;)
				{
					position1=pos1;
					enemy1=(Cenemy*)pDoc->enemylist1.GetNext(pos1);
					if(pDoc->balllist1.GetCount()<=5){
						Cball *ball1 = new Cball();
						ball1->setPosition(enemy1->getPosition().x+20,enemy1->getPosition().y+30);
						ball1->setSpeed(level*2+30);
						pDoc->balllist1.AddHead(ball1);
					}
					if((enemy1->getPosition().y)<lpRect.bottom)
						enemy1->move(direction1);
					else
					{
						if(pDoc->enemylist1.GetHeadPosition()==position1){
							pDoc->enemylist1.RemoveHead();
							delete enemy1;
						}
						else if(pDoc->enemylist1.GetTailPosition()==position1){
							pDoc->enemylist1.RemoveTail();
							delete enemy1;
						}
						else if(pDoc->enemylist1.GetAt(position1)!=NULL)
						{
							pDoc->enemylist1.RemoveAt(position1);
							delete enemy1;
						}
					}
				}
				for(pos1=pDoc->enemylist2.GetHeadPosition(); pos1!=NULL;)
				{
					position1=pos1;
					enemy2=(Cenemy*)pDoc->enemylist2.GetNext(pos1);
					if(pDoc->balllist2.GetCount()<=5){
						Cball *ball2 = new Cball();
						ball2->setPosition(enemy2->getPosition().x+20,enemy2->getPosition().y-30);
						ball2->setSpeed(level*2+30);
						pDoc->balllist2.AddHead(ball2);
					}
					if((enemy2->getPosition().y)>lpRect.top)
						enemy2->move(direction2);
					else
					{
						if(pDoc->enemylist2.GetHeadPosition()==position1){
							pDoc->enemylist2.RemoveHead();
							delete enemy2;
						}
						else if(pDoc->enemylist2.GetTailPosition()==position1){
							pDoc->enemylist2.RemoveTail();
							delete enemy2;
						}
						else if(pDoc->enemylist2.GetAt(position1)!=NULL)
						{
							pDoc->enemylist2.RemoveAt(position1);
							delete enemy2;
						}
					}
				}
				//设置boss的子弹
				if(level==4&&boss!=NULL){
					for(int i=0;i<5;i++){
						Cball *ball3 =new Cball(i,0);
						ball3->setPosition(boss->getPosition().x+45,boss->getPosition().y+125);
						pDoc->balllist3.AddTail(ball3);
					}
				}
				if(level==5&&boss!=NULL){
					for(int i=0;i<5;i++){
						Cball *ball3 =new Cball(i,0);
						ball3->setPosition(boss->getPosition().x+10*i,boss->getPosition().y+125);
						pDoc->balllist3.AddTail(ball3);
					}
					/*for(int i=0;i<=5;i++){
						Cball *ball3 = new Cball();
						ball3->setPosition(boss->getPosition().x+)
					}*/
				}
				this->Invalidate(TRUE);
				break;
			}
		case 3:
			{
				//敌机子弹的移动
				POSITION pos2,position2;
				CPoint point;
				Cball *ball1;
				Cball *ball2;
				int direction1=-1,direction2=1;
				for(pos2=pDoc->balllist1.GetHeadPosition(); pos2!=NULL;)
				{
					position2=pos2;
					ball1=(Cball*)pDoc->balllist1.GetNext(pos2);
					if((ball1->getPosition().y)<lpRect.bottom){
						if(level>=3)
							ball1->move(plane.getPosition());
						else
							ball1->move(direction1);
						//if(point!=plane.getPosition())
						//	ball1->type=1;
					}
					else
					{
						if(pDoc->balllist1.GetHeadPosition()==position2){
							pDoc->balllist1.RemoveHead();
							delete ball1;
						}
						else if(pDoc->balllist1.GetTailPosition()==position2){
							pDoc->balllist1.RemoveTail();
							delete ball1;
						}
						else if(pDoc->balllist1.GetAt(position2)!=NULL)
						{
							pDoc->balllist1.RemoveAt(position2);
							delete ball1;
						}
					}
				}
				for(pos2=pDoc->balllist2.GetHeadPosition(); pos2!=NULL;)
				{
					position2=pos2;
					ball2=(Cball*)pDoc->balllist2.GetNext(pos2);
					if((ball2->getPosition().y)>lpRect.top){
						if(level>=3)
							ball2->move(plane.getPosition());
						else
							ball2->move(direction2);
						//ball2->move(direction2);
						//if(point!=plane.getPosition())
						//	ball2->type=1;
					}
					else
					{
						if(pDoc->balllist2.GetHeadPosition()==position2){
							pDoc->balllist2.RemoveHead();
							delete ball2;
						}
						else if(pDoc->balllist2.GetTailPosition()==position2){
							pDoc->balllist2.RemoveTail();
							delete ball2;
						}
						else if(pDoc->balllist2.GetAt(position2)!=NULL)
						{
							pDoc->balllist2.RemoveAt(position2);
							delete ball2;
						}
					}
				}
				this->Invalidate(TRUE);
				break;
			}
		case 4:{
			//boss子弹移动
			if(level>=4){
				int i=1;
				Cball *ball3;
				POSITION pos2,position2;
				int direction1=-1;
				for(pos2=pDoc->balllist3.GetHeadPosition(); pos2!=NULL;)
				{
					position2=pos2;
					ball3=(Cball*)pDoc->balllist2.GetNext(pos2);
					ball3->setSpeed(40);
					if((ball3->getPosition().y)<lpRect.bottom)
						if(level==5)
							ball3->move(plane.getPosition());
						else
							ball3->move();
					else
					{
						if(pDoc->balllist3.GetHeadPosition()==position2){
							pDoc->balllist3.RemoveHead();
							delete ball3;
						}
						else if(pDoc->balllist3.GetTailPosition()==position2){
							pDoc->balllist3.RemoveTail();
							delete ball3;
						}
						else if(pDoc->balllist3.GetAt(position2)!=NULL)
						{
							pDoc->balllist3.RemoveAt(position2);
							delete ball3;
						}
					}
				}
			}
			//boss移动
			if(level>=4&&boss!=NULL){
					boss->move();
			}
			this->Invalidate(TRUE);
			break;
		  }
		}
	}
	shot();//射击
	pass();//通关
	CView::OnTimer(nIDEvent);
}

//void CPlaneGameView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CView::OnLButtonDown(nFlags, point);
//}

//BOOL CPlaneGameView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	//return CView::OnEraseBkgnd(pDC);
//	return false;
//}

//void CPlaneGameView::OnSetlevel()
//{
//    // TODO: 在此添加命令处理程序代码
//    Clevel l;
//    l.level=level;
//    if(l.DoModal()==IDOK)
//        level=l.level;
//}
//
//void CPlaneGameView::On32771()
//{
//    // TODO: 在此添加命令处理程序代码
//    Cgamelevel l;
//    l.level=level;
//    if(l.DoModal()==IDOK)
//        level=l.level;
//}

//void CPlaneGameView::On32772()
//{
//	// TODO: 在此添加命令处理程序代码
//	isPause=1;
//	Cgame l;
//	l.level=level;
//	if(l.DoModal()==IDOK)
//		level=l.level;
//	isPause=0;
//	
//}

//重新开始
void CPlaneGameView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	pDoc->enemylist1.RemoveAll();
	pDoc->enemylist2.RemoveAll();
	pDoc->bomblist1.RemoveAll();
	pDoc->balllist1.RemoveAll();
	pDoc->balllist2.RemoveAll();
	score=0;
	lifenum=100;
	bosslife=50;
	isPause=0;
	isPass=0;
	level=1;
	SetTimer(1,100,NULL);//战机子弹定时器
	SetTimer(2,60,NULL);//敌机产生定时器
	SetTimer(3,50,NULL);//敌机子弹定时器
	SetTimer(4,500,NULL);//boss移动定时器
}
//游戏说明
void CPlaneGameView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	isPause=1;
	AfxMessageBox(L"方向键控制战机方向，空格键射击，Z键暂停，S键开始,鼠标控制战机位置，Ctrl键发射3排分散子弹，Shift键发射5排分散子弹。第一关初始生命值为100每增加一关生命值加100,消灭一个敌机加1分，如果分数达到100分即可进入下一关。随着关卡增多，敌机速度和数量均增加，在第4、5关由一个大boss，通过5关即可通关！");
	isPause=0;
}
//设置难度
void CPlaneGameView::OnNandu()
{
	// TODO: 在此添加命令处理程序代码
	isPause=1;
	Clevels l;
	l.level=level;
	if(l.DoModal()==IDOK)
		level=l.level;
	lifenum=100*level;
	isPause=0;
}
//射击
int CPlaneGameView::shot(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 1;
	if(isPause == 0){
		CRect tempRect;
		//战机子弹打中向下走的敌机
		POSITION pos,position,pos1,position1;
		Cenemy *enemy1,*enemy2;
		Cbomb *bomb1;
		for(pos=pDoc->enemylist1.GetHeadPosition();pos!=NULL;){
			position=pos;
			enemy1=(Cenemy*)pDoc->enemylist1.GetNext(pos);
			CRect eneRect = enemy1->getRect();
			for(pos1=pDoc->bomblist1.GetHeadPosition();pos1!=NULL;){
				position1=pos1;
				bomb1=(Cbomb*)pDoc->bomblist1.GetNext(pos1);
				CRect bomRect = bomb1->getRect();
				//判断两个矩形区域是否有交接
				if(tempRect.IntersectRect(&bomRect,eneRect))
				{
					//将爆炸对象添加到爆炸链表中
					Cexplosion *explosion=new Cexplosion((enemy1->getPosition().x+17),(enemy1->getPosition().y+17));
					pDoc->explosionlist.AddHead(explosion);
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
					//删除子弹
					if(pDoc->bomblist1.GetHeadPosition()==position){
						pDoc->bomblist1.RemoveHead();
						delete bomb1;
					}
					else if(pDoc->bomblist1.GetTailPosition()==position){
						pDoc->bomblist1.RemoveTail();
						delete bomb1;
					}
					else if(pDoc->bomblist1.GetAt(position1)!=NULL){
						pDoc->bomblist1.RemoveAt(position1);
						delete  bomb1;
					}
					//删除敌机
					if(pDoc->enemylist1.GetHeadPosition()==position1){
						pDoc->enemylist1.RemoveHead();
						delete enemy1;
					}
					else if(pDoc->enemylist1.GetTailPosition()==position1){
						pDoc->enemylist1.RemoveTail();
						delete enemy1;
					}
					else if(pDoc->enemylist1.GetAt(position)!=NULL){
						pDoc->enemylist1.RemoveAt(position);
						delete  enemy1;
					}
					score++;
					lifenum++;
					break;
				}

			}
		}
		//战机子弹打中向上走的敌机
		for(pos=pDoc->enemylist2.GetHeadPosition();pos!=NULL;){
			position=pos;
			enemy2=(Cenemy*)pDoc->enemylist2.GetNext(pos);
			CRect eneRect = enemy2->getRect();
			for(pos1=pDoc->bomblist1.GetHeadPosition();pos1!=NULL;){
				position1=pos1;
				bomb1=(Cbomb*)pDoc->bomblist1.GetNext(pos1);
				CRect bomRect = bomb1->getRect();
				//判断两个矩形区域是否有交接
				if(tempRect.IntersectRect(&bomRect,eneRect))
				{
					//将爆炸对象添加到爆炸链表中
					Cexplosion *explosion=new Cexplosion((enemy2->getPosition().x+17),(enemy2->getPosition().y+17));
					pDoc->explosionlist.AddHead(explosion);
					PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
					//删除子弹
					if(pDoc->bomblist1.GetHeadPosition()==position){
						pDoc->bomblist1.RemoveHead();
						delete bomb1;
					}
					else if(pDoc->bomblist1.GetTailPosition()==position){
						pDoc->bomblist1.RemoveTail();
						delete bomb1;
					}
					else if(pDoc->bomblist1.GetAt(position1)!=NULL){
						pDoc->bomblist1.RemoveAt(position1);
						delete  bomb1;
					}
					//删除敌机
					if(pDoc->enemylist2.GetHeadPosition()==position1){
						pDoc->enemylist2.RemoveHead();
						delete enemy2;
					}
					else if(pDoc->enemylist2.GetTailPosition()==position1){
						pDoc->enemylist2.RemoveTail();
						delete enemy2;
					}
					else if(pDoc->enemylist2.GetAt(position)!=NULL){
						pDoc->enemylist2.RemoveAt(position);
						delete  enemy2;
					}
					score++;
					lifenum++;
					break;
				}
			}
		}
		Cball *balllist1,*balllist2,*ball3;
		//敌机向下的子弹打中战机
		for(pos=pDoc->balllist1.GetHeadPosition();pos!=NULL;){
			position=pos;
			balllist1=(Cball*)pDoc->balllist1.GetNext(pos);
			CRect ballRect = balllist1->getRect();
			CRect planeRect = plane.getRect();
			//判断两个矩形区域是否有交接
			if(tempRect.IntersectRect(&ballRect,planeRect))
			{
				if(position==pDoc->balllist1.GetHeadPosition()){
					pDoc->balllist1.RemoveHead();
					delete balllist1;
				}
				else if(position==pDoc->balllist1.GetTailPosition()){
					pDoc->balllist1.RemoveTail();
					delete balllist1;
				}
				else if(pDoc->balllist1.GetAt(position)!=NULL)
				{
					pDoc->balllist1.RemoveAt(position);
					delete  balllist1;
				}
				lifenum--;
				break;
			}
		}
		//敌机向上的子弹打中战机
		for(pos=pDoc->balllist2.GetHeadPosition();pos!=NULL;){
			position=pos;
			balllist2=(Cball*)pDoc->balllist2.GetNext(pos);
			CRect ballRect = balllist2->getRect();
			CRect planeRect = plane.getRect();
			//判断两个矩形区域是否有交接
			if(tempRect.IntersectRect(&ballRect,planeRect))
			{
				if(position==pDoc->balllist2.GetHeadPosition()){
					pDoc->balllist2.RemoveHead();
					delete balllist2;
				}
				else if(position==pDoc->balllist2.GetTailPosition()){
					pDoc->balllist2.RemoveTail();
					delete balllist2;
				}
				else if(pDoc->balllist2.GetAt(position)!=NULL){
					pDoc->balllist2.RemoveAt(position);
					delete  balllist2;
				}
				lifenum--;
				break;
			}
		}
		//战机与向下走的敌机相撞
		for(pos=pDoc->enemylist1.GetHeadPosition();pos!=NULL;){
			position=pos;
			enemy1=(Cenemy*)pDoc->enemylist1.GetNext(pos);
			CRect eneRect = enemy1->getRect();
			CRect planeRect = plane.getRect();
			//判断两个矩形区域是否有交接
			if(tempRect.IntersectRect(&eneRect,planeRect))
			{
				////将爆炸对象添加到爆炸链表中
				Cexplosion *explosion=new Cexplosion((enemy1->getPosition().x+17),(enemy1->getPosition().y+17));
				pDoc->explosionlist.AddHead(explosion);
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
				if(position==pDoc->enemylist1.GetHeadPosition()){
					pDoc->enemylist1.RemoveHead();
					delete enemy1;
				}
				else if(position==pDoc->enemylist1.GetTailPosition()){
					pDoc->enemylist1.RemoveTail();
					delete enemy1;
				}
				else if(pDoc->enemylist1.GetAt(position)!=NULL)
				{
					pDoc->enemylist1.RemoveAt(position);
					delete  enemy1;
				}
				lifenum=lifenum-5;
				break;
			}
		}
		//战机与向上走的敌机相撞
		for(pos=pDoc->enemylist2.GetHeadPosition();pos!=NULL;){
			position=pos;
			enemy2=(Cenemy*)pDoc->enemylist2.GetNext(pos);
			CRect eneRect = enemy2->getRect();
			CRect planeRect = plane.getRect();
			//判断两个矩形区域是否有交接
			if(tempRect.IntersectRect(&eneRect,planeRect))
			{
				////将爆炸对象添加到爆炸链表中
				Cexplosion *explosion=new Cexplosion((enemy2->getPosition().x+17),(enemy2->getPosition().y+17));
				pDoc->explosionlist.AddHead(explosion);
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
				//删除敌机
				if(position==pDoc->enemylist2.GetHeadPosition()){
					pDoc->enemylist2.RemoveHead();
					delete enemy2;
				}
				else if(position==pDoc->enemylist2.GetTailPosition()){
					pDoc->enemylist2.RemoveTail();
					delete enemy2;
				}
				else if(pDoc->enemylist2.GetAt(position)!=NULL)
				{
					pDoc->enemylist2.RemoveAt(position);
					delete  enemy2;
				}
				lifenum=lifenum-5;
				break;
			}
		}
		if(level>=4){
			//boss的子弹打中战机
			for(pos=pDoc->balllist3.GetHeadPosition();pos!=NULL;){
				position=pos;
				ball3=(Cball*)pDoc->balllist3.GetNext(pos);
				CRect ballRect = ball3->getRect();
				CRect planeRect = plane.getRect();
				//判断两个矩形区域是否有交接
				if(tempRect.IntersectRect(&ballRect,planeRect))
				{
					//删除boss子弹
					if(position==pDoc->balllist3.GetHeadPosition()){
						pDoc->balllist3.RemoveHead();
						delete ball3;
					}
					else if(position==pDoc->balllist3.GetTailPosition()){
						pDoc->balllist3.RemoveTail();
						delete ball3;
					}
					else if(pDoc->balllist3.GetAt(position)!=NULL){
						pDoc->balllist3.RemoveAt(position);
						delete  ball3;
					}
					lifenum--;
					break;
				}
			}
			//boss与战机相撞
			if(boss!=NULL){
				CRect bossRect = boss->getRect();
				CRect planeRect = plane.getRect();
				if(tempRect.IntersectRect(&bossRect,planeRect))
				{
					lifenum=lifenum-10;
					//bosslife=bosslife-5;
				}
				//战机子弹打中boss
				for(pos1=pDoc->bomblist1.GetHeadPosition();pos1!=NULL;){
					position1=pos1;
					bomb1=(Cbomb*)pDoc->bomblist1.GetNext(pos1);
					CRect bomRect = bomb1->getRect();
					//判断两个矩形区域是否有交接
					if(tempRect.IntersectRect(&bomRect,bossRect))
					{
						//删除子弹
						if(pDoc->bomblist1.GetHeadPosition()==position){
							pDoc->bomblist1.RemoveHead();
							delete bomb1;
						}
						else if(pDoc->bomblist1.GetTailPosition()==position){
							pDoc->bomblist1.RemoveTail();
							delete bomb1;
						}
						else if(pDoc->bomblist1.GetAt(position1)!=NULL){
							pDoc->bomblist1.RemoveAt(position1);
							delete  bomb1;
						}
						score++;
						lifenum++;
						bosslife--;
						break;
					}
				}
			}
		}
	}
	if(bosslife<=0&&boss!=NULL){
		//将爆炸对象添加到爆炸链表中
		Cexplosion *explosion=new Cexplosion((boss->getPosition().x+17),(boss->getPosition().y+17));
		pDoc->explosionlist.AddHead(explosion);
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE |SND_ASYNC);
		delete boss;
		boss=NULL;
		bosslife=0;
	}
	return 0;
}

int CPlaneGameView::pass(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 1;
	//过关
	if(score>=100&&isPause==0){
		isPass = 1; 
	}
	if(isPass==1){
		if(level>=5){
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			KillTimer(4);
			if(AfxMessageBox(L"恭喜你已通关！是否重新开始？",MB_YESNO)==6)
			{
				pDoc->enemylist1.RemoveAll();
				pDoc->enemylist2.RemoveAll();
				pDoc->bomblist1.RemoveAll();
				pDoc->balllist1.RemoveAll();
				pDoc->balllist2.RemoveAll();
				pDoc->balllist3.RemoveAll();
				score=0;
				lifenum=100;
				bosslife=30;
				isPause=0;
				isPass=0;
				level=1;
				boss=new Cboss;
				SetTimer(1,100,NULL);
				SetTimer(2,60,NULL);
				SetTimer(3,50,NULL);
				SetTimer(4,500,NULL);
			}
			else 
				exit(1);
		}
		else if(level<5)
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			KillTimer(4);
			if(AfxMessageBox(L"恭喜你已过关！是否进入下一关？",MB_YESNO)==6)
			{
				pDoc->enemylist1.RemoveAll();
				pDoc->enemylist2.RemoveAll();
				pDoc->bomblist1.RemoveAll();
				pDoc->balllist1.RemoveAll();
				pDoc->balllist2.RemoveAll();
				pDoc->balllist3.RemoveAll();
				score=0;
				level++;
				lifenum=100*level;
				bosslife=50;
				isPause=0;
				isPass=0;
				boss=new Cboss;
				SetTimer(1,100,NULL);
				SetTimer(2,60,NULL);
				SetTimer(3,50,NULL);
				SetTimer(4,500,NULL);
			}
			else 
				exit(1);
		}
	}
	if(lifenum<=0&&isPass==0&&isPause==0){
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		KillTimer(4);
		if(AfxMessageBox(L"GAME OVER！是否重新开始？",MB_YESNO)==6)
		{
			pDoc->enemylist1.RemoveAll();
			pDoc->enemylist2.RemoveAll();
			pDoc->bomblist1.RemoveAll();
			pDoc->balllist1.RemoveAll();
			pDoc->balllist2.RemoveAll();
			pDoc->balllist3.RemoveAll();
			score=0;
			lifenum=100;
			bosslife=50;
			isPause=0;
			isPass=0;
			level=1;
			SetTimer(1,100,NULL);
			SetTimer(2,60,NULL);
			SetTimer(3,50,NULL);
			SetTimer(4,500,NULL);
		}
		else 
			exit(1);
	}
	return 0;
}

void CPlaneGameView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->GetClientRect(&lpRect);
	if(point.y>=lpRect.top&&point.y<=lpRect.bottom-60&&point.x>=lpRect.left&&point.x<=lpRect.right-50)
		plane.setPosition(point.x,point.y);
	CView::OnMouseMove(nFlags, point);
}

BOOL CPlaneGameView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return CView::OnEraseBkgnd(pDC);
	return FALSE;
}
