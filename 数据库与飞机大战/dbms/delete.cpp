#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
#include "delete.h"
using namespace std;

void refresh(int start,int end,fstream &f)//��start��ʼд��end
{
    fstream f3;
    f3.open("reftmp.txt",ios::binary|ios::out|ios::app);
    char tp;
    f.seekg(start,ios::beg);
    for(int i=start/8; i<end/8; i++)
    {
        tp=readfile(f);
        writefile(tp,f3);
    }
    f3.close();
}

void Delete()
{
    char table_name[20];//buf�ж��������ͻ���
    char tp;
    char *str=".txt";
    char tmp[30];
    int i=0,w=0;
    int num=0;//���Եĸ���
    int length[10];//ÿ�����Եĳ���
    char name[20][20];//ÿ�����Ե�����
    int start=0,end=0;
    int power=0;//�Ƿ���ɾ������Ŀ
    tmp[i]=' ';
    string cmpa,cmpb,value;
    cout<<"Delete from ";
    cin>>table_name;
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
            int nn=1;//��ȡ���Ÿ���
            f1.seekg(-8,ios::cur);
p:
            tp=readfile(f1);//��ȡ���Ը�����ÿ�����Գ��ȼ���������
            if(tp!='!')
            {
                tp=readfile(f1);
                while(tp!=',')
                {
                    name[num][w]=tp;
                    w++;
                    tp=readfile(f1);
                }
                name[num][w]='\0';
                w=0;
                tp=readfile(f1);
                while(nn<=1)
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
            cout<<"where ";

            char tiaojian1[20];
            cin>>tiaojian1;//������
            cout<<"=";
            char tiaojian2[20];
            cin>>tiaojian2;
            string tiaojian2str=string(tiaojian2);
            string tiaojian1str=string(tiaojian1);
            string shuxing;
            int pos=0;//��pos�����������õ�
            for(int z=0; z<num; z++)
            {
                shuxing=string(name[z]);
                if(tiaojian1str==shuxing)//û���ж������Ƿ����
                {
                    pos=z;
                    break;
                }
            }
            int sum=0;//ÿ�����ݵļ��λ��
            for(int z=0; z<num; z++)
            {
                sum=sum+length[z]*8;
            }
            sum=sum-length[pos]*8;
            int firstpos=0;//�ʼ����λ��
            for(int z=0; z<pos; z++)
            {
                firstpos=firstpos+length[z]*8;
            }

            f2.seekg(firstpos,ios::cur);//��һ��
            char tmpp[30];//����ֵ
            string tmpstr;
            int time=0;//�ڼ���������Ӧ��ɾ����
            while(1)
            {
                for(int z=0; z<length[pos]; z++)
                {
                    tmpp[z]=readfile(f2);
                    if(tmpp[z]==' ')
                    {
                        tmpp[z]='\0';
                    }
                    tmpp[z+1]='\0';
                }
                time++;
                tmpstr=string(tmpp);
                if(tmpstr==tiaojian2str)
                {
                    end=time*(length[pos]*8+sum);
                    refresh(start,end-length[pos]*8-sum,f2);
                    f2.seekg(end-(sum-firstpos),ios::beg);
                    power=1;
                    start=end;
                }
                // f2.seekg(sum-firstpos,ios::cur);
                if(f2.eof()!=0)
                {
                    if(power==0)
                    {
                        cout<<"��������Ԫ�ز�����!"<<endl;
                        return;
                    }
                    else
                    {
                        f2.close();
                        end=(time-1)*(length[pos]*8+sum);
                        fstream f4;
                        f4.open(table_name,ios::binary|ios::in);
                        refresh(start,end,f4);
                        f4.close();
                        char tt[]="del ";
                        strcat(tt,table_name);
                        system(tt);
                        rename("reftmp.txt",table_name);
                        cout<<"ɾ�����!"<<endl;
                        return;
                    }
                }
                else
                {
                    //f2.seekg(firstpos-sum,ios::cur);
                }
                f2.seekg(sum,ios::cur);//���
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
