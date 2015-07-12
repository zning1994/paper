#include  <iostream>
#include  <fstream>
#include    <conio.h>
#include   <stdlib.h>
#include   <string.h>
#define   MAX  100
#define   LEN  10
using namespace std;

char SQL[MAX],SQL1[MAX];

int    number=0;
int Pro_Num[LEN];
char   tableName[LEN][MAX], fieldName[LEN][LEN][MAX],fieldType[LEN][LEN][MAX],
       f_t_len[LEN][LEN][LEN], fieldCondition[LEN][LEN][MAX];
int al_num;

void Read()
{
    char   mark[MAX][MAX];
    char   string[MAX][MAX];
    char   _condition1[MAX][MAX];
    char   _condition2[MAX][MAX];
    char   _condition3[44][44];
    int i,j;
    fstream ioFile;
    ioFile.open("C:\\Users\\Administrator\\Desktop\\DBMS.txt",ios::in);
    ioFile>>string[number];
    while(!ioFile.eof())
    {
        ioFile>>tableName[number];
        ioFile>>Pro_Num[number];
        for( i=0; i < Pro_Num[number]; i++ )
        {
            ioFile>>fieldName[number][i];
            ioFile>>fieldType[number][i];
            if(strcmp(fieldType[number][i],"char")==0||strcmp(fieldType[number][i],"float")==0||strcmp(fieldType[number][i],"double")==0)
            {
                ioFile>>mark[i];
                f_t_len[number][i][0] = '(';
                f_t_len[number][i][1] = mark[i][1];
                f_t_len[number][i][2] = ')';
                f_t_len[number][i][3] = '\0';
            }
            else
                f_t_len[number][i][0] = '\0';

            ioFile>>_condition1[i];
            if(strcmp(_condition1[i],"primary")==0)
            {
                ioFile>>_condition2[i];
                fieldCondition[number][i][0] ='p';
                fieldCondition[number][i][1] ='r';
                fieldCondition[number][i][2] ='i';
                fieldCondition[number][i][3] ='m';
                fieldCondition[number][i][4] ='a';
                fieldCondition[number][i][5] ='r';
                fieldCondition[number][i][6] ='y';
                fieldCondition[number][i][7] =' ';
                fieldCondition[number][i][8] ='k';
                fieldCondition[number][i][9] ='e';
                fieldCondition[number][i][10] ='y';
                fieldCondition[number][i][11] ='\0';
            }
            else if(strcmp(_condition1[i],"unique")==0)
            {

                fieldCondition[number][i][0]= 'u';
                fieldCondition[number][i][1]= 'n';
                fieldCondition[number][i][2]= 'i';
                fieldCondition[number][i][3]= 'q';
                fieldCondition[number][i][4]= 'u';
                fieldCondition[number][i][5]= 'e';
                fieldCondition[number][i][6]= '\0';
            }
            else if(strcmp(_condition1[i],"not")==0)
            {
                ioFile>>_condition2[i];
                fieldCondition[number][i][0] = 'n';
                fieldCondition[number][i][1] = 'o';
                fieldCondition[number][i][2] = 't';
                fieldCondition[number][i][3] = ' ';
                fieldCondition[number][i][4] = 'n';
                fieldCondition[number][i][5] = 'u';
                fieldCondition[number][i][6] = 'l';
                fieldCondition[number][i][7] = 'l';
                fieldCondition[number][i][8] = '\0';
            }
            else
                strcpy(fieldCondition[number][i],_condition1[i]);
        }
        number++;
    }
    ioFile.close();
}
void Start()
{
    printf("                                                                             \n");
    printf("*****************************************************************************\n");
    printf("                                                                             \n");
    printf("                             Welcome   to MYSQL系统                          \n");
    printf("                                                                             \n");
    printf("*****************************************************************************\n");
    printf("                                                                             \n");
}
int Input()
{

    char c;
    int i,j;
    printf("请输入SQL语句(帮助:请输入help):\n\n");

    for(i = 0; ( c = getch()) != ';';  i++)
    {

        if(c == 27)  //ESC
            exit(0);
        if(c==8)    //退格
        {
            i-=2;
            if(i<-1)
                i=-1;
            system("cls");
            Start();
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("请输入SQL语句:\n\n");
            for(j=0; j<=i; j++)
            {
                if(SQL1[j]==13)  //回车
                {
                    puts("");
                }
                printf("%c",SQL1[j]);
            }
            continue;
        }

        SQL1[i]=c;
        if(c==13)
        {
            puts("");
            SQL[i]=' ';
        }
        else if(c=='('||c==')'||c=='\'')
        {
            printf("%c",c);
            SQL[i]=' ';
        }
        else
        {
            printf("%c",c);
            SQL[i]=c;
        }
    }
    SQL[i]=';';
    SQL[i+1]='\0';
    printf(";");
    puts("");
    return 0;
}
int SQL_CREATE()
{
    int  num = 0;
    char   t_Name[MAX],         f_Name[MAX],        f_Type,              f_condition[MAX];
    char   temp[LEN],condition[MAX];
    char type[5][LEN]= {"char","int","float","double","date"};
    char Type1[5]= {'C','I','F','B','D'};
    int i,j,error=1;
    for(i=0; SQL[i]==' '; i++);  //去除开头的空格
    /*+++++++++++++++++判断create++++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"create")!=0)//create写错
    {
        error=0;
        printf("\n你输入的'create'有误，请重新创建!\n");
    }
    else  //create 对了
    {
        /*+++++++++++++++++++判断table+++++++++++++++++++++++++++++++++++*/
        for(; SQL[i]==' '; i++);//删去空格

        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
        {
            temp[j]=tolower(SQL[i]);
        }
        temp[j]='\0';
        if(strcmp(temp,"table")!=0)//table写错
        {
            error=0;
            printf("\n你输入的'table'有误，请重新创建!\n");
        }
        else  //table正确
        {
            /*++++++++++++++++++++++++提取表名++++++++++++++++++++++++++*/
            for(; SQL[i]==' '; i++);
            for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
            {
                t_Name[j]=SQL[i];
            }

            int _i=0;
            for(_i = 0; _i < j; _i++)
                tableName[number][_i]=t_Name[_i];
            tableName[number][_i] = '\0';
            //+++++++++++++++++++++++提取各字段（字段名，字段类型，字段长度，约束条件）+++++++++++++++++++++++++
            do
            {
                int f_length=0,flag=1,mark=0;
                /*++++++++++++++++++++提取字段名+++++++++++++++++++++*/
                for(; SQL[i]==' '||SQL[i]==','; i++);
                if(SQL[i]==';')
                    break;
                for(j=0; SQL[i]!=' '; i++,j++)
                {
                    f_Name[j]=SQL[i];
                }
                f_Name[j] = '\0';
                int a=0;
                for(  a = 0; f_Name[a] != '\0'; a++)
                    fieldName[number][num][a] = f_Name[a];
                fieldName[number][num][a] = '\0';
                /*++++++++++++++++++++++++提取字段类型+++++++++++++++++++++++++*/
                for(; SQL[i]==' '; i++);
                for(j=0; SQL[i]!=' '&&SQL[i]!=','; i++,j++)
                {
                    temp[j]=tolower(SQL[i]);
                }
                temp[j]='\0';
                for(j=0; j<5; j++)
                {
                    if(strcmp(temp,type[j])==0)
                    {
                        f_Type=Type1[j];

                        break;
                    }
                }
                /*++++++++++++字段类型输入有误+++++*/
                if(j==5)
                {
                    error=0;
                    printf("\n你输入的字段类型有误(务必是char,int,float,double,date)，请重新创建!\n");
                    break;
                }
                else
                {
                    int b;
                    for(  b = 0; temp[b] != '\0'; b++)
                        fieldType[number][num][b] = temp[b];
                    if(f_Type=='C'||f_Type=='F'||f_Type=='B')
                    {
                        //++++++++++++++++++++++++提取字段长度+++++++++++++++++++++++++
                        for(; SQL[i]==' '; i++);
                        for(; SQL[i]!=' '; i++)
                        {
                            if(SQL[i]<48||SQL[i]>58)//字段长度必须是数字
                            {
                                flag=0;
                                break;
                            }
                            else
                            {
                                f_length=f_length*10+(SQL[i]-48);
                            }
                        }
                        if(flag==0)
                        {
                            error=0;
                            printf("\n你输入的字段长度有误，请重新创建!\n");
                            break;
                        }
                        else
                        {
                            f_t_len[number][num][0] = '(';
                            f_t_len[number][num][1] = f_length+48;
                            f_t_len[number][num][2] = ')';
                            f_t_len[number][num][3] ='\0';
                        }
                    }
                    else
                    {

                        f_t_len[number][num][0] ='\0';

                    }
                    /*++++++++++++++++++++约束条件+++++++++++++++++++*/
                    f_length=0,flag=1;
                    for(; SQL[i]==' '; i++);
                    for(j=0; SQL[i]!=' '&&SQL[i]!=','&&SQL[i]!=';'; i++,j++)
                    {
                        condition[j]=tolower(SQL[i]);
                    }
                    condition[j]='\0';
                    if(condition[0]!=','&&condition[0]!='\0')
                    {
                        /*+++++++++++++++++++判断主键++++++++++++++++++++*/
                        if(strcmp(condition,"primary")==0)
                        {
                            for(; SQL[i]==' '; i++);
                            for(j=0; SQL[i]!=' '&&SQL[i]!=','; i++,j++) //temp  暂时存放key字符串
                            {
                                temp[j]=tolower(SQL[i]);
                            }
                            temp[j]='\0';
                            if(strcmp(temp,"key")==0)
                            {
                                fieldCondition[number][num][0] ='p';
                                fieldCondition[number][num][1] ='r';
                                fieldCondition[number][num][2] ='i';
                                fieldCondition[number][num][3] ='m';
                                fieldCondition[number][num][4] ='a';
                                fieldCondition[number][num][5] ='r';
                                fieldCondition[number][num][6] ='y';
                                fieldCondition[number][num][7] =' ';
                                fieldCondition[number][num][8] ='k';
                                fieldCondition[number][num][9] ='e';
                                fieldCondition[number][num][10] ='y';
                                fieldCondition[number][num][11] ='\0';
                                //     num++;

                            }
                            else
                            {
                                error=0;
                                printf("\n你输入的'KEY'有误，请重新创建!\n");
                                break;
                            }
                        }

                        /*++++++++++++++++++判断列值唯一+++++++++++++++++++++*/
                        else if(strcmp(condition,"unique")==0)
                        {

                            fieldCondition[number][num][0]= 'u';
                            fieldCondition[number][num][1]= 'n';
                            fieldCondition[number][num][2]= 'i';
                            fieldCondition[number][num][3]= 'q';
                            fieldCondition[number][num][4]= 'u';
                            fieldCondition[number][num][5]= 'e';
                            fieldCondition[number][num][6]= '\0';
                        }

                        /*++++++++++++++++++NOT NULL+++++++++++++++++++++*/
                        else if(strcmp(condition,"not")==0)
                        {
                            for(; SQL[i]==' '; i++);
                            for(j=0; SQL[i]!=' '&&SQL[i]!=','; i++,j++)
                            {
                                temp[j]=tolower(SQL[i]);
                            }
                            temp[j]='\0';
                            if(strcmp(temp,"null")==0)
                            {
                                fieldCondition[number][num][0] = 'n';
                                fieldCondition[number][num][1] = 'o';
                                fieldCondition[number][num][2] = 't';
                                fieldCondition[number][num][3] = ' ';
                                fieldCondition[number][num][4] = 'n';
                                fieldCondition[number][num][5] = 'u';
                                fieldCondition[number][num][6] = 'l';
                                fieldCondition[number][num][7] = 'l';
                                fieldCondition[number][num][8] = '\0';
                                //     num++;
                            }
                            else
                            {
                                error=0;
                                printf("\n你输入的约束条件'NOT NULL'有误，请重新创建!\n");
                                break;
                            }
                        }
                        /*++++++++++++++++++约束条件错误+++++++++++++++++++++*/
                        else
                        {
                            error=0;

                            break;
                        }
                    }
                    else
                    {
                        fieldCondition[number][num][0] = 'N';
                        fieldCondition[number][num][1] ='U';
                        fieldCondition[number][num][2] ='L';
                        fieldCondition[number][num][3] ='L';
                    }
                }

                num++;//下一字段
            }
            while(SQL[i]!=';');
        }//table正确
    }//create正确
    Pro_Num[number] = num;
    number++;
    return 1;
}
int SQL_ALTER()
{
    char t_name[20];
    char type[5][LEN]= {"char","int","float","double","date"};
    char Type1[5]= {'C','I','F','B','D'};
    char alterName[MAX];
    int i,j,error=1;
    char T;//字段类型
    char temp[LEN],field_name[LEN],f_type[LEN],condition[LEN];
    //  field_name 字段名 f_type 字段类型
    for(i=0; SQL[i]==' '; i++);
    /*+++++++++++++++++++判断alter+++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"alter")!=0)//INSRT写错
    {
        error=0;
        printf("\n你输入的'alter'有误，请重新输入SQL语句!\n");
    }
    else   //////alter正确//////////////////////////////////////////////////////////////////////
    {
        /*+++++++++++++++++++++判断table+++++++++++++++++++++*/
        for(; SQL[i]==' '; i++);
        for(j=0; SQL[i]!=' '; i++,j++)
        {
            temp[j]=tolower(SQL[i]);
        }
        temp[j]='\0';
        if(strcmp(temp,"table")!=0)
        {
            error=0;
            printf("\n你输入的'table'有误，请重新输入SQL语句!\n");
        }
        else
        {
            /*+++++++++++++++++++++提取表名+++++++++++++++++++++*/
            for(; SQL[i]==' '; i++);
            for(j=0; SQL[i]!=' '; i++,j++)
            {
                t_name[j]=SQL[i];
            }
            int _i=0;
            for(_i = 0; _i < j; _i++)
                alterName[_i] = t_name[_i];
            alterName[_i] = '\0';
            /*+++++++++++++++++++++判断该表是否存在+++++++++++++++++++++*/
            for( al_num = 0; al_num < number; al_num++)
            {
                if(strcmp(tableName[al_num],alterName) == 0 )

                    break;
            }
            //  printf("%d %d",al_num,number);
            if(al_num == number)
            {
                printf("\n你输入的表%s不存在，请重新输入SQL语句!\n",t_name);
                error=0;
            }
            else
            {
                for(; SQL[i]==' '; i++);
                /*+++++++++++++++++++++(1)(alter---add)+++++++++++++++++++++++++++*/
                if(tolower(SQL[i])=='a')
                {
                    /*+++++++++++++++++++++判断ADD+++++++++++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"add")!=0)
                    {
                        error=0;
                        printf("\n你输入的'add'有误，请重新输入SQL语句!\n");
                    }
                    else
                    {
                        int f_length=0,flag=1;
                        /*++++++++++++++++++提取添加的字段名++++++++++++++++++++*/
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        int a=0;
                        for(  a = 0; field_name[a]!= '\0'; a++)
                            fieldName[al_num][Pro_Num[al_num]][a]= field_name[a];
                        /*+++++++++++++++++++++提取字段类型++++++++++++++*/
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                        {
                            f_type[j]=tolower(SQL[i]);
                        }
                        f_type[j]='\0';
                        for(j=0; j<5; j++)
                        {
                            if(strcmp(f_type,type[j])==0)
                            {
                                T=Type1[j];
                                break;
                            }
                        }
                        /*++++++++++++字段类型输入有误++++++++++++++++*/
                        if(j==5)
                        {
                            error=0;
                            memset(SQL,0,sizeof(char)*300);
                            printf("\n你输入的字段类型有误，请重新输入SQL语句!\n");
                            return 0;
                        }
                        if(T=='C'||T=='F'||T=='B')
                        {
                            //如果类型是char float double 需要提取字段长度，如果是int date等则不需要提取字段长度
                            int b;
                            for(  b = 0; f_type[b] != '\0'; b++)
                                fieldType[al_num][Pro_Num[al_num]][b] = f_type[b];
                            //++++++++++++++++++++++++提取字段长度+++++++++++++++++++++++++
                            for(; SQL[i]==' '; i++);
                            for(; SQL[i]!=' '; i++)
                            {
                                if(SQL[i]<48||SQL[i]>58)//字段长度必须是数字
                                {
                                    flag=0;
                                    break;
                                }
                                else
                                {
                                    f_length=f_length*10+(SQL[i]-48);
                                }
                            }
                            if(flag==0)
                            {
                                error=0;
                                memset(SQL,0,sizeof(char)*300);
                                printf("\n你输入的字段长度有误(必须是数字)，请重新输入SQL语句!\n");
                                return 0;
                            }
                            else
                            {
                                f_t_len[al_num][Pro_Num[al_num]][0] = '(';
                                f_t_len[al_num][Pro_Num[al_num]][1] = f_length+48;
                                f_t_len[al_num][Pro_Num[al_num]][2] = ')';
                                f_t_len[al_num][Pro_Num[al_num]][3] ='\0';
                            }
                        }
                        else
                        {
                            f_t_len[al_num][Pro_Num[al_num]][0] = '\0';
                        }
                        /*++++++++++++++++++++约束条件+++++++++++++++++++*/
                        /*PARIMARY KEY 1 UNIQUE 2  NOT NULL 3*/
                        f_length=0,flag=1;
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                        {
                            condition[j]=tolower(SQL[i]);
                        }
                        condition[j]='\0';
                        if(condition[0]!=';'&&condition[0]!='\0')
                        {
                            /*+++++++++++++++++++判断主键++++++++++++++++++++*/
                            if(strcmp(condition,"primary")==0)
                            {
                                for(; SQL[i]==' '; i++);
                                for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                                {
                                    temp[j]=tolower(SQL[i]);
                                }
                                temp[j]='\0';
                                if(strcmp(temp,"key")==0)
                                {
                                    fieldCondition[al_num][Pro_Num[al_num]][0]  = 'p';
                                    fieldCondition[al_num][Pro_Num[al_num]][1]  = 'r';
                                    fieldCondition[al_num][Pro_Num[al_num]][2]  = 'i';
                                    fieldCondition[al_num][Pro_Num[al_num]][3]  = 'm';
                                    fieldCondition[al_num][Pro_Num[al_num]][4]  = 'a';
                                    fieldCondition[al_num][Pro_Num[al_num]][5]  = 'r';
                                    fieldCondition[al_num][Pro_Num[al_num]][6]  = 'y';
                                    fieldCondition[al_num][Pro_Num[al_num]][7]  = ' ';
                                    fieldCondition[al_num][Pro_Num[al_num]][8]  = 'k';
                                    fieldCondition[al_num][Pro_Num[al_num]][9]  = 'e';
                                    fieldCondition[al_num][Pro_Num[al_num]][10] = 'y';
                                    fieldCondition[al_num][Pro_Num[al_num]][11] = '\0';
                                }
                                else
                                {
                                    error=0;
                                    printf("\n你输入的'KEY'有误，请重新输入SQL语句!\n");
                                }
                            }
                            /*++++++++++++++++++判断列值唯一+++++++++++++++++++++*/
                            else if(strcmp(condition,"unique")==0)
                            {
                                fieldCondition[al_num][Pro_Num[al_num]][0]  = 'u';
                                fieldCondition[al_num][Pro_Num[al_num]][1]  = 'n';
                                fieldCondition[al_num][Pro_Num[al_num]][2]  = 'i';
                                fieldCondition[al_num][Pro_Num[al_num]][3]  = 'q';
                                fieldCondition[al_num][Pro_Num[al_num]][4]  = 'u';
                                fieldCondition[al_num][Pro_Num[al_num]][5]  = 'e';
                                fieldCondition[al_num][Pro_Num[al_num]][6]  = '\0';
                            }
                            /*++++++++++++++++++NOT NULL+++++++++++++++++++++*/
                            else if(strcmp(condition,"not")==0)
                            {
                                for(; SQL[i]==' '; i++);
                                for(j = 0; SQL[i] != ' ' &&  SQL[i] != ';'; i++,j++)
                                {
                                    condition[j]=tolower(SQL[i]);
                                }
                                condition[j]='\0';
                                if(strcmp(condition,"null")==0)
                                {
                                    fieldCondition[al_num][Pro_Num[al_num]][0]  = 'n';
                                    fieldCondition[al_num][Pro_Num[al_num]][1]  = 'o';
                                    fieldCondition[al_num][Pro_Num[al_num]][2]  = 't';
                                    fieldCondition[al_num][Pro_Num[al_num]][3]  = ' ';
                                    fieldCondition[al_num][Pro_Num[al_num]][4]  = 'n';
                                    fieldCondition[al_num][Pro_Num[al_num]][5]  = 'u';
                                    fieldCondition[al_num][Pro_Num[al_num]][6]  = 'l';
                                    fieldCondition[al_num][Pro_Num[al_num]][7]  = 'l';
                                    fieldCondition[al_num][Pro_Num[al_num]][8]  = '\0';
                                }
                                else
                                {
                                    error=0;
                                    printf("\n你输入的约束条件'NOT NULL'有误，请重新输入SQL语句!\n");
                                }
                            }
                            /*++++++++++++++++++约束条件错误+++++++++++++++++++++*/
                            else
                            {
                                error=0;
                                printf("\n你输入的约束条件有误(必须PARIMARY KEY,UNIQUE,NOT NULL)，请重新输入SQL语句!\n");
                            }

                        }//主键
                        else
                        {
                            fieldCondition[al_num][Pro_Num[al_num]][0] ='N';
                            fieldCondition[al_num][Pro_Num[al_num]][1] ='U';
                            fieldCondition[al_num][Pro_Num[al_num]][2] ='L';
                            fieldCondition[al_num][Pro_Num[al_num]][3] ='L';
                          //  fieldCondition[al_num][Pro_Num[al_num]][4] ='\0';
                        }
                        Pro_Num[al_num]++;
                    }//add无误
                }//if
                /*++++++++++++++++++++++(2)(alter----modify)++++++++++++++++++++++++++++++*/
                else if(tolower(SQL[i])=='m')
                {
                    /*+++++++++++++++++++++提取modify++++++++++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"modify")!=0)//判断modify是否写正确
                    {
                        error=0;
                        printf("\n你输入的约束条件'modify'有误，请重新输入SQL语句!\n");
                    }
                    else//modify正确
                    {
                        /*+++++++++++++++提取字段名+++++++++++++*/
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        /*+++++++++++++++判断该字段是否存在+++++++++++++*/
                        int al_FN;
                        for( al_FN = 0; al_FN < Pro_Num[al_num] ; al_FN++)
                        {
                            if(strcmp(fieldName[al_num][al_FN],field_name) == 0 )
                                break;
                        }
                        if(al_FN  ==  Pro_Num[al_num])
                        {
                            printf("你输入要修改的%s不存在，请重新输入SQL语句!\n",field_name);
                            error=0;
                        }
                        else
                        {
                            /*+++++++++++++++字段类型+++++++++++++*/
                            for(; SQL[i]==' '; i++);
                            for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                            {
                                f_type[j]=tolower(SQL[i]);
                            }
                            f_type[j]='\0';
                            for(j=0; j<5; j++)
                            {
                                if(strcmp(f_type,type[j])==0)
                                {
                                    T=Type1[j];
                                    break;
                                }
                            }
                            //++++++++++++字段类型输入有误+++++
                            if(j==5)
                            {
                                error=0;
                                printf("\n你输入的字段类型有误，请重新输入SQL语句!\n");
                            }
                            else
                            {
                                int flag=1,f_length=0;
                                if(T=='C'||T=='F'||T=='D')
                                {
                                    fieldType[al_num][al_FN][0] = '\0';   //清空原属性的类型
                                    int b;
                                    for(  b = 0; f_type[b] != '\0'; b++)
                                        fieldType[al_num][al_FN][b] = f_type[b];
                                    //++++++++++++++++++++++++提取字段长度+++++++++++++++++++++++++
                                    for(; SQL[i]==' '; i++);
                                    for(; SQL[i]!=' '; i++)
                                    {
                                        if(SQL[i]<48||SQL[i]>58)//字段长度必须是数字
                                        {
                                            flag=0;
                                            break;
                                        }
                                        else
                                        {
                                            f_length=f_length*10+(SQL[i]-48);
                                        }
                                    }
                                    if(flag==0)
                                    {
                                        error=0;
                                        printf("\n你输入的字段长度有误(必须是数字)，请重新输入SQL语句!\n");
                                    }
                                    else
                                    {

                                        f_t_len[al_num][al_FN][0] = '(';
                                        f_t_len[al_num][al_FN][1] = f_length+48;
                                        f_t_len[al_num][al_FN][2] = ')';
                                        f_t_len[al_num][al_FN][3] ='\0';

                                    }
                                }
                                else
                                {
                                    f_t_len[al_num][al_FN][0] ='\0';
                                }
                            }//属性类型无误
                        }//属性存在
                    }//modify正确
                }//modify
                /*++++++++++++++++++++++(2)(alter----drop)++++++++++++++++++++++++++++++*/
                else if(tolower(SQL[i])=='d')
                {
                    /*+++++++++++++++提取drop+++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"drop")!=0)//判断drop是否写正确
                    {
                        error=0;
                        printf("\n你输入的约束条件'drop'有误，请重新输入SQL语句!\n");
                    }
                    else//drop正确
                    {
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        /*+++++++++++++++判断该属性是否存在+++++++++++++*/
                        int al_FN;
                        for( al_FN = 0; al_FN < Pro_Num[al_num] ; al_FN++)
                        {
                            if(strcmp(fieldName[al_num][al_FN],field_name) == 0 )
                                break;
                        }
                        if(al_FN  ==  Pro_Num[al_num])
                        {
                            printf("你输入要修改的%s不存在，请重新输入SQL语句!\n",field_name);
                            error=0;
                        }
                        else
                        {
                            fieldCondition[al_num][al_FN][0]  = 'N';
                            fieldCondition[al_num][al_FN][1]  = 'U';
                            fieldCondition[al_num][al_FN][2]  = 'L';
                            fieldCondition[al_num][al_FN][3]  = 'L';
                            fieldCondition[al_num][al_FN][4]  = '\0';
                        }
                    }
                }
                else
                {
                    error=0;
                    printf("\n你输入的alter 类型有误(add,modify,drop)，请重新输入SQL语句!\n");
                }
            }//表存在
        }//table else
    }//alter else
    if(error==0)
    {
        return 0;
    }
    return 1;
}
int SQL_SHOW()
{
    char   temp[LEN];
    int i,j;
    for(i=0; SQL[i]==' '; i++);  //去除开头的空格
    /*+++++++++++++++++判断show++++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"show")!=0)//create写错
    {
        printf("\n你输入的'show'有误，请重新创建!\n");
        return 0;
    }
    return 1;
}
int showtable()
{
    int l,k;
    printf("********************************************************\n");
    printf("----------\n");
    for(l = 0; l < number; l++)
    {
        printf("%s\n",tableName[l]);
        for(k = 0; k < Pro_Num[l]; k++)
        {
            //printf("%s  %s%s   %s\n",fieldName[l][k],fieldType[l][k], f_t_len[l][k],fieldCondition[l][k]);
            printf("%s  %s%s",fieldName[l][k],fieldType[l][k], f_t_len[l][k]);
            if(strcmp(fieldCondition[l][k],"NULL") != 0)
                printf("  %s\n",fieldCondition[l][k]);
            else
                printf("\n");
        }
        printf("----------\n");
    }
    printf("********************************************************\n");
}
void help()
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("| 课程题目 ：MYSQL系统                                                        |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("| 使用说明 ：该系统实现SQL语句的创建表以及对表的属性进行修改的功能            |\n");
    printf("|            同时可以读取文件中的数据并保存                                   |\n");
    printf("|                                                                             |\n");
    printf("| 输入示例：                                                                  |\n");
    printf("|           <1>create语句 如：CREATE table student                            |\n");
    printf("|                             ( cname char(4) PRIMARY KEY ,                   |\n");
    printf("|                               cno int UNIQUE,                               |\n");
    printf("|                               cpon char(10) NOT NULL,                       |\n");
    printf("|                               grade float                                   |\n");
    printf("|                             );等                                            |\n");
    printf("|           <2>alter 语句   如：                                              |\n");
    printf("|                 alter table student add qw123 char(2)    not null；         |\n");
    printf("|                 alter table student modify qw123 char(3) not null；         |\n");
    printf("|                 alter table student DROP Sname;  等                         |\n");
    printf("|           <3>show;                                                          |\n");
    printf("|                 可以查看已存在的表。                                        |\n");
    printf("|                                                                             |\n");
    printf("+-----------------------------------------------------------------------------+\n");
}
int main()
{
    int j;
    char mark;
    char t_name[40];
    fstream oFile;
    Read();
    Start();
    while(1)
    {
        int i;
        char order;
        Input();

        for(i=0; SQL[i]==' '; i++);
        mark=tolower(SQL[i]);// 把字符转换成小写字母,非字母字符不做出处理

        switch(mark)
        {
        case 'c':
            if(SQL_CREATE())
            {

                printf("**********************************建表成功!**********************************\n");

            }
            else
            {
                printf("**********************************建表失败!**********************************\n");
                continue;
            }

            break;

        case 'a':
            if(SQL_ALTER())
            {
                printf("********************************修改属性成功!*******************************\n");
                //showtable();
            }

            else
            {
                printf("********************************修改属性失败!*******************************\n");
                continue;
            }
            break;

        case 's':
            if(SQL_SHOW())
                showtable();
            else
            {
                printf("********************************SHOW失败!************************************\n");
                continue;
            }
            break;

        case 'h':
            help();
            break;
        default:
            printf("输入错误,请重新输入!\n");
        }

        printf("是否继续操作,请选择(y/n)\n");
        while((order=getchar())=='\n');
        while(getchar()!='\n');
        while(order != 'n' && order != 'y')
        {
            printf("你输入错误,请重新选择(y/n)\n");
            while((order=getchar())=='\n');
            while(getchar()!='\n');
        }
        if(order=='n')
        {
            fstream oFile;
            oFile.open("C:\\Users\\Administrator\\Desktop\\DBMS.txt",ios::trunc);
            oFile.open("C:\\Users\\Administrator\\Desktop\\DBMS.txt",ios::out);
            int l,k;
            oFile<<"table"<<endl;
            for(l = 0; l < number ; l++)

            {
                oFile<<endl;
                oFile<<tableName[l]<<" ";
                oFile<<Pro_Num[l]<<endl;
                for(k = 0; k < Pro_Num[l]-1; k++)
                {

                    oFile<<fieldName[l][k]<<" "<<fieldType[l][k]<<" "<<f_t_len[l][k]<<" "<<fieldCondition[l][k]<<endl;
                }
                oFile<<fieldName[l][k]<<" "<<fieldType[l][k]<<" "<<f_t_len[l][k]<<" "<<fieldCondition[l][k];
            }

            oFile.close();

            break;
        }
    }
}
