#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
using namespace std;

void display()//
{
    char table_name[20];
    char *str=".txt";
    cout<<"display:";
    cin>>table_name;
    char tp;
    char tmp[20];
    int i=0;
    int num=0;//���Եĸ���
    int length[10];//ÿ�����Եĳ���
    tmp[i]=' ';
    string cmpa,cmpb,value;
    cmpa=string(table_name);
    fstream f1;
    f1.open("model.txt",ios::binary|ios::in);//�ж��Ƿ���ڱ�;
o:
    tmp[i]=readfile(f1);
    i++;
    if(f1.eof()==0)
    {
        while(tmp[i-1]!=',')
        {
            tmp[i]=readfile(f1);
            i++;
        }
        tmp[i-1]='\0';
        cmpb=string(tmp);
        if(cmpa==cmpb)//��������
        {

            int nn=1;//��ȡ���Ÿ�����Ҫ������������ȡһ��int
p:
            tp=readfile(f1);//��ȡ���Ը�����ÿ�����Գ���
            if(tp!='!')
            {
                while(nn<=2)
                {
                    tp=readfile(f1);
                    if(tp==',')
                    {
                        nn++;
                    }
                }
                tp=readfile(f1);
                length[num]=(int)tp-48;
                tp=readfile(f1);
                if(tp<='9'&&tp>='0')
                {
                    length[num]=length[num]*10+((int)tp-48);
                    tp=readfile(f1);
                    if(tp<='9'&&tp>='0')
                    {
                        length[num]=length[num]*10+((int)tp-48);
                    }
                    else
                    {
                        f1.seekg(-8,ios::cur);
                    }
                }
                else
                {
                    f1.seekg(-8,ios::cur);
                }
                num++;
                nn=1;
                goto p;
            }
            else
            {
                f1.close();
            }
            strcat(table_name,str);//table_name ����
            fstream f2;
            f2.open(table_name,ios::binary|ios::in);
            while(f2.eof()==0)
            {
                for(int z=0; z<num; z++)
                {
                    for(int k=0; k<length[z]; k++)
                    {
                        cout<<readfile(f2);
                    }
                    cout<<"\t";
                }
                cout<<endl;
            }
            f2.close();
            return;
        }
        else
        {
            tp=readfile(f1);
            while(tp!='!')
            {
                tp=readfile(f1);
            }
            i=0;
            goto o;
        }
    }
    else
    {
        cout<<"the table is not exist."<<endl;
        f1.close();
        return;
    }
}

