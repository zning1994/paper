// �ɻ���սView.cpp : C�ɻ���սView ���ʵ��
//

#include "stdafx.h"
#include "�ɻ���ս.h"

#include "�ɻ���սDoc.h"
#include "�ɻ���սView.h"
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
int DaoJu_Waite=0;//�������
// C�ɻ���սView

IMPLEMENT_DYNCREATE(C�ɻ���սView, CView)

BEGIN_MESSAGE_MAP(C�ɻ���սView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C�ɻ���սView ����/����

C�ɻ���սView::C�ɻ���սView()
{
	// TODO: �ڴ˴���ӹ������
	//PlaySound(TEXT("../sound/nizhan.wav"),NULL,SND_FILENAME | SND_ASYNC);
	//����ͼƬ
	myplane.LoadImage();
	enemy.LoadImage();
	bomb.LoadImage();
	ball.LoadImage();
	explosion.LoadImage();
	daoju.LoadImage();
	//text.Draw();
}

C�ɻ���սView::~C�ɻ���սView()
{
}

BOOL C�ɻ���սView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C�ɻ���սView ����

void C�ɻ���սView::OnDraw(CDC* pDC)
{
	
	
	C�ɻ���սDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	//˫����

	 CRect rc; 
     CDC MecDC; 
     GetClientRect(&rc); 
     CBitmap bmp; //�ڴ��г�����ʱͼ���λͼ 

     MecDC.CreateCompatibleDC(pDC); //��������DC���������ڴ�DC 
 	 //bmp.CreateCompatibleBitmap(pDC,rc.right,rc.bottom); //��������λͼ(������pDC���������򻭳���ͼ�α�ɺ�ɫ)
	 bmp.LoadBitmap(IDB_SKY);//���뱳��ͼƬ
     CBitmap *pOldBit=MecDC.SelectObject(&bmp); //�ú���ѡ��һ����ָ�����豸�����Ļ����У����¶����滻��ǰ����ͬ���͵Ķ���
   
	// MecDC.FillSolidRect(0,0,rc.right,rc.bottom,RGB(100,149,237));  //��ԭ���������ͻ�������Ȼ���Ǻ�ɫ


	/******************ս��*********************/
	 if(n>0)
	 {
		myplane.Draw(&MecDC,TRUE);
	 }
	
	//*****************����л�****************/
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


	  
	 if(oblenemy.GetCount()<number)//���ɵл�����
	 {
	 
		 int x=rand()%970;
		 int n=rand()%2?1:-1;//����Ĳ���������������
		 CEnemy* pEnemy=new CEnemy(x,n==1?0:600,n);//���ɵл�
		 oblenemy.AddHead(pEnemy);

	 }
	 POSITION pos=oblenemy.GetHeadPosition();
	 while(pos!=0)//�����л�������Խ��ľͽ���ɾ��
	 {
		 POSITION dpos=pos;
		 CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(pos);//������һ����ַ
		 if(pEnemy->GetPoint().y>600||pEnemy->GetPoint().y<0)//ɾ���л�
		 {
			 oblenemy.RemoveAt(dpos);
			 delete pEnemy;
			 continue;
		 }
		  pEnemy->Draw(&MecDC,TRUE);//��ͼ
	 }




   //**************�л�������  ��ײ���//����ս���ӵ�*******************/


   if(n>0&&obl.IsEmpty()==0)//isempty ���ǿյ�ʱ�򷵻�0���жϵ����Ƿ�Ϊ��o����ս��
{
	
		//��һ��������һ��λ��
		CBomb* pBomb=(CBomb*)obl.GetHead();
        POSITION pos=obl.GetHeadPosition();

		bool isFired =false;//�Ƿ���Ա�����
		while(pos!=NULL)//��������
		{
		//��һ�����������Ժ󣬻��������Զ���ֵ����һ������
		    POSITION dpos=pos;
			pBomb=(CBomb*)obl.GetNext(pos);
			/**************************��������********************************/
			//�����ľ�������
			CRect One = CRect(pBomb->GetPoint().x,pBomb->GetPoint().y,(pBomb->GetPoint().x)+10,(pBomb->GetPoint().y)+20);
			
			
			if(oblenemy.IsEmpty()==0)//�жϵл��Ƿ�Ϊ��
            {
				POSITION posD=oblenemy.GetHeadPosition();
				
				CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
				while(posD!=NULL)//�����л�
				{
					POSITION dposD=posD;
					CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posD);

				/**************************��������********************************/
				//	�л��ľ�������
				CRect Two = CRect(pEnemy->GetPoint().x,pEnemy->GetPoint().y,(pEnemy->GetPoint().x) +35,(pEnemy->GetPoint().y)+35);
				CRect Inter;
				if(Inter.IntersectRect(One,Two))//��ײ
				{
				    PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
				    m++;
					 //����ըͼƬ
					CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
					newplosion->Draw(&MecDC,TRUE);	
					//ɾ���л�
					oblenemy.RemoveAt(dposD);
					delete pEnemy;
					//ɾ����ըͼƬ
					delete newplosion;
					isFired = true;//ȷ��������
					break;
				}
				}
				
			}
			if(!isFired)
			pBomb->Draw(&MecDC,TRUE);//������
			else
			{
				//ɾ��ը��
				obl.RemoveAt(dpos);
				delete pBomb;
			}
			
				
		}
}

//**********************�л���ս����ײ*****************/
   if(n>0&&oblenemy.IsEmpty()==0)
   {
       POSITION posD=oblenemy.GetHeadPosition();
				
	   CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
		while(posD!=NULL)//�����л�
			{
					POSITION dposD=posD;
					CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posD);

				/**************************��������********************************/
				//	�л��ľ�������ö����ṹ������һ��Դ����
				CRect Three = CRect(pEnemy->GetPoint().x,pEnemy->GetPoint().y,(pEnemy->GetPoint().x) +35,(pEnemy->GetPoint().y)+35);
				//ս���ľ���������ö����ṹ������һ��Դ����
				CRect Four = CRect(myplane.GetPoint().x,myplane.GetPoint().y,myplane.GetPoint().x+50,myplane.GetPoint().y+60);
				CRect Inter2;//�˺���ʹInter2�����������о��εĽ�����������Դ���ε��غϲ��֡�
				if(Inter2.IntersectRect(Three,Four))//��ײ�������Inter2��Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�0��
				{
				    PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
				    m++;
					 //����ըͼƬ
					CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
					newplosion->Draw(&MecDC,TRUE);	
					//ɾ���л�
					oblenemy.RemoveAt(dposD);
					delete pEnemy;
					//ɾ����ըͼƬ
					delete newplosion;
	                 n--;
					break;
				}
		  }
   }

			
//*********************���Ƶл����ӵ���ը��ս��**********/
  
 //�������������ĵл�,�洢�ӵ�
	 POSITION pos3=oblenemy.GetHeadPosition();
	 
	 bool isFired =false;//�Ƿ���Ա�����
	   while(pos3!=NULL)
     {
		 CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(pos3);
	  
		int find=0;//�����ж��Ƿ���Ϸ����ӵ�������
		if(myplane.GetPoint().x>=pEnemy->GetPoint().x-50&&myplane.GetPoint().x<pEnemy->GetPoint().x+35)
   
	     {
			 if((pEnemy->GetMontion()==1&&myplane.GetPoint().y>pEnemy->GetPoint().y)||(pEnemy->GetMontion()==-1&&myplane.GetPoint().y<pEnemy->GetPoint().y))
			 {
				 find=1;//��������
				 if(pEnemy->m_nWait%20==0)//��ʱ����
				 {
		            CBall *pBall=new CBall(pEnemy->GetPoint().x+17,pEnemy->GetPoint().y,pEnemy->GetMontion());
	                oblball.AddHead(pBall);
				 }
				 pEnemy->m_nWait++;//�洢�ӵ�����ʱ20��ˢ��ʱ��
			 }
        }
	   if(find==0)
			pEnemy->m_nWait=0;//�����Ϸ���������ʱ��ͳ�ʼλ����λ0

     }   
//׼�������ӵ�
	   if(n>0&&oblball.IsEmpty()==0)//isempty ���ǿյ�ʱ�򷵻�0��ս�����ڲŻᷢ�ӵ�
     {
		//��һ���ӵ���һ��λ��
		 CBall* pBall=(CBall*)oblball.GetHead();
        POSITION pos=oblball.GetHeadPosition();
        
		while(pos!=NULL)//�����ӵ�
		{
			POSITION dpos=pos;
		  //��һ���ӵ������Ժ󣬻��ӵ����Զ���ֵ����һ���ӵ�λ��
			CBall* pBall=(CBall*)oblball.GetNext(pos);
			//�ӵ���Խ��ɾ��
			if(pBall->GetPoint().y>600||pBall->GetPoint().y<0)//ɾ���л�
		       {
			     oblball.RemoveAt(dpos);
			     delete pBall;
			     continue;
		       }
			//û��Խ���ӵ���ը
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
					n--;//�ж�ս������ֵ
					
					isFired = true;
					break;//һ���ӵ�ֻ��һ���ɻ�
				}
				
			}
            
			if(!isFired)
			pBall->Draw(&MecDC,TRUE);
			
			
		}
     }
	   
	   
//*********************����**********************/
	 DaoJu_Waite++;//���Ƴ������ʱ��
	 if(DaoJu_Waite==100)
	 {
		 DaoJu_Waite=0;
		 int x=rand()%970;
		 int y=rand()%600;
		 CDaoju* pDaoju=new CDaoju(x,y);
		 obldaoju.AddHead(pDaoju);
	 }
	 POSITION posW=obldaoju.GetHeadPosition();
	 while(posW!=0)//�����л�������Խ��ľͽ���ɾ��
	 {
		 POSITION dposW=posW;
		 CDaoju* pDaoju=(CDaoju*)obldaoju.GetNext(posW);//������һ����ַ
		 if(pDaoju->GetPoint().y>600)//ɾ���л�
		 {
			 obldaoju.RemoveAt(dposW);
			 delete pDaoju;
			 continue;
		 }
		 //	���ߵľ�������ö����ṹ������һ��Դ����
		 CRect DAOJU = CRect(pDaoju->GetPoint().x,pDaoju->GetPoint().y,(pDaoju->GetPoint().x) +29,(pDaoju->GetPoint().y)+28);
		 //ս���ľ���������ö����ṹ������һ��Դ����
		 CRect ZHANJI = CRect(myplane.GetPoint().x,myplane.GetPoint().y,myplane.GetPoint().x+50,myplane.GetPoint().y+60);
		 CRect Inter3;//�˺���ʹInter2�����������о��εĽ�����������Դ���ε��غϲ��֡�
		 if(Inter3.IntersectRect(DAOJU,ZHANJI))
		 {
			 n+=5;
			 obldaoju.RemoveAt(dposW);
			 delete pDaoju;
			 continue;
		 }
		  pDaoju->Draw(&MecDC,TRUE);//��ͼ
	 }

	 /***************************����**********************/
	 if(GetKey('S'))
	 {
		 if(m>80&&n>50)
		 {
			 if(oblenemy.IsEmpty()==0)
			 {
                  POSITION posS=oblenemy.GetHeadPosition();
				
				  CEnemy* pEnemy=(CEnemy*)oblenemy.GetHead();
				  while(posS!=NULL)//�����л�
					{
					  POSITION dposS=posS;
					  CEnemy* pEnemy=(CEnemy*)oblenemy.GetNext(posS);
					  if(pEnemy->GetPoint().x>0&&pEnemy->GetPoint().x<970)
						  if(pEnemy->GetPoint().y>0&&pEnemy->GetPoint().y<600)
						  {
							  PlaySound(TEXT("../sound/bomb.wav"),NULL,SND_FILENAME | SND_ASYNC);
							  m++;
							 //����ըͼƬ
							  CExplosion* newplosion=new CExplosion(pEnemy->GetPoint().x,pEnemy->GetPoint().y);
							  newplosion->Draw(&MecDC,TRUE);	
							//ɾ���л�
							  oblenemy.RemoveAt(dposS);
						      delete pEnemy;
					        //ɾ����ըͼƬ
					          delete newplosion;
							 

						  }

					}
				   n-=10;
			 }
		 }
	 }


	   /*******************�������*************************/
	 	
		CFont*  m_pFont=new CFont;
		LOGFONT lf; 
        MecDC.SelectObject(*m_pFont); 
		
		MecDC.SetTextColor(RGB(255,255,0));//��ɫ
		MecDC.SetBkMode(TRANSPARENT);//͸��
		CString s,sm,sgq;
		//int n;
		s.Format(TEXT("����л��������� %d"),m);
		sm.Format(TEXT("ս��������ֵΪ��%d"),n);

		MecDC.TextOutW(10,10,s);
		MecDC.TextOutW(10,30,sm);
		MecDC.TextOutW(10,50,_T("�����ڵĹؿ���"));
		if(m<30)
		{ 
            MecDC.TextOutW(110,50,_T("��һ��"));
		}else if(m<50&&m>=30 )
		{
			MecDC.TextOutW(110,50,_T("�ڶ���"));
		}else  if(m<100&&m>=50)
		{
			MecDC.TextOutW(110,50,_T("������"));
		}else if(m>100&&m<=150)
		{
            MecDC.TextOutW(110,50,_T("���Ĺ�"));
		}	
			if(m>150&&m<300)
		{
			MecDC.TextOutW(110,50,_T("ӭ���޵�״̬�ɣ�������"));			
		}else if(m>=300&&n!=0)
		{
            
            memset(&lf, 0, sizeof(LOGFONT));		
			lf.lfHeight  = 80;  
			lf.lfWeight  = 20;  
			m_pFont->CreateFontIndirect(&lf); //��������
			MecDC.SelectObject(*m_pFont); //��ΪĬ�ϵ�����
			MecDC.TextOutW(100,300,_T("��ϲ�㣬ͨ���ˣ�����"));
            KillTimer(1);
			delete m_pFont;


		}
		if(n==0)
		{
			memset(&lf, 0, sizeof(LOGFONT));		
			lf.lfHeight  = 80;  
			lf.lfWeight  = 20;  
			m_pFont->CreateFontIndirect(&lf); //��������
			MecDC.SelectObject(*m_pFont); //��ΪĬ�ϵ�����
			MecDC.TextOutW(300,300,_T("��Ϸ����������"));
			delete m_pFont;
			//���Ըĳ�ͼƬ������û�к��ʵ�
			 /*CImageList images;
			 CBitmap bmp1;
			 bmp1.LoadBitmap(IDB_GAMEOVER);
			 images.Create(220,220,ILC_COLOR24,0,1);
			 images.Add(&bmp1,RGB(0,0,0));
			 images.Draw(&MecDC,0,CPoint(300,160),ILD_TRANSPARENT);*/
		}



	//˫����
	pDC->BitBlt(0,0,rc.right,rc.bottom,&MecDC,0,0,SRCCOPY);////���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨ 

     //��ͼ��ɺ������
    MecDC.DeleteDC();//ɾ��DC

    bmp.DeleteObject(); //ɾ��λͼ
	SetTimer(1,40,NULL);
	//ͨ��
	if(m>=300&&n!=0)
		KillTimer(1);

	
}


// C�ɻ���սView ��ӡ

BOOL C�ɻ���սView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C�ɻ���սView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C�ɻ���սView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// C�ɻ���սView ���

#ifdef _DEBUG
void C�ɻ���սView::AssertValid() const
{
	CView::AssertValid();
}

void C�ɻ���սView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C�ɻ���սDoc* C�ɻ���սView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C�ɻ���սDoc)));
	return (C�ɻ���սDoc*)m_pDocument;
}
#endif //_DEBUG


// C�ɻ���սView ��Ϣ�������

void C�ɻ���սView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDC *pDC=GetDC();//�������ľ��
	CRect rect;
	GetClientRect(&rect);
     
    


   //******************ս�����ƶ�*****************/
	    myplane.SetHorMotion(0);
		myplane.SetVerMotion(0);
		if(GetKey(VK_LEFT))
	{
		myplane.SetHorMotion(-10);//����
	}
		if(GetKey(VK_RIGHT))
	{
		myplane.SetHorMotion(10);//����
	}
		if(GetKey(VK_UP))
	{
		myplane.SetVerMotion(-10);//����
	}
		if(GetKey(VK_DOWN))
	{
		myplane.SetVerMotion(10);//����
	}
		

/*************************ս���ı߽�**********************************/
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
	 

    //***************ս������ӵ�������***************/
		if(GetKey(VK_SPACE))
	{
		
		//���������ӵ�
			CBomb* newpBombL=new CBomb(myplane.GetPoint().x+2,myplane.GetPoint().y,0);
			CBomb* newpBombR=new CBomb(myplane.GetPoint().x+24,myplane.GetPoint().y,0);
		
		//���������β��
			obl.AddHead(newpBombL);
			obl.AddHead(newpBombR);
        //��һ���ӵ���λ�ã�����
			CBomb* pBomb=(CBomb*)obl.GetHead();
			POSITION pos=obl.GetHeadPosition();
			//����ӵ�
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
		
		//���������ӵ�
			CBomb* newpBombl=new CBomb(myplane.GetPoint().x+2,myplane.GetPoint().y,-10);
			CBomb* newpBombr=new CBomb(myplane.GetPoint().x+24,myplane.GetPoint().y,10);
			CBomb* newpBombm=new CBomb(myplane.GetPoint().x+15,myplane.GetPoint().y,0);
		
		//���������β��
			obl.AddHead(newpBombl);
			obl.AddHead(newpBombr);
			obl.AddHead(newpBombm);
        //��һ���ӵ���λ�ã�����
			CBomb* pBomb=(CBomb*)obl.GetHead();
			POSITION pos=obl.GetHeadPosition();
			//����ӵ�
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
   C�ɻ���սView::OnDraw(pDC);
	CView::OnTimer(nIDEvent);
}
