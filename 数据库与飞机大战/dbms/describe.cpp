#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
#include "display.h"
#include "insert.h"
#include "describe.h"

using namespace std;

void describe()
{
    char table_name[20];//buff输入转存
    char tp;
    char tmp[20];
    int i=0;
    int num=0;//属性的个数
    tmp[i]=' ';
    string cmpa,cmpb,value;
    cout<<"describe:";
    cin>>table_name;
    cmpa=string(table_name);
    fstream f1;
    f1.open("model.txt",ios::binary|ios::in);//判断是否存在表;
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
        if(cmpa==cmpb)//表名存在
        {
            cout<<cmpb<<"(";

            char tmpp[100];
            int k=1;
            int end=0;

            while(1)
            {
                tp=readfile(f1);
                tmpp[k-1]=tp;
                while(tmpp[k-1]!=','&&tmpp[k-1]!='!')
                {
                    tmpp[k]=readfile(f1);
                    k++;
                }
                if(tmpp[k-1]=='!')
                {
                    end=1;
                }
                tmpp[k-1]='\0';
                num++;
                if(num==1)
                {
                    cout<<"'"<<tmpp<< "' ";
                    k=1;
                }
                else if(num==2)
                {
                    k=1;
                    cout<<tmpp<<"(";
                }
                else
                {
                    num=0;
                    k=1;
                    if(end==0)
                        cout<<tmpp<<"),";
                    else
                    {
                        cout<<tmpp<<"))"<<endl;
                        f1.close();
                        return;
                    }
                }
            }
            f1.close();
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
