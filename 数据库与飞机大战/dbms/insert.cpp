#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
#include "insert.h"
using namespace std;

void insert()
{
    char table_name[20],buff[100],buf[100];//buff�����������buf�ж��������ͻ���
    char tp;
    char *str=".txt";
    char tmp[20];
    int i=0,w=0,pos;//pos��¼����ֵλ��
    int num=0;//���Եĸ���
    int length[10];//ÿ�����Եĳ���
    char type[20][20];//ÿ�����Ե�����
    char insertbuff[1000];//�����һ������
    char table_buff[1500][10][100];//��������ڴ�
    char ttp,ttpv[100],ttpb[100];
    int data_num=0,pp=0;//��������
    int key=1,ss=0;//���������
    fstream f7;
    f7.open("key.txt",ios::binary|ios::in);
    string inputkeystr;//��������������
    tmp[i]=' ';
    string cmpa,cmpb,value;
    cout<<"Insert into ";
    cin>>table_name;
    cmpa=string(table_name);
    tp=readfile(f7);
    string ttpbstr;
    /* while(f7.eof()==0)
     {
         cout<<readfile(f7);
     }*/

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
            while(f7.eof()==0)
            {
                while(tp!=',')
                {
                    if(tp=='!')
                        tp=readfile(f7);
                    ttpb[ss]=tp;
                    tp=readfile(f7);
                    ttpb[ss+1]='\0';
                    ss++;
                }
                ss=0;
                ttpbstr=string(ttpb);
                if(ttpbstr==cmpa)
                {
                    tp=readfile(f7);
                    key=(int)tp-48;
                    break;
                }
                else
                {
                    tp=readfile(f7);
                    tp=readfile(f7);
                }
            }
            f7.close();
            int nn=1;//��ȡ���Ÿ�����Ҫ������������ȡһ��int
p:
            tp=readfile(f1);//��ȡ���Ը�����ÿ�����Գ��ȼ���������

            if(tp!='!')
            {
                while(nn<=1)
                {
                    tp=readfile(f1);
                    if(tp==',')
                    {
                        nn++;
                    }

                }
                tp=readfile(f1);
                while(tp!=',')
                {
                    type[num][w]=tp;
                    w++;
                    tp=readfile(f1);
                }
                w=0;
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

                for(int p=0; p<num; p++)
                {
                    for(int r=0; r<length[p]; r++)
                    {
                        ttp=readfile(f2);
                        table_buff[data_num][p][r]=ttp;
                    }
                }
                data_num++;
            }
            data_num--;
            cout<<"values ('";
            int buff_long;
            int base=0;//��¼insertbuff��¼����һλ
            for(int z=0; z<num; z++)
            {
s:
                cin>>value;
                if(z==(key-1))
                {
                    inputkeystr=value;
                }
                int buf_long,q=0;
                buf_long=value.copy(buf,90);
                buf[buf_long]='\0';
                switch(type[z][0])
                {
                case 'i':
                    if(buf_long>length[z])
                    {
                        cout<<"the value is too long,it should be "<<length[z]<<" try again!"<<endl;
                        goto s;
                    }
                    while(buf[q]!='\0')
                    {
                        if(buf[q]<'0'||buf[q]>'9')
                        {
                            cout<<"the value is wrong type! the type should be "<<type[z]<<" try again!"<<endl;
                            goto s;
                        }
                        q++;
                    }
                    break;
                case 'v':
                    if(buf_long>length[z])
                    {
                        cout<<"the value is too long,it should be "<<length[z]<<" try again!"<<endl;
                        goto s;
                    }
                    break;
                case 'd':
                    buf_long=value.copy(buf,90);
                    buf[buf_long]='\0';
                    if(buf_long!=length[z])
                    {
                        cout<<"the value's length is wrong,it should be "<<length[z]<<" try again!"<<endl;
                        goto s;
                    }
                    while(buf[q]!='\0')
                    {
                        if(buf[q]<'0'||buf[q]>'9')
                        {
                            cout<<"the value is wrong type! the type should be "<<type[z]<<" try again!"<<endl;
                            goto s;
                        }
                        q++;
                        if(q>8)
                        {
                            cout<<"the value is wrong type! the type should be "<<type[z]<<" try again!"<<endl;
                            goto s;
                        }
                    }
                    break;
                }
                string strtmp;
                for(int j=0; j<length[z]-value.size(); j++)
                {
                    strtmp=strtmp+" ";
                }
                value=value+strtmp;
                buff_long = value.copy(buff, 90);
                buff[buff_long] = '\0';
                for(pp=0; pp<=buff_long; pp++)
                    insertbuff[base+pp]=buff[pp];
                base=base+pp-1;
                string ttpp;
                if(z==(num-1))
                {
                    pos=data_num;
                    for(int i=0; i<data_num; i++)
                    {
                        for(int j=0; j<length[key-1]; j++)
                        {
                            if(table_buff[i][key-1][j]!=' ')
                            {
                                 ttpv[j]=table_buff[i][key-1][j];
                                 ttpv[j+1]='\0';
                            }

                        }
                        ttpp=string(ttpv);
                        if(ttpp==inputkeystr)
                        {
                            cout<<"�����ظ�!�����ԣ�"<<endl;
                            return;
                        }
                        if(ttpp>inputkeystr)
                        {
                            pos=i;
                            break;
                        }
                    }
                    f2.close();
                    fstream f6;
                    f6.open(table_name,ios::binary|ios::out);
                    for(int t=0; t<pos; t++)
                    {
                        for(int y=0; y<num; y++)
                        {
                            for(int u=0; u<length[y]; u++)
                            {
                                writefile(table_buff[t][y][u],f6);
                            }
                        }
                    }
                    for(int t=0; t<base; t++)
                    {
                        writefile(insertbuff[t],f6);
                    }
                    for(int t=pos; t<data_num; t++)
                    {
                        for(int y=0; y<num; y++)
                        {
                            for(int u=0; u<length[y]; u++)
                            {
                                writefile(table_buff[t][y][u],f6);
                            }
                        }
                    }
                    cout<<"')"<<endl<<"����ɹ�"<<endl;
                }

                else
                    cout<<"','";
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
