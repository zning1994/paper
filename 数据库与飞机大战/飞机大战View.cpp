// 飞机大战View.cpp : C飞机大战View 类的实现
//

#include "stdafx.h"
#include "飞机大战.h"

#include "飞机大战Doc.h"
#include "飞机大战View.h"
#include "string.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int a=0;
int n=100;
int m=0;
int number=1;
int DaoJu_Waite=0;//发射道具
// C飞机大战View

IMPLEMENT_DYNCREATE(C飞机大战View, CView)

BEGIN_MESSAGE_MAP(C飞机大战View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C飞机大战View 构造/析构

C飞机大战View::C飞机大战View()
{
	// TODO: 在此处添加构造代码
	//PlaySound(TEXT("../sound/nizhan.wav"),NULL,SND_FILENAME | SND_ASYNC);
	//加载图片
	myplane.LoadImage();
	enemy.LoadImage();
	bomb.LoadImage();
	ball.LoadImage();
	explosion.LoadImage();
	daoju.LoadImage();
	//text.Draw();
}

C飞机大战View::~C飞机大战View()
{
}

BOOL C飞机大战View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C飞机大战View 绘制

void C飞机大战View::OnDraw(CDC* pDC)
{
	
	
	C飞机大战Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	//双缓冲

	 CRect rc; 
     CDC MecDC; 
     GetClientRect(&rc); 
     CBitmap bmp; //内存中承载临时图象的位图 

     MecDC.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC 
 	 //bmp.CreateCompatibleBitmap(pDC,rc.right,rc.bottom); //创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
	 bmp.LoadBitmap(IDB_SKY);//插入背景图片
     CBitmap *pOldBit=MecDC.SelectObject(&bmp); //该函数选择一对象到指定的设备上下文环境中，该新对象替换先前的相同类型的对象。
   
	// MecDC.FillSolidRect(0,0,rc.right,rc.bottom,RGB(100,149,237));  //按原来背景填充客户区，不然会是黑色


	/******************战机*********************/
	 if(n>0)
	 {
		myplane.Draw(&MecDC,TRUE);
	 }
	
	//*****************输出敌机****************/
      if(m==0)
	  {  
		  number=10;//rand()%10+1;
	  }else if(m==30)
	  {
		  number=25;//rand()%25+1;
	  }else if(m==50)
	  {
		  number=35;//rand()%45+1;
	  }else if(m==100)
	  {
          number=45;//rand()%75+1;
	  }else if(m==150)
	  {
          number=65;//rand()%100+1;
	  }


	  
	 if(oblenemy.GetCount()<number)//生成敌机链表
	 {
	 
		 int x=rand()%970;
		 int n=rand()%2?1:-1;//随机的产生上下两个方向
		 CEnemy* pEnemy=new CEnemy(x,n==1?0:600,n);//生成敌机
		 oblenemy.AddHead(pEnemy);

	 }
	 POSITION pos=oblenemy.GetHeadPosition();
	 while(pos!=0)//遍历敌机，碰到越界的就将其删除
	 {
		 POSITION dpos=pos;
		 CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(pos);//传给下一个地址
		 if(pEnemy->GetPoint().y>600||pEnemy->GetPoint().y<0)//删除敌机
		 {
			 oblenemy.RemoveAt(dpos);
			 delete pEnemy;
			 continue;
		 }
		  pEnemy->Draw(&MecDC,TRUE);//画图
	 }




   //**************敌机被击中  碰撞检测//绘制战机子弹*******************/


   if(n>0&&obl.IsEmpty()==0)//isempty 不是空的时候返回0，判断导弹是否为空o存在战机
{
	
		//第一个导弹第一个位置
		CBomb* pBomb=(CBomb*)obl.GetHead();
        POSITION pos=obl.GetHeadPosition();

		bool isFired =false;//是否可以被击中
		while(pos!=NULL)//遍历导弹
		{
		//第一个导弹发射以后，画导弹，自动赋值给下一个导弹
		    POSITION dpos=pos;
			pBomb=(CBomb*)obl.GetNext(pos);
			/**************************矩形区域********************************/
			//导弹的矩形区域
			CRect One = CRect(pBomb->GetPoint().x,pBomb->GetPoint().y,(pBomb->GetPoint().x)+10,(pBomb->GetPoint().y)+20);
			
			
			if(oblenemy.IsEmpty()==0)//判断敌机是否为空
            {
				POSITION posD=oblenemy.GetHeadPosition();
				
				CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
				while(posD!=NULL)//遍历敌机
				{
					POSITION dposD=posD;
					CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posD);

				/**************************矩形区域********************************/
				//	敌机的矩形区域
				CRect Two = CRect(pEnemy->GetPoint().x,pEnemy->GetPoint().y,(pEnemy->GetPoint().x) +35,(pEnemy->GetPoint().y)+35);
				CRect Inter;
				if(Inter.IntersectRect(One,Two))//相撞
				{
				    PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
				    m++;
					 //画爆炸图片
					CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
					newplosion->Draw(&MecDC,TRUE);	
					//删除敌机
					oblenemy.RemoveAt(dposD);
					delete pEnemy;
					//删除爆炸图片
					delete newplosion;
					isFired = true;//确定被击中
					break;
				}
				}
				
			}
			if(!isFired)
			pBomb->Draw(&MecDC,TRUE);//画导弹
			else
			{
				//删除炸弹
				obl.RemoveAt(dpos);
				delete pBomb;
			}
			
				
		}
}

//**********************敌机与战机相撞*****************/
   if(n>0&&oblenemy.IsEmpty()==0)
   {
       POSITION posD=oblenemy.GetHeadPosition();
				
	   CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
		while(posD!=NULL)//遍历敌机
			{
					POSITION dposD=posD;
					CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posD);

				/**************************矩形区域********************************/
				//	敌机的矩形区域该对象或结构包含了一个源矩形
				CRect Three = CRect(pEnemy->GetPoint().x,pEnemy->GetPoint().y,(pEnemy->GetPoint().x) +35,(pEnemy->GetPoint().y)+35);
				//战机的矩形新区域该对象或结构包含了一个源矩形
				CRect Four = CRect(myplane.GetPoint().x,myplane.GetPoint().y,myplane.GetPoint().x+50,myplane.GetPoint().y+60);
				CRect Inter2;//此函数使Inter2等于两个现有矩形的交。即是两个源矩形的重合部分。
				if(Inter2.IntersectRect(Three,Four))//相撞，如果交Inter2不为空，则返回非零值；否则，如果交为空则返回0。
				{
				    PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
				    m++;
					 //画爆炸图片
					CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
					newplosion->Draw(&MecDC,TRUE);	
					//删除敌机
					oblenemy.RemoveAt(dposD);
					delete pEnemy;
					//删除爆炸图片
					delete newplosion;
	                 n--;
					break;
				}
		  }
   }

			
//*********************绘制敌机的子弹，炸掉战机**********/
  
 //便利符合条件的敌机,存储子弹
	 POSITION pos3=oblenemy.GetHeadPosition();
	 
	 bool isFired =false;//是否可以被击中
	   while(pos3!=NULL)
     {
		 CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(pos3);
	  
		int find=0;//用于判断是否符合发射子弹的条件
		if(myplane.GetPoint().x>=pEnemy->GetPoint().x-50&&myplane.GetPoint().x<pEnemy->GetPoint().x+35)
   
	     {
			 if((pEnemy->GetMontion()==1&&myplane.GetPoint().y>pEnemy->GetPoint().y)||(pEnemy->GetMontion()==-1&&myplane.GetPoint().y<pEnemy->GetPoint().y))
			 {
				 find=1;//符合条件
				 if(pEnemy->m_nWait%20==0)//延时发射
				 {
		            CBall *pBall=new CBall(pEnemy->GetPoint().x+17,pEnemy->GetPoint().y,pEnemy->GetMontion());
	                oblball.AddHead(pBall);
				 }
				 pEnemy->m_nWait++;//存储子弹，延时20个刷新时间
			 }
        }
	   if(find==0)
			pEnemy->m_nWait=0;//不符合发射条件的时候就初始位置置位0

     }   
//准备发射子弹
	   if(n>0&&oblball.IsEmpty()==0)//isempty 不是空的时候返回0，战机存在才会发子弹
     {
		//第一个子弹第一个位置
		 CBall* pBall=(CBall*)oblball.GetHead();
        POSITION pos=oblball.GetHeadPosition();
        
		while(pos!=NULL)//遍历子弹
		{
			POSITION dpos=pos;
		  //第一个子弹发射以后，画子弹，自动赋值给下一个子弹位置
			CBall* pBall=(CBall*)oblball.GetNext(pos);
			//子弹的越界删除
			if(pBall->GetPoint().y>600||pBall->GetPoint().y<0)//删除敌机
		       {
			     oblball.RemoveAt(dpos);
			     delete pBall;
			     continue;
		       }
			//没有越界子弹爆炸
			if(pBall->GetPoint().x>=myplane.GetPoint().x-10&&pBall->GetPoint().x<=myplane.GetPoint().x+50)
			if(pBall->GetPoint().y>=myplane.GetPoint().y-10&&pBall->GetPoint().y<=myplane.GetPoint().y+60)
			{
				if(n>0)
				{			
					 PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
					CExplosion* newplosion=new CExplosion(myplane.GetPoint().x,myplane.GetPoint().y);
					newplosion->Draw(&MecDC,TRUE);								
					delete newplosion;

					oblball.RemoveAt(dpos);
					delete pBall;
					n--;//判断战机生命值
					
					isFired = true;
					break;//一个子弹只打一个飞机
				}
				
			}
            
			if(!isFired)
			pBall->Draw(&MecDC,TRUE);
			
			
		}
     }
	   
	   
//*********************道具**********************/
	 DaoJu_Waite++;//控制出精灵的时间
	 if(DaoJu_Waite==100)
	 {
		 DaoJu_Waite=0;
		 int x=rand()%970;
		 int y=rand()%600;
		 CDaoju* pDaoju=new CDaoju(x,y);
		 obldaoju.AddHead(pDaoju);
	 }
	 POSITION posW=obldaoju.GetHeadPosition();
	 while(posW!=0)//遍历敌机，碰到越界的就将其删除
	 {
		 POSITION dposW=posW;
		 CDaoju* pDaoju=(CDaoju*)obldaoju.GetNext(posW);//传给下一个地址
		 if(pDaoju->GetPoint().y>600)//删除敌机
		 {
			 obldaoju.RemoveAt(dposW);
			 delete pDaoju;
			 continue;
		 }
		 //	道具的矩形区域该对象或结构包含了一个源矩形
		 CRect DAOJU = CRect(pDaoju->GetPoint().x,pDaoju->GetPoint().y,(pDaoju->GetPoint().x) +29,(pDaoju->GetPoint().y)+28);
		 //战机的矩形新区域该对象或结构包含了一个源矩形
		 CRect ZHANJI = CRect(myplane.GetPoint().x,myplane.GetPoint().y,myplane.GetPoint().x+50,myplane.GetPoint().y+60);
		 CRect Inter3;//此函数使Inter2等于两个现有矩形的交。即是两个源矩形的重合部分。
		 if(Inter3.IntersectRect(DAOJU,ZHANJI))
		 {
			 n+=5;
			 obldaoju.RemoveAt(dposW);
			 delete pDaoju;
			 continue;
		 }
		  pDaoju->Draw(&MecDC,TRUE);//画图
	 }

	 /***************************大招**********************/
	 if(GetKey('S'))
	 {
		 if(m>80&&n>50)
		 {
			 if(oblenemy.IsEmpty()==0)
			 {
                  POSITION posS=oblenemy.GetHeadPosition();
				
				  CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
				  while(posS!=NULL)//遍历敌机
					{
					  POSITION dposS=posS;
					  CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posS);
					  if(pEnemy->GetPoint().x>0&&pEnemy->GetPoint().x<970)
						  if(pEnemy->GetPoint().y>0&&pEnemy->GetPoint().y<600)
						  {
							  PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
							  m++;
							 //画爆炸图片
							  CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
							  newplosion->Draw(&MecDC,TRUE);	
							//删除敌机
							  oblenemy.RemoveAt(dposS);
						      delete pEnemy;
					        //删除爆炸图片
					          delete newplosion;
							 

						  }

					}
				   n-=10;
			 }
		 }
	 }


	   /*******************输出文字*************************/
	 	
		CFont*  m_pFont=new CFont;
		LOGFONT lf; 
        MecDC.SelectObject(*m_pFont); 
		
		MecDC.SetTextColor(RGB(255,255,0));//颜色
		MecDC.SetBkMode(TRANSPARENT);//透明
		CString s,sm,sgq;
		//int n;
		s.Format(TEXT("消灭敌机的数量： %d"),m);
		sm.Format(TEXT("战机的生命值为：%d"),n);

		MecDC.TextOutW(10,10,s);
		MecDC.TextOutW(10,30,sm);
		MecDC.TextOutW(10,50,_T("您所在的关卡："));
		if(m<30)
		{ 
            MecDC.TextOutW(110,50,_T("第一关"));
		}else if(m<50&&m>=30 )
		{
			MecDC.TextOutW(110,50,_T("第二关"));
		}else  if(m<100&&m>=50)
		{
			MecDC.TextOutW(110,50,_T("第三关"));
		}else if(m>100&&m<=150)
		{
            MecDC.TextOutW(110,50,_T("第四关"));
		}	
			if(m>150&&m<300)
		{
			MecDC.TextOutW(110,50,_T("迎接无敌状态吧！！！！"));			
		}else if(m>=300&&n!=0)
		{
            
            memset(&lf, 0, sizeof(LOGFONT));		
			lf.lfHeight  = 80;  
			lf.lfWeight  = 20;  
			m_pFont->CreateFontIndirect(&lf); //创建字体
			MecDC.SelectObject(*m_pFont); //设为默认的字体
			MecDC.TextOutW(100,300,_T("恭喜你，通关了！！！"));
            KillTimer(1);
			delete m_pFont;


		}
		if(n==0)
		{
			memset(&lf, 0, sizeof(LOGFONT));		
			lf.lfHeight  = 80;  
			lf.lfWeight  = 20;  
			m_pFont->CreateFontIndirect(&lf); //创建字体
			MecDC.SelectObject(*m_pFont); //设为默认的字体
			MecDC.TextOutW(300,300,_T("游戏结束！！！"));
			delete m_pFont;
			//可以改成图片，但是没有合适的
			 /*CImageList images;
			 CBitmap bmp1;
			 bmp1.LoadBitmap(IDB_GAMEOVER);
			 images.Create(220,220,ILC_COLOR24,0,1);
			 images.Add(&bmp1,RGB(0,0,0));
			 images.Draw(&MecDC,0,CPoint(300,160),ILD_TRANSPARENT);*/
		}



	//双缓冲
	pDC->BitBlt(0,0,rc.right,rc.bottom,&MecDC,0,0,SRCCOPY);////将内存DC上的图象拷贝到前台 

     //绘图完成后的清理
    MecDC.DeleteDC();//删除DC

    bmp.DeleteObject(); //删除位图
	SetTimer(1,40,NULL);
	//通关
	if(m>=300&&n!=0)
		KillTimer(1);

	
}


// C飞机大战View 打印

BOOL C飞机大战View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C飞机大战View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void C飞机大战View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// C飞机大战View 诊断

#ifdef _DEBUG
void C飞机大战View::AssertValid() const
{
	CView::AssertValid();
}

void C飞机大战View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C飞机大战Doc* C飞机大战View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C飞机大战Doc)));
	return (C飞机大战Doc*)m_pDocument;
}
#endif //_DEBUG


// C飞机大战View 消息处理程序

void C飞机大战View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDC *pDC=GetDC();//传进来的句柄
	CRect rect;
	GetClientRect(&rect);
     
    


   //******************战机的移动*****************/
	    myplane.SetHorMotion(0);
		myplane.SetVerMotion(0);
		if(GetKey(VK_LEFT))
	{
		myplane.SetHorMotion(-10);//向左
	}
		if(GetKey(VK_RIGHT))
	{
		myplane.SetHorMotion(10);//向右
	}
		if(GetKey(VK_UP))
	{
		myplane.SetVerMotion(-10);//向上
	}
		if(GetKey(VK_DOWN))
	{
		myplane.SetVerMotion(10);//向下
	}
		

/*************************战机的边界**********************************/
	  if(myplane.GetPoint().x<0)
	  {
		  myplane.SetPoint(960,myplane.GetPoint().y);
	  }
	  if(myplane.GetPoint().x>970)
	  {
		  myplane.SetPoint(0,myplane.GetPoint().y);
	  }
	  if(myplane.GetPoint().y<0)
	  {
		  myplane.SetPoint(myplane.GetPoint().x,300);
	  }
	  if(myplane.GetPoint().x>600)
	  {
		  myplane.SetPoint(myplane.GetPoint().x,300);
	  }
	 

    //***************战机输出子弹的生成***************/
		if(GetKey(VK_SPACE))
	{
		
		//左右两颗子弹
			CBomb* newpBombL=new CBomb(myplane.GetPoint().x+2,myplane.GetPoint().y,0);
			CBomb* newpBombR=new CBomb(myplane.GetPoint().x+24,myplane.GetPoint().y,0);
		
		//加入链表的尾部
			obl.AddHead(newpBombL);
			obl.AddHead(newpBombR);
        //第一个子弹的位置，发射
			CBomb* pBomb=(CBomb*)obl.GetHead();
			POSITION pos=obl.GetHeadPosition();
			//清除子弹
			while(pos!=NULL)
			{
				POSITION dpos=pos;
				CBomb *pBomb = (CBomb *)obl.GetNext( pos );
				if(pBomb->GetPoint().y<0)
				{
					obl.RemoveAt(dpos);
					delete pBomb;
					continue;
				}
			}
	}
		if(GetKey('A'))
	{
		
		//左右两颗子弹
			CBomb* newpBombl=new CBomb(myplane.GetPoint().x+2,myplane.GetPoint().y,-10);
			CBomb* newpBombr=new CBomb(myplane.GetPoint().x+24,myplane.GetPoint().y,10);
			CBomb* newpBombm=new CBomb(myplane.GetPoint().x+15,myplane.GetPoint().y,0);
		
		//加入链表的尾部
			obl.AddHead(newpBombl);
			obl.AddHead(newpBombr);
			obl.AddHead(newpBombm);
        //第一个子弹的位置，发射
			CBomb* pBomb=(CBomb*)obl.GetHead();
			POSITION pos=obl.GetHeadPosition();
			//清除子弹
			while(pos!=NULL)
			{
				POSITION dpos=pos;
				CBomb *pBomb = (CBomb *)obl.GetNext( pos );
				if(pBomb->GetPoint().y<0)
				{
					obl.RemoveAt(dpos);
					delete pBomb;
					continue;
				}
			}
	}



   // ReleaseDC(pDC);
   C飞机大战View::OnDraw(pDC);
	CView::OnTimer(nIDEvent);
}
