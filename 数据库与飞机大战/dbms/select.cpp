#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream.h>
#include <cstring>
#include "file_operate.h"
#include "select.h"
#include "create.h"
using namespace std;

int disnum(char table_name[])
{
    char tp;
    char tmp[200];
    int i=0;
    int num=0;//属性的个数
    int length[100];//每个属性的长度
    tmp[i]=' ';
    string cmpa,cmpb,value;
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

            int nn=1;//读取逗号个数，要读连续两个读取一个int
p:
            tp=readfile(f1);//读取属性个数及每个属性长度
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
            return num;
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
        cout<<"the table does not exist."<<endl;
        f1.close();
        return 0;
    }
}

int* dis(char table_name[])
{
    char tp;
    char tmp[200];
    int i=0;
    int num=0;//属性的个数
    int length[100];//每个属性的长度
    tmp[i]=' ';
    string cmpa,cmpb,value;
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

            int nn=1;//读取逗号个数，要读连续两个读取一个int
p:
            tp=readfile(f1);//读取属性个数及每个属性长度
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
            int *Array=(int*)malloc(sizeof( int )*num);
            for(int u=0; u<num; u++)
                Array[u]=length[u];
            return Array;
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
        cout<<"the table does not exist."<<endl;
        f1.close();
        return 0;
    }
}



void Projection() //投影
{
    int flag=0;
    fstream fead;
    //从model中读取表的信息
    cout <<"(please input)"<<endl;
    cout <<"select  ";
    char lyj[200];
    cin>>lyj;
    cout <<"(please input)"<<endl;
    cout <<"from  ";
    char table[200];
    char table_new[200];
    char txt[]=".txt";
    cin>>table;
    char lyjlyj[1000];
    char lyjlyjlyj[1000];
    char u,oz;
    string ama_3[1000];
    cout<<"请选择是否有where y/n：";
    cin>>u;
    if(u=='y')
    {
        char abc[1000]= {""};
        char abccc[1000]= {};
        cout <<"(please input)"<<endl;
        cout <<"where  ";
        cin>>lyjlyj;
        int ong=len(lyjlyj);
        int y=0,z=0;
        while(lyjlyj[y]!='=')
        {
            abc[y]=lyjlyj[y];
            y++;
        }
        ama_3[0]=string(abc);
        y++;
        while(y!=ong)
        {
            abc[z]=lyjlyj[y];
            y++;
            z++;
        }
        abc[z]='\0';
        ama_3[1]=string(abc);
        cout<<"是否and? y/n"<<endl;
        cin>>oz;
        if(oz=='y')
        {
            flag=1;
            y=0;
            cin>>lyjlyjlyj;
            int ongg=len(lyjlyjlyj);
            while(lyjlyjlyj[y]!='=')
            {
                abccc[y]=lyjlyjlyj[y];
                y++;
            }
            y++;
            ama_3[2]=string(abccc);
            z=0;
            while(y!=ongg)
            {
                abccc[z]=lyjlyjlyj[y];
                y++;
                z++;
            }
            abccc[z]='\0';
            ama_3[3]=string(abccc);
        }
    }
    int compu,comppu;
    string ama_1[1000];
    string ama_2[1000];
    cpy(table_new,table);
    strcat(table,txt);
    char man[100][100]= {""};
    char tp;
    char tmp[20];
    int i = 0;
    int num=0;//属性的个数
    string cmpa,cmpb,value;
    cmpa = string(table_new);
    int length[10];//每个属性的长度
    int ff=0;
    int gg=0;
    fead.open("model.txt",ios::binary|ios::in);//判断是否存在表;
o:
    tmp[i]=readfile(fead);
    i++;
    if(fead.eof()==0)
    {
        while(tmp[i-1]!=',')
        {
            tmp[i]=readfile(fead);
            i++;
        }
        tmp[i-1]='\0';
        cmpb=string(tmp);
        if(cmpa==cmpb)//表名存在
        {

            int nn=1;//读取逗号个数，要读连续两个读取一个int
            man[gg][ff]=readfile(fead);
            ff++;
            fead.seekg(-8,ios::cur);
p:
            tp=readfile(fead);//读取属性个数及每个属性长度
            if(tp!='!')
            {
                while(readfile(fead)!=',')
                {
                    fead.seekg(-8,ios::cur);
                    man[gg][ff]=readfile(fead);
                    ff++;
                }
                ff=0;
                gg++;
                while(nn<=1)
                {
                    tp=readfile(fead);
                    if(tp==',')
                    {
                        nn++;
                    }

                }
                tp=readfile(fead);
                length[num]=(int)tp-48;
                tp=readfile(fead);
                if(tp<='9'&&tp>='0')
                {
                    length[num]=length[num]*10+((int)tp-48);
                    tp=readfile(fead);
                    if(tp<='9'&&tp>='0')
                    {
                        length[num]=length[num]*10+((int)tp-48);
                    }
                    else
                    {
                        fead.seekg(-8,ios::cur);
                    }
                }
                else
                {
                    fead.seekg(-8,ios::cur);
                }
                num++;
                nn=1;
                goto p;
            }
            else
            {
                fead.close();
            }
            for(int h=0; h<num; h++)
            {
                ama_2[h]=string(man[h]);
            }
            char bbc[100][100];
            int lenn=len(lyj);
            int x,y=0;
            for(int j=0; j<lenn; j++)
            {
                if(lyj[j]!=',')
                {
                    bbc[y][x]=lyj[j];
                    x++;
                }
                else
                {
                    x=0;
                    y++;
                }
            }
            for(int h=0; h<=y; h++)
            {
                ama_1[h]=string(bbc[h]);
            }
            int yy[y];
            for(int r=0; r<num; r++)
            {
                if(ama_3[0]==ama_2[r])
                {
                    compu=r;
                    break;
                }
            }
            for(int r=0; r<num; r++)
            {
                if(ama_3[2]==ama_2[r])
                {
                    comppu=r;
                    break;
                }
            }
            for(int u=0; u<=y; u++)
            {
                for(int r=0; r<num; r++)
                {
                    if(ama_1[u]==ama_2[r])
                    {
                        yy[u]=r;
                        break;
                    }
                }
            }

            if(u!='y')
            {
                fstream f2;
                int uuu=0;
                f2.open(table,ios::binary|ios::in);
                while(f2.eof()==0)
                {
                    for(int z=0; z<num; z++)
                    {
                        for(int k=0; k<length[z]; k++)
                        {
                            if(yy[uuu]==z)
                            {
                                cout<<readfile(f2);
                            }
                            else
                                readfile(f2);
                        }
                        if(yy[uuu]==z)
                            uuu++;
                        cout<<"\t";
                    }
                    uuu=0;
                    cout<<endl;
                }
                f2.close();
            }
            else
            {
                fstream f3;
                int uuuu=0;
                char uuuuu[500]= {""};
                string jsj[100];
                f3.open(table,ios::binary|ios::in);
                while(f3.eof()==0)
                {
                    for(int z=0; z<num; z++)
                    {
                        for(int k=0; k<length[z]; k++)
                        {
                            uuuuu[k]=readfile(f3);
                            if(int(uuuuu[k])==32)
                            uuuuu[k]='\0';
                        }
                        uuuuu[length[z]]='\0';
                        jsj[z]=string(uuuuu);
                    }
                    if(flag==0)
                    {
                        if(jsj[compu]==ama_3[1])
                        {
                            for(int i=0; i<num; i++)
                            {
                                if(yy[uuuu]==i)
                                {
                                    cout<<jsj[i];
                                    cout<<"\t";
                                    uuuu++;
                                }
                            }
                        }
                    }
                    else{
                        if((jsj[compu]==ama_3[1])&&(jsj[comppu]==ama_3[3]))
                        {

                            for(int i=0; i<num; i++)
                            {
                                if(yy[uuuu]==i)
                                {
                                    cout<<jsj[i];
                                    cout<<"\t";
                                    uuuu++;
                                }
                            }

                        }
                    }
                    uuuu=0;
                    //cout<<endl;
                }
                f3.close();
            }
            return;
        }
        else
        {
            tp=readfile(fead);
            while(tp!='!')
            {
                tp=readfile(fead);
            }
            i=0;
            goto o;
        }
    }
    else
    {
        cout<<"the table is not exist."<<endl;
        fead.close();
        return;
    }
    fead.close();
}

void equi_join()
{
    cout<<"(please input)  "<<endl;
    cout<<"select  ";
    char join_select[200]= {""};//存储数组
    cin>>join_select;
    cout<<"(please input)  "<<endl;
    cout<<"from  ";
    char join_from[200]= {""};
    cin>>join_from;
    cout<<"(please input)  "<<endl;
    cout<<"where  ";
    char join_where[200]= {""};
    cin>>join_where;
    string join_select_tmp[2000];//转换为字符串
    string join_from_tmp[2000];
    string join_where_tmp[2000];
    fstream fjoin,cjoin;//输入用
    char tmp_select[1000][300];//临时数组
    char tmp_from[1000][300];
    char tmp_where[1000][300];
    int selectlen=len(join_select);
    int s1=0,s2=0,f1=0,f2=0,w1=0,w2=0;
    for (int y=0; y<selectlen; y++)
    {
        if(join_select[y]!=',')
        {
            tmp_select[s1][s2]=join_select[y];
            s2++;
        }
        else
        {
            s1++;
            s2=0;
        }
    }
    int fromlen=len(join_from);
    for (int y=0; y<fromlen; y++)
    {
        if(join_from[y]!=',')
        {
            tmp_from[f1][f2]=join_from[y];
            f2++;
        }
        else
        {
            f1++;
            f2=0;
        }
    }
    int wherelen=len(join_where);
    for (int y=0; y<wherelen; y++)
    {
        if((join_where[y]!='.')&&(join_where[y]!='='))
        {
            tmp_where[w1][w2]=join_where[y];
            w2++;
        }
        else
        {
            w1++;
            w2=0;
        }
    }
    char str[]=".txt";
    for(int y=0; y<=f1; y++)
    {
        join_from_tmp[y]=string(tmp_from[y]);
    }
    int *f,*g,tmpg,tmph;
    tmpg=disnum(tmp_from[0]);
    tmph=disnum(tmp_from[1]);
    f=dis(tmp_from[0]);
    g=dis(tmp_from[1]);
    string tmp1[2000][20];
    string tmp2[2000][20];
    for(int y=0; y<=s1; y++)//将select的数据放入join_select_tmp中
    {
        join_select_tmp[y]=string(tmp_select[y]);
    }
    string time_0211[100],time_0212[100];//存放属性表
    int time1=0,time2=0;
    char tp;
    char tmp[20];
    int i=0;
    int num=0;//属性的个数
    tmp[i]=' ';
    string cmpa,cmpb,value;
    cmpa=string(tmp_from[0]);
    fstream f3;
    f3.open("model.txt",ios::binary|ios::in);//判断是否存在表;
    while(1)
    {
o:
        tmp[i]=readfile(f3);
        i++;
        if(f3.eof()==0)
        {
            while(tmp[i-1]!=',')
            {
                tmp[i]=readfile(f3);
                i++;
            }
            tmp[i-1]='\0';
            cmpb=string(tmp);
            if(cmpa==cmpb)//表名存在
            {
                char tmpp[100];
                int k=1;
                int end=0;
                while(1)
                {
                    tp=readfile(f3);
                    tmpp[k-1]=tp;
                    while(tmpp[k-1]!=','&&tmpp[k-1]!='!')
                    {
                        tmpp[k]=readfile(f3);
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
                        time_0211[time1]=string(tmpp);
                        time1++;
                        k=1;
                    }
                    else if(num==2)
                    {
                        k=1;
                    }
                    else
                    {
                        num=0;
                        k=1;
                        if(end==0)
                        {

                        }
                        else
                        {
                            f3.close();
                            break;
                        }
                    }
                }
                f3.close();
                break;
            }
            else
            {
                tp=readfile(f3);
                while(tp!='!')
                {
                    tp=readfile(f3);
                }
                i=0;
                goto o;
            }
        }
        else
        {
            cout<<"the table does not exist."<<endl;
            f3.close();
            break;
        }
    }
    i=0;
    num=0;
    cmpa=string(tmp_from[1]);
    fstream f4;
    char ttmp[20];
    ttmp[i]=' ';
    f4.open("model.txt",ios::binary|ios::in);//判断是否存在表;
    while(1)
    {
p:
        ttmp[i]=readfile(f4);
        i++;
        if(f4.eof()==0)
        {
            while(ttmp[i-1]!=',')
            {
                ttmp[i]=readfile(f4);
                i++;
            }
            ttmp[i-1]='\0';
            cmpb=string(ttmp);
            if(cmpa==cmpb)//表名存在
            {
                char tmpp[100];
                int k=1;
                int end=0;
                while(1)
                {
                    tp=readfile(f4);
                    tmpp[k-1]=tp;
                    while(tmpp[k-1]!=','&&tmpp[k-1]!='!')
                    {
                        tmpp[k]=readfile(f4);
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
                        time_0212[time2]=string(tmpp);
                        time2++;
                        k=1;
                    }
                    else if(num==2)
                    {
                        k=1;
                    }
                    else
                    {
                        num=0;
                        k=1;
                        if(end==0)
                        {

                        }
                        else
                        {
                            f4.close();
                            break;
                        }
                    }
                }
                f4.close();
                break;
            }
            else
            {
                tp=readfile(f4);
                while(tp!='!')
                {
                    tp=readfile(f4);
                }
                i=0;
                goto p;
            }
        }
        else
        {
            cout<<"the table does not exist."<<endl;
            f4.close();
            break;
        }
    }
    int aaa[20];
    int bbb[20];
    int s11=0,s22=0;
    for(int y=0; y<=s1; y++)
    {
        for(int x=0; x<disnum(tmp_from[0]); x++)
        {
            if(join_select_tmp[y]==time_0211[x])
            {
                aaa[y]=x;
                s11++;
            }
        }
    }
    for(int y=0; y<=s1; y++)
    {
        for(int x=0; x<disnum(tmp_from[1]); x++)
        {
            if(join_select_tmp[y]==time_0212[x])
            {
                bbb[s22]=x;
                s22++;
            }
        }
    }
    for(int y=0; y<=w1; y++)
        join_where_tmp[y]=string(tmp_where[y]);
    int j_328,j_329;
    for(int x=0; x<disnum(tmp_from[0]); x++)
    {
        if(join_where_tmp[1]==time_0211[x])
        {
            j_328=x;
        }
    }
    for(int x=0; x<disnum(tmp_from[1]); x++)
    {
        if(join_where_tmp[3]==time_0212[x])
        {
            j_329=x;
        }
    }
    strcat(tmp_from[0],str);
    fjoin.open(tmp_from[0],ios::binary|ios::in);
    int in=0;
    while(fjoin.eof()==0)
    {

        for(int z=0; z<tmpg; z++)
        {
            char tempp[500]= {""};
            for(int k=0; k<f[z]; k++)
            {
                tempp[k]=readfile(fjoin);
            }
            tmp1[in][z]=string(tempp);
        }
        in++;
    }
    fjoin.close();
    int out=0;
    strcat(tmp_from[1],str);
    cjoin.open(tmp_from[1],ios::binary|ios::in);
    while(cjoin.eof()==0)
    {

        for(int z=0; z<tmph; z++)
        {
            char tempp[500]= {""};
            for(int k=0; k<g[z]; k++)
            {
                tempp[k]=readfile(cjoin);
            }
            tmp2[out][z]=string(tempp);
        }
        out++;
    }
    cjoin.close();
    for(int y=0; y<in-1; y++)
    {
        for(int x=0; x<out-1; x++)
        {
            if(tmp1[y][j_328]==tmp2[x][j_329])
            {
                for(int z=0; z<s11; z++)
                {
                    cout<<tmp1[y][aaa[z]]<<" ";
                }
                for(int o=0; o<s22; o++)
                {
                    cout <<tmp2[x][bbb[o]]<<" ";
                }

                cout<<endl;
            }
        }
    }
}
