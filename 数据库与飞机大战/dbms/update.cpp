#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
#include "update.h"
#include "delete.h"
using namespace std;

void update()
{
    char result[20][90][90];//存放要更新的所有属性
    cout<<"update:(输入表名)";
    char table_name[20];//buf判断数据类型缓冲
    char tp;
    char *str=".txt";
    char tmp[30];
    int i=0,w=0;
    int num=0;//属性的个数
    int length[10];//每个属性的长度
    char name[20][20];//每个属性的名称
    int start=0,end=0;
    int power=0;//是否有删除的条目
    tmp[i]=' ';
    string cmpa,cmpb;
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
            int nn=1;//读取逗号个数
            f1.seekg(-8,ios::cur);
p:
            tp=readfile(f1);//读取属性个数及每个属性长度及属性名称
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
            strcat(table_name,str);//table_name 表名
            fstream f2;
            f2.open(table_name,ios::binary|ios::in);
            cout<<"where(输入条件属性名)";
            char tiaojian1[20];
            cin>>tiaojian1;//属性名
            cout<<"=(输入属性值)";
            char tiaojian2[20];
            cin>>tiaojian2;
            string tiaojian2str=string(tiaojian2);
            string tiaojian1str=string(tiaojian1);
            string shuxing;
            int pos=0;//第pos个属性是有用的
            for(int z=0; z<num; z++)
            {
                shuxing=string(name[z]);
                if(tiaojian1str==shuxing)//没有判断属性是否存在
                {
                    pos=z;
                    break;
                }
            }
            int sum=0;//每条数据的间隔位数
            for(int z=0; z<num; z++)
            {
                sum=sum+length[z]*8;
            }
            sum=sum-length[pos]*8;
            int firstpos=0;//最开始后移位数
            for(int z=0; z<pos; z++)
            {
                firstpos=firstpos+length[z]*8;
            }

            f2.seekg(firstpos,ios::cur);//第一个
            char tmpp[30];//属性值
            string tmpstr;
            int time=0;//第几条数据是应当删除的
            int n=0;//共删除n条数据
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
                    f2.seekg(-length[pos]*8-firstpos,ios::cur);
                    for(int p=0; p<num; p++)
                    {
                        for(int q=0; q<length[p]; q++)
                        {
                            result[n][p][q]=readfile(f2);
                            cout<<result[n][p][q];
                            result[n][p][q+1]='\0';
                        }
                    }
                    end=time*(length[pos]*8+sum);
                    refresh(start,end-length[pos]*8-sum,f2);
                    f2.seekg(end-(sum-firstpos),ios::beg);
                    power=1;
                    start=end;
                    n++;
                }
                // f2.seekg(sum-firstpos,ios::cur);
                if(f2.eof()!=0)
                {
                    if(power==0)
                    {
                        cout<<"符合条件元素不存在!"<<endl;
                        return ;
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
                        cout<<"删除完成!"<<endl;
                        //开始插入

                        cout<<"set (输入属性名)";
                        cin>>tiaojian1;//属性名
                        tiaojian1str=string(tiaojian1);
                        for(int z=0; z<num; z++)
                        {
                            shuxing=string(name[z]);
                            if(tiaojian1str==shuxing)//没有判断属性是否存在
                            {
                                pos=z;
                                break;
                            }
                        }
                        char value[90];
                        string valuestr;
                        cout<<"=(输入属性值)";
                        int q=0;
                        q=0;
                        cin>>value;
                        valuestr=string(value);
                        int buff_long;
                        buff_long=valuestr.size();
                        string strtmp;
                        for(int j=0; j<length[pos]-buff_long; j++)
                        {
                            strtmp=strtmp+" ";
                        }
                        valuestr=valuestr+strtmp;
                        buff_long = valuestr.copy(value, 90);
                        value[buff_long] = '\0';
                        fstream f5;
                        f5.open(table_name,ios::binary|ios::out|ios::app);
                        for(int h=0; h<n; h++)
                        {
                            for(int z=0; z<pos; z++)//开始
                            {
                                for(int j=0; j<length[z]; j++)
                                {
                                    writefile(result[h][z][j],f5);
                                }

                            }

                            for(int x=0; x<length[pos]; x++)//中间
                            {
                                writefile(value[x],f5);
                            }

                            for(int z=pos+1; z<=num; z++)//最后
                            {
                                for(int j=0; j<length[z]; j++)
                                {
                                    writefile(result[h][z][j],f5);
                                }

                            }
                        }
                        f5.close();
                        cout<<"插入成功"<<endl;
                        return;
                    }
                }
                else
                {
                    //f2.seekg(firstpos-sum,ios::cur);
                }
                f2.seekg(sum,ios::cur);//间隔
            }

            f2.close();
            return ;
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
        return ;
    }

}
