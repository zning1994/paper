#include <iostream>
#include <fstream.h>
#include <math.h>
using namespace std;
char readfile(fstream &f)//读出一个字符
{
    char i[8],str;
    int k=0,w=0,a=0,b=0,c=0,x;
    for(x=0; x<8; x++)
    {
        i[x]=f.get();
    }
    int j;
    j=atoi(i);
    a=j;
    w=0;
    while(a!=0)
    {
        k=a%10;
        a=a/10;
        c=(int)pow(2,w);
        b=b+k*c;
        w++;
    }
    str=(char)b;
    return str;
}
void writefile(char k,fstream &f)//写一个字符
{

    int i=0;
    char str[10];
    char str2[10];
    i=(int)k;
    itoa(i,str,2);
    int s;
    for(s=0; s<=20; s++)
    {
        if(str[s]=='\0')
            break;
    }
    if(s%4!=0)
        s=4-s%4;
    else
        s=0;
    int c;
    for(c=0; c<s; c++)
    {
        str2[c]='0';
    }
    while(c<=10)
    {
        str2[c]='\0';
        c++;
    }
    strcat(str2,str);
    f<<str2;
}
