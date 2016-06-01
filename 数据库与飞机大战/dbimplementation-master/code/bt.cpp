#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<time.h>
#include<stdio.h>
#include<iostream>
using std::cout;
using std::endl;

class BTree
{
public:
	int n;       //�ýڵ������ؼ��ֵĸ���  ���ڵ���2
	BTree *father;
	static int number;//����   ���ڵ���3
	static BTree *root;	
	BTree();	
	int *data;
	//int *offset;
	BTree **down;

	static bool inserttree(int t);//�����в���t
	static	BTree* searchinsert(int t);//�������뵽ĳ�ڵ�
	bool insertpoint(int t,BTree *p);//�ڽڵ����
	void split(int t,BTree *p);  //����

	static void treedel(int t);
	void  delpoint(int t);
	static BTree*searchdel(int t);//����ɾ��ĳ�ڵ�
	void combine();

	static int deep;  //���
	static void deletetree();
};
struct node
{
   BTree* q;
   node *next;
};
node *head=NULL;
int BTree::number=4;
int BTree::deep=0;
BTree *BTree::root=NULL;
BTree::BTree()             //����һ���ڵ�
{
	data=new int[number];
	down=new BTree*[number];
	for(int i=0;i<number;i++)
	{
		data[i]=0;
		down[i]=NULL;
	}
	father=NULL;
	n=0;
}
BTree* BTree::searchdel(int t)
{
	BTree *p;
	p=root;
	while(p->down[0]!=NULL)
	{
		int i;
		for(i=0;i<p->n&&t>p->data[i];i++);
		if(t==p->data[i])
			goto loop;     //Ҫ�ĸ��ڵ��ֵ
		p=p->down[i];
	}
	return p;
loop:
	int y=0;
	while(p->data[y]!=t)y++;//�������ڵĽ��
	BTree *q=p->down[y];
	while(q->down[0]!=NULL)
	{
		q=q->down[q->n-1];
	}
	int a=q->data[q->n-2];  //q����׶�
	p->data[y]=a;
	p=p->down[y];
	while(p->down[0]!=NULL)
	{
		p->data[p->n-1]=a;
		p=p->down[p->n-1];
	}
	return p;
}
void BTree::delpoint(int t)//��this��ɾ��t
{
	int i;
	for(i=0;i<n&&t>data[i];i++);
	if(t!=data[i])
	{
		cout<<"�޸�Ԫ��"<<endl;
		return ;   //�޸�Ԫ�أ�����;	
	}
	for(;i<n-1;i++)
	{
		data[i]=data[i+1];
		down[i]=down[i+1];
	}
	n--;
	if(n<(number+1)/2)  
	{
		combine();
	}
}
void BTree::treedel(int t)
{
	if(root==NULL)
	{
		cout<<"����"<<endl;
		return ;
	}
	if(t>root->data[root->n-1])
	{
		cout<<"�޸�Ԫ��"<<endl;
		return ;
	}
	searchdel(t)->delpoint(t);
	
}
void BTree::combine()  //1�Ž���ҵڶ�������������ǰһ��
{
	if(this==root)
	{
		if(root->n==0)
		{
			deep--;
			BTree *p=root;
			root=NULL;
			delete p;
		}
	else	
			if(root->n==1&&root->down[0]!=NULL)
		{	
				BTree *p=root;
				root=root->down[0];
				delete p;
				deep--;
		}
	
		return;
	}
	int i;
	for(i=0;i<father->n;i++)
	{
		if(father->down[i]==this)
			break;
	}
	if(0==i)
	{
		BTree *p;
		int j;
		p=father->down[1];
		if(p->n==(number+1)/2)
		{
			int a;
			a=data[n-1];
			for(j=0;j<p->n;j++)
			{
				data[n]=p->data[j];
				down[n++]=p->down[j];
				if(p->down[j]!=NULL)
					p->down[j]->father=this;
			}
			father->down[1]=this;
			father->delpoint(a);
			delete p;
		}
		else
		{
			father->data[0]=p->data[0];
			data[n]=p->data[0];
			down[n++]=p->down[0];
			if(p->down[0]!=NULL)p->down[0]->father=this;
			for(j=0;j<p->n-1;j++)
			{
				p->data[j]=p->data[j+1];
				p->down[j]=p->down[j+1]	;	
			}
			p->n--;
		}
	}
	else
	{
		BTree *p;
		int j;
		p=father->down[i-1];
		if(p->n==(number+1)/2)
		{
			int a;
			a=p->data[p->n-1];
			for(j=0;j<n;j++)
			{
				p->data[p->n]=data[j];
				p->down[p->n++]=down[j];
				if(down[j]!=NULL)
					down[j]->father=p;
			}
			father->down[i]=p;
			father->delpoint(a);
			delete this;
		}
		else
		{
			father->data[i-1]=p->data[p->n-2];
			p->n--;
			for(j=n;j>0;j--)
			{
				data[j]=data[j-1];
			}
			n++;
			data[0]=p->data[p->n];
		}
	}

}
BTree* BTree::searchinsert(int t)//����t�ĸò����λ�ã�����ָ��
{
	if(root==NULL)
	{
		root=new BTree;
		deep=1;
		return root;
	}
	BTree *p;
	p=root;
	if(t>root->data[root->n-1])  //�������ؼ���Ҫ�ĸ��ڵ�Ĺؼ���
	{
		while(p->down[0]!=NULL)
		{
			p->data[p->n-1]=t;
			p=p->down[p->n-1];
		}
		return p;
	}	
	while(p->down[0]!=NULL)
	{
		int i;
		for(i=0;i<p->n&&t>p->data[i];i++);
		p=p->down[i];
	}
	return p;
}
bool BTree:: inserttree(int t)//��t��������
{
	BTree *p=BTree::searchinsert(t);
	if(1==p->insertpoint(t,NULL))
		return 1;
	else 
		return 0;
}
bool BTree::insertpoint(int t,BTree *p)//��Ԫ��t������ָ����������this�����
{
	
	int i,j;
	for(i=n-1;i>=0&&data[i]>t;i--);

	if(i>=0&&t==data[i]) 
		return 0;  //��ͬ��������
	
	if(n+1>number)
	{
		split(t,p);
		return 1 ;
	}

	for(j=n-1;j>i;j--)      //����Ԫ�غ�ָ��
	{
		data[j+1]=data[j];
		
		down[j+1]=down[j];
	}
	data[i+1]=t;
	down[i+1]=p;
	if(p!=NULL)
		p->father=this;
	n++;
	return 1;
}
void BTree::split(int t,BTree *p)//t,p�ֱ��Ƕ���Ľڵ��ַ���ؼ��֣�����this�ڵ�
{
	
	int i,j;
	if(this==root)
	{
		deep++;
		root=new BTree;
		BTree *pt=new BTree;
		for(i=0,j=0;i<(number+1)/2;i++)//�ҵ�ǰ(number+1)/2����pt
		{
			if(t>data[j])
			{
				pt->data[i]=data[j];
				if(down[i]!=NULL)
					down[i]->father=pt;
				pt->down[i]=down[j];
				j++;
			}
			else
			{
				pt->data[i]=t;
				t=99999999;
				if(p!=NULL)
					p->father=pt;
				pt->down[i]=p;
			}

		}
		pt->father=root;
		pt->n=(number+1)/2;
		root->data[0]=pt->data[(number+1)/2-1];
		root->down[0]=pt;
		for(i=0;i<number-(number+1)/2+1;i++)
		{
			if(j==number)
			{
				data[i]=t;
				down[i]=p;
				break;
			}
			if(t>data[j])
			{
				data[i]=data[j];
				down[i]=down[j];
				j++;
			}
			else
			{
				data[i]=t;
				down[i]=p;
				t=99999999;
			}			
		}
		father=root;
		n=number-(number+1)/2+1;
		root->n=2;
		root->data[1]=data[number-(number+1)/2];
		root->down[1]=this;	
		}
	else
	{
		BTree *pt=new BTree;
		for(i=0,j=0;i<(number+1)/2;i++)
		{
			if(t>data[j])
			{
				pt->data[i]=data[j];
				if(down[j]!=NULL)down[j]->father=pt;
				pt->down[i]=down[j];
				j++;
			}
			else
			{
				pt->data[i]=t;
				t=99999999;
				if(p!=NULL)p->father=pt;
				pt->down[i]=p;
			}

		}
		pt->father=father;
		pt->n=(number+1)/2;
		for(i=0;i<number-(number+1)/2+1;i++)
		{
			if(j==number){data[i]=t;down[i]=p;break;}
			if(t>data[j])
			{
				data[i]=data[j];
				down[i]=down[j];
				j++;
			}
			else
			{
				data[i]=t;
				t=99999999;
				down[i]=p;
			}			
		}
		n=number-(number+1)/2+1;
		father->insertpoint(pt->data[pt->n-1],pt);
	}

}

int *x;    //����Ľ����
class dui
{
	
public :
	BTree * data[200];  //Ԫ��
	int   num[200];    //��Ԫ���ǵڼ����
	int tp,tl;//tpΪ��ͷ��tlΪ��β
	dui(){tp=0;tl=0;}
	BTree* pop();
	void push(BTree*,int);
	bool empty(); 
};
BTree* dui::pop()//����
{
	int t;
	t=tp;
	tp=(tp+1)%200;
	if(num[t]!=BTree::deep-1)//��ΪҶ�ӽڵ�
	{
		for(int i=0;i<data[t]->n;i++)
		{
			push(data[t]->down[i],num[t]+1);
		}
	}
	return data[t];
  }
void dui::push(BTree *i,int j)
{
	data[tl]=i;
	num[tl]=j;
	tl=(tl+1)%200;
	x[j]++;
}
bool dui::empty()
{
	if(tp==tl)return 1;
	else return 0;
}
dui qu;
void print(BTree *p)
{
	
	for (int i=0; i <p->n; i++)
		cout<<p->data[i];		
	cout<<" | ";
}
void printtree(BTree *q)
{
	if(q==NULL)
	{
		cout<<"����"<<endl;
		return;
	}
	int i,j;
	for(i=0;i<BTree::deep;i++)
	{
		x[i]=0;
	}
	qu.push(q,0);
	for(i=0;i<BTree::deep;i++)
	{
		cout<<"��"<<i+1<<"��:"<<endl;
		for(j=0;j<x[i];j++)
		{	
			
			print(qu.pop());
			
		}
		cout<<endl;
	}
}
void BTree::deletetree()
{
	if(root!=NULL)
	{
		deep=1;
		qu.push(root,0);
	}
	while(!qu.empty())
	{
		delete(qu.pop());
	}
	node *p;
	while(head!=NULL)
	{
		p=head;
		head=head->next;
		delete(p);
	}

}
void Createlink(BTree* p)
{
	qu.push(p,0);
	BTree *tree;
	do
	{
		tree=qu.pop();
	}while(tree->down[0]!=NULL);
	node *p1,*p2;
	head=p1=new node;
	p1->q=tree;
	while(!qu.empty())
	{
		p2=new node;
		p2->q=qu.pop();
		p1->next=p2;
		p1=p2;
	}
	p1->next=NULL;
}

void Create(int m)
{
	BTree::deletetree();
	srand((unsigned)time(NULL));
	for(int i=0;i<m;i++)
	{
		BTree::inserttree(rand()%999+1);
	}
	x=new int[BTree::deep];
 	Createlink(BTree::root);
	
}
void searchroot(int t)
{
	if(BTree::root==NULL)
	{
		cout<<"����"<<endl;
		return;
	}
	if(t>BTree::root->data[BTree::root->n-1])
	{
		cout<<"�޸Ľ��ֵ"<<endl;
		return;
	}
	BTree *p=BTree::root;
	while(p->down[0]!=NULL)
	{
		int i;
		for(i=0;i<p->n&&t>p->data[i];i++);
		p=p->down[i];
	}
	int i;
	for(i=0;i<p->n&&t>p->data[i];i++);
	if(t==p->data[i])
		cout<<"success!~~���ڸý��ֵ"<<endl;
	else 
		cout<<"fail!~~~�����ڸý��ֵ��~~"<<endl;
}
void searchlink(int t)
{
	if(head==NULL)
	{
		cout<<"����"<<endl;
		return;
	}
	node *p=head;
	int n=0;
	while(p!=NULL)
	{
		n++;
		int i;
		for(i=0;i<p->q->n&&t>p->q->data[i];i++);
		if(t==p->q->data[i]){cout<<"success!~���ڵ�"<<BTree::deep<<"��ĵ�"<<n<<"�������"<<endl;break;}
		else
			if(t<p->q->data[i])
		{
			cout<<"fail!~�޸ý��ֵ"<<endl;
			break;
		}
		p=p->next;		
	}
	if(p==NULL)cout<<"fail!~�޸ý��ֵ"<<endl;


}



/*
void main()
{
	int choice;
	do
	{
		system("cls");
		cout<<"*******************************************************************"<<endl;
		cout<<"*           ��ӭ����B+����ʾ������ѡ����Ӧ���ܡ�                *"<<endl;
		cout<<"*           1���������һ��B+����                                 *"<<endl;
 		cout<<"*           2����B+��������Ҷ����һ������                         *"<<endl;
		cout<<"*           3����B+�������ø�����һ������                         *"<<endl;
		cout<<"*           4����B+���в���һ������                               *"<<endl;
		cout<<"*           5����B+����ɾ��һ������                               *"<<endl;
		cout<<"*           6����ʾ����B+����                                     *"<<endl;
		cout<<"*           0���˳�����                                         *"<<endl;
		cout<<"*******************************************************************"<<endl;
		cout<<"��ѡ��"<<endl;
		cin>>choice;
		int m;
		switch (choice)
		{
			case 1:
				system("cls");
				cout<<"��ѡ����Ǵ���B+��"<<endl;
				cout<<"���������(>=3)"<<endl;
				cin>>BTree::number;
				cout<<"���������ݸ���(10-150)��"<<endl;
				cin>>m;
				Create(m);
				cout<<"�����ɹ�"<<endl;
				printtree(BTree::root);
				getchar();
				cin>>m;
				break;

			case 2:
				system("cls");
				cout<<"��B+��������Ҷ��������һ����"<<endl;
				cout<<"������Ҫ���ҵ���ֵ��"<<endl;
				cin>>m;
				searchlink(m);
				getchar();
				cin>>m;
				break;
			case 3:
				system("cls");
				cout<<"��B+�������ø�����һ����"<<endl;
				cout<<"������Ҫ���ҵ���ֵ��"<<endl;
				cin>>m;
				searchroot(m);

				getchar();
				cin>>m;
				break;

			case 4:
				system("cls");
				cout<<"��ѡ����ǲ���һ���Զ������"<<endl;
				cout<<"����ǰ��������:"<<endl;
				printtree(BTree::root);
				cout<<"������Ҫ�������ֵ��"<<endl;
				cin>>m;
				if(BTree::inserttree(m)==1)cout<<"����ɹ�"<<endl;
				else cout<<"����ʧ�ܣ�������ͬԪ��"<<endl;
				cout<<"������������"<<endl;
				printtree(BTree::root);
				getchar();
				cin>>m;
				break;
	
			case 5:
				system("cls");
				cout<<"��ѡ�����ɾ��һ���Զ������"<<endl;
				cout<<"ɾ��ǰ��������:"<<endl;
				printtree(BTree::root);
				cout<<"������Ҫɾ������ֵ��"<<endl;
				cin>>m;
				BTree::treedel(m);
				cout<<"ɾ�����������:"<<endl;
				printtree(BTree::root);
				getchar();
				break;

			case 6:
				system("cls");
				printtree(BTree::root);
				cin>>m;
				getchar();
			break;
		}
	}while(choice);

}*/