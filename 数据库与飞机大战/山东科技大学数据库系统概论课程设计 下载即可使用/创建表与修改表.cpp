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
    printf("                             Welcome   to MYSQLϵͳ                          \n");
    printf("                                                                             \n");
    printf("*****************************************************************************\n");
    printf("                                                                             \n");
}
int Input()
{

    char c;
    int i,j;
    printf("������SQL���(����:������help):\n\n");

    for(i = 0; ( c = getch()) != ';';  i++)
    {

        if(c == 27)  //ESC
            exit(0);
        if(c==8)    //�˸�
        {
            i-=2;
            if(i<-1)
                i=-1;
            system("cls");
            Start();
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("������SQL���:\n\n");
            for(j=0; j<=i; j++)
            {
                if(SQL1[j]==13)  //�س�
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
    for(i=0; SQL[i]==' '; i++);  //ȥ����ͷ�Ŀո�
    /*+++++++++++++++++�ж�create++++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"create")!=0)//createд��
    {
        error=0;
        printf("\n�������'create'���������´���!\n");
    }
    else  //create ����
    {
        /*+++++++++++++++++++�ж�table+++++++++++++++++++++++++++++++++++*/
        for(; SQL[i]==' '; i++);//ɾȥ�ո�

        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
        {
            temp[j]=tolower(SQL[i]);
        }
        temp[j]='\0';
        if(strcmp(temp,"table")!=0)//tableд��
        {
            error=0;
            printf("\n�������'table'���������´���!\n");
        }
        else  //table��ȷ
        {
            /*++++++++++++++++++++++++��ȡ����++++++++++++++++++++++++++*/
            for(; SQL[i]==' '; i++);
            for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
            {
                t_Name[j]=SQL[i];
            }

            int _i=0;
            for(_i = 0; _i < j; _i++)
                tableName[number][_i]=t_Name[_i];
            tableName[number][_i] = '\0';
            //+++++++++++++++++++++++��ȡ���ֶΣ��ֶ������ֶ����ͣ��ֶγ��ȣ�Լ��������+++++++++++++++++++++++++
            do
            {
                int f_length=0,flag=1,mark=0;
                /*++++++++++++++++++++��ȡ�ֶ���+++++++++++++++++++++*/
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
                /*++++++++++++++++++++++++��ȡ�ֶ�����+++++++++++++++++++++++++*/
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
                /*++++++++++++�ֶ�������������+++++*/
                if(j==5)
                {
                    error=0;
                    printf("\n��������ֶ���������(�����char,int,float,double,date)�������´���!\n");
                    break;
                }
                else
                {
                    int b;
                    for(  b = 0; temp[b] != '\0'; b++)
                        fieldType[number][num][b] = temp[b];
                    if(f_Type=='C'||f_Type=='F'||f_Type=='B')
                    {
                        //++++++++++++++++++++++++��ȡ�ֶγ���+++++++++++++++++++++++++
                        for(; SQL[i]==' '; i++);
                        for(; SQL[i]!=' '; i++)
                        {
                            if(SQL[i]<48||SQL[i]>58)//�ֶγ��ȱ���������
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
                            printf("\n��������ֶγ������������´���!\n");
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
                    /*++++++++++++++++++++Լ������+++++++++++++++++++*/
                    f_length=0,flag=1;
                    for(; SQL[i]==' '; i++);
                    for(j=0; SQL[i]!=' '&&SQL[i]!=','&&SQL[i]!=';'; i++,j++)
                    {
                        condition[j]=tolower(SQL[i]);
                    }
                    condition[j]='\0';
                    if(condition[0]!=','&&condition[0]!='\0')
                    {
                        /*+++++++++++++++++++�ж�����++++++++++++++++++++*/
                        if(strcmp(condition,"primary")==0)
                        {
                            for(; SQL[i]==' '; i++);
                            for(j=0; SQL[i]!=' '&&SQL[i]!=','; i++,j++) //temp  ��ʱ���key�ַ���
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
                                printf("\n�������'KEY'���������´���!\n");
                                break;
                            }
                        }

                        /*++++++++++++++++++�ж���ֵΨһ+++++++++++++++++++++*/
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
                                printf("\n�������Լ������'NOT NULL'���������´���!\n");
                                break;
                            }
                        }
                        /*++++++++++++++++++Լ����������+++++++++++++++++++++*/
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

                num++;//��һ�ֶ�
            }
            while(SQL[i]!=';');
        }//table��ȷ
    }//create��ȷ
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
    char T;//�ֶ�����
    char temp[LEN],field_name[LEN],f_type[LEN],condition[LEN];
    //  field_name �ֶ��� f_type �ֶ�����
    for(i=0; SQL[i]==' '; i++);
    /*+++++++++++++++++++�ж�alter+++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"alter")!=0)//INSRTд��
    {
        error=0;
        printf("\n�������'alter'��������������SQL���!\n");
    }
    else   //////alter��ȷ//////////////////////////////////////////////////////////////////////
    {
        /*+++++++++++++++++++++�ж�table+++++++++++++++++++++*/
        for(; SQL[i]==' '; i++);
        for(j=0; SQL[i]!=' '; i++,j++)
        {
            temp[j]=tolower(SQL[i]);
        }
        temp[j]='\0';
        if(strcmp(temp,"table")!=0)
        {
            error=0;
            printf("\n�������'table'��������������SQL���!\n");
        }
        else
        {
            /*+++++++++++++++++++++��ȡ����+++++++++++++++++++++*/
            for(; SQL[i]==' '; i++);
            for(j=0; SQL[i]!=' '; i++,j++)
            {
                t_name[j]=SQL[i];
            }
            int _i=0;
            for(_i = 0; _i < j; _i++)
                alterName[_i] = t_name[_i];
            alterName[_i] = '\0';
            /*+++++++++++++++++++++�жϸñ��Ƿ����+++++++++++++++++++++*/
            for( al_num = 0; al_num < number; al_num++)
            {
                if(strcmp(tableName[al_num],alterName) == 0 )

                    break;
            }
            //  printf("%d %d",al_num,number);
            if(al_num == number)
            {
                printf("\n������ı�%s�����ڣ�����������SQL���!\n",t_name);
                error=0;
            }
            else
            {
                for(; SQL[i]==' '; i++);
                /*+++++++++++++++++++++(1)(alter---add)+++++++++++++++++++++++++++*/
                if(tolower(SQL[i])=='a')
                {
                    /*+++++++++++++++++++++�ж�ADD+++++++++++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"add")!=0)
                    {
                        error=0;
                        printf("\n�������'add'��������������SQL���!\n");
                    }
                    else
                    {
                        int f_length=0,flag=1;
                        /*++++++++++++++++++��ȡ��ӵ��ֶ���++++++++++++++++++++*/
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        int a=0;
                        for(  a = 0; field_name[a]!= '\0'; a++)
                            fieldName[al_num][Pro_Num[al_num]][a]= field_name[a];
                        /*+++++++++++++++++++++��ȡ�ֶ�����++++++++++++++*/
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
                        /*++++++++++++�ֶ�������������++++++++++++++++*/
                        if(j==5)
                        {
                            error=0;
                            memset(SQL,0,sizeof(char)*300);
                            printf("\n��������ֶ�������������������SQL���!\n");
                            return 0;
                        }
                        if(T=='C'||T=='F'||T=='B')
                        {
                            //���������char float double ��Ҫ��ȡ�ֶγ��ȣ������int date������Ҫ��ȡ�ֶγ���
                            int b;
                            for(  b = 0; f_type[b] != '\0'; b++)
                                fieldType[al_num][Pro_Num[al_num]][b] = f_type[b];
                            //++++++++++++++++++++++++��ȡ�ֶγ���+++++++++++++++++++++++++
                            for(; SQL[i]==' '; i++);
                            for(; SQL[i]!=' '; i++)
                            {
                                if(SQL[i]<48||SQL[i]>58)//�ֶγ��ȱ���������
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
                                printf("\n��������ֶγ�������(����������)������������SQL���!\n");
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
                        /*++++++++++++++++++++Լ������+++++++++++++++++++*/
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
                            /*+++++++++++++++++++�ж�����++++++++++++++++++++*/
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
                                    printf("\n�������'KEY'��������������SQL���!\n");
                                }
                            }
                            /*++++++++++++++++++�ж���ֵΨһ+++++++++++++++++++++*/
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
                                    printf("\n�������Լ������'NOT NULL'��������������SQL���!\n");
                                }
                            }
                            /*++++++++++++++++++Լ����������+++++++++++++++++++++*/
                            else
                            {
                                error=0;
                                printf("\n�������Լ����������(����PARIMARY KEY,UNIQUE,NOT NULL)������������SQL���!\n");
                            }

                        }//����
                        else
                        {
                            fieldCondition[al_num][Pro_Num[al_num]][0] ='N';
                            fieldCondition[al_num][Pro_Num[al_num]][1] ='U';
                            fieldCondition[al_num][Pro_Num[al_num]][2] ='L';
                            fieldCondition[al_num][Pro_Num[al_num]][3] ='L';
                          //  fieldCondition[al_num][Pro_Num[al_num]][4] ='\0';
                        }
                        Pro_Num[al_num]++;
                    }//add����
                }//if
                /*++++++++++++++++++++++(2)(alter----modify)++++++++++++++++++++++++++++++*/
                else if(tolower(SQL[i])=='m')
                {
                    /*+++++++++++++++++++++��ȡmodify++++++++++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"modify")!=0)//�ж�modify�Ƿ�д��ȷ
                    {
                        error=0;
                        printf("\n�������Լ������'modify'��������������SQL���!\n");
                    }
                    else//modify��ȷ
                    {
                        /*+++++++++++++++��ȡ�ֶ���+++++++++++++*/
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        /*+++++++++++++++�жϸ��ֶ��Ƿ����+++++++++++++*/
                        int al_FN;
                        for( al_FN = 0; al_FN < Pro_Num[al_num] ; al_FN++)
                        {
                            if(strcmp(fieldName[al_num][al_FN],field_name) == 0 )
                                break;
                        }
                        if(al_FN  ==  Pro_Num[al_num])
                        {
                            printf("������Ҫ�޸ĵ�%s�����ڣ�����������SQL���!\n",field_name);
                            error=0;
                        }
                        else
                        {
                            /*+++++++++++++++�ֶ�����+++++++++++++*/
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
                            //++++++++++++�ֶ�������������+++++
                            if(j==5)
                            {
                                error=0;
                                printf("\n��������ֶ�������������������SQL���!\n");
                            }
                            else
                            {
                                int flag=1,f_length=0;
                                if(T=='C'||T=='F'||T=='D')
                                {
                                    fieldType[al_num][al_FN][0] = '\0';   //���ԭ���Ե�����
                                    int b;
                                    for(  b = 0; f_type[b] != '\0'; b++)
                                        fieldType[al_num][al_FN][b] = f_type[b];
                                    //++++++++++++++++++++++++��ȡ�ֶγ���+++++++++++++++++++++++++
                                    for(; SQL[i]==' '; i++);
                                    for(; SQL[i]!=' '; i++)
                                    {
                                        if(SQL[i]<48||SQL[i]>58)//�ֶγ��ȱ���������
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
                                        printf("\n��������ֶγ�������(����������)������������SQL���!\n");
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
                            }//������������
                        }//���Դ���
                    }//modify��ȷ
                }//modify
                /*++++++++++++++++++++++(2)(alter----drop)++++++++++++++++++++++++++++++*/
                else if(tolower(SQL[i])=='d')
                {
                    /*+++++++++++++++��ȡdrop+++++++++++++*/
                    for(j=0; SQL[i]!=' '; i++,j++)
                    {
                        temp[j]=tolower(SQL[i]);
                    }
                    temp[j]='\0';
                    if(strcmp(temp,"drop")!=0)//�ж�drop�Ƿ�д��ȷ
                    {
                        error=0;
                        printf("\n�������Լ������'drop'��������������SQL���!\n");
                    }
                    else//drop��ȷ
                    {
                        for(; SQL[i]==' '; i++);
                        for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
                        {
                            field_name[j]=SQL[i];
                        }
                        field_name[j]='\0';
                        /*+++++++++++++++�жϸ������Ƿ����+++++++++++++*/
                        int al_FN;
                        for( al_FN = 0; al_FN < Pro_Num[al_num] ; al_FN++)
                        {
                            if(strcmp(fieldName[al_num][al_FN],field_name) == 0 )
                                break;
                        }
                        if(al_FN  ==  Pro_Num[al_num])
                        {
                            printf("������Ҫ�޸ĵ�%s�����ڣ�����������SQL���!\n",field_name);
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
                    printf("\n�������alter ��������(add,modify,drop)������������SQL���!\n");
                }
            }//�����
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
    for(i=0; SQL[i]==' '; i++);  //ȥ����ͷ�Ŀո�
    /*+++++++++++++++++�ж�show++++++++++++++++++++++++*/
    for(j=0; SQL[i]!=' '&&SQL[i]!=';'; i++,j++)
    {
        temp[j]=tolower(SQL[i]);
    }
    temp[j]='\0';
    if(strcmp(temp,"show")!=0)//createд��
    {
        printf("\n�������'show'���������´���!\n");
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
    printf("| �γ���Ŀ ��MYSQLϵͳ                                                        |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("| ʹ��˵�� ����ϵͳʵ��SQL���Ĵ������Լ��Ա�����Խ����޸ĵĹ���            |\n");
    printf("|            ͬʱ���Զ�ȡ�ļ��е����ݲ�����                                   |\n");
    printf("|                                                                             |\n");
    printf("| ����ʾ����                                                                  |\n");
    printf("|           <1>create��� �磺CREATE table student                            |\n");
    printf("|                             ( cname char(4) PRIMARY KEY ,                   |\n");
    printf("|                               cno int UNIQUE,                               |\n");
    printf("|                               cpon char(10) NOT NULL,                       |\n");
    printf("|                               grade float                                   |\n");
    printf("|                             );��                                            |\n");
    printf("|           <2>alter ���   �磺                                              |\n");
    printf("|                 alter table student add qw123 char(2)    not null��         |\n");
    printf("|                 alter table student modify qw123 char(3) not null��         |\n");
    printf("|                 alter table student DROP Sname;  ��                         |\n");
    printf("|           <3>show;                                                          |\n");
    printf("|                 ���Բ鿴�Ѵ��ڵı�                                        |\n");
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
        mark=tolower(SQL[i]);// ���ַ�ת����Сд��ĸ,����ĸ�ַ�����������

        switch(mark)
        {
        case 'c':
            if(SQL_CREATE())
            {

                printf("**********************************����ɹ�!**********************************\n");

            }
            else
            {
                printf("**********************************����ʧ��!**********************************\n");
                continue;
            }

            break;

        case 'a':
            if(SQL_ALTER())
            {
                printf("********************************�޸����Գɹ�!*******************************\n");
                //showtable();
            }

            else
            {
                printf("********************************�޸�����ʧ��!*******************************\n");
                continue;
            }
            break;

        case 's':
            if(SQL_SHOW())
                showtable();
            else
            {
                printf("********************************SHOWʧ��!************************************\n");
                continue;
            }
            break;

        case 'h':
            help();
            break;
        default:
            printf("�������,����������!\n");
        }

        printf("�Ƿ��������,��ѡ��(y/n)\n");
        while((order=getchar())=='\n');
        while(getchar()!='\n');
        while(order != 'n' && order != 'y')
        {
            printf("���������,������ѡ��(y/n)\n");
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
