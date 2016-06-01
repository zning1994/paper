#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream.h>
#include <cstring>
#include "create.h"
#include "file_operate.h"
using namespace std;

void  cpy(char to[], char from[])
{
    int  i = 0;
    while (from[i] != '\0')
    {
        to[i] = from[i];
        i++;
    }
    to[i] = '\0';
}
unsigned int len(char str[]) //数组长度
{
    int  i;
    unsigned int len = 0;
    for (i=0; str[i]!='\0'; i++)
    {
        len++;
    }
    return (len);
}
void Create()
{
    fstream fin,ccin,ddin;
    cout<<"CREATE TABLE ";
    char table_create[100];
    char table_create1[100];
    char txt_create[]=".txt";
    cin>>table_create;
    cpy(table_create1,table_create);
    strcat(table_create1,txt_create);
    fin.open(table_create1,ios::binary|ios::in);
    if (fin.is_open()) // 检查文件是否成功打开
    {
        cout << "You already have this table." << endl;
        fin.close();
    }
    else
    {
        fin.close();
        int length = len(table_create);
        table_create1[length]=',';
        ccin.open("model.txt",ios::binary|ios::out|ios::app);
        ddin.open("key.txt",ios::binary|ios::out|ios::app);
        for(int i=0; i<=length; i++)
            writefile(table_create1[i],ccin);
        ccin.close();
        for(int i=0; i<=length; i++)
            writefile(table_create1[i],ddin);
            ddin.close();
        strcat(table_create,txt_create);
        ccin.open(table_create,ios::binary|ios::out);
        ccin.close();
        //以上建立table，并将其写入model中
        cout<<"please input the number of attributes:  ";
        int num;
        cin>>num;
        char tmp[10000];
        cout<<"please input ATTRIBUTE TYPE DIGITS(separated by SPACE)"<<endl;
        for(int o=0; o<(num*3); o++)
        {
            char creat[1000];
            cin>>creat;
            char temp[]=",";
            strcat(tmp,creat);
            strcat(tmp,temp);
        }
        int length_tmp = len(tmp);
        tmp[length_tmp-1]='!';
        ccin.open("model.txt",ios::binary|ios::out|ios::app);
        for(int i=0; i<length_tmp; i++)
            writefile(tmp[i],ccin);
        ccin.close();
        char tttmp[10];
        cout <<"请输入第几个为主键,从1开始"<<endl;
        ddin.open("key.txt",ios::binary|ios::out|ios::app);
        cin>>tttmp;
        tttmp[1]='!';
        for(int i=0; i<2; i++)
            writefile(tttmp[i],ddin);
        ddin.close();
    }
}
