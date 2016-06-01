#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#define MAX 85

using namespace std;

struct Property  //属性结构体
{
    char property[20]; //属性名
    char type[15];     //属性类型
    char size[20];      //属性的尺寸
    char Constraint[50];     //完整性约束
    int ConType;   //完整性约束的类型
    char Ref_TName[10]; //保存被参照表名
    char Ref_ProNm[10]; //保存所参照的属性
    char data[20][20];  //插入的记录内容
};
struct Table  //表结构体
{
    int number;        //属性个数
    char TableName[20];  //表名
    Property P[10];  //保存属性
    int Datanum;  //插入记录数
};
struct Alter      //保存Alter命令语句的结构体
{
    char Aoperation[10];  //表操作
    char ATname[20];     //表名
    char AA[50];        //操作具体内容
};

struct Insert    //保存Insert命令语句的结构体
{
    char Name[20];   //表名
    char Pro[MAX];    //插入的属性
    char Val[10];      // values
    char ProDate[MAX];  //插入的数据，以“,”隔开
};
struct Inrecord   //保存插入的记录
{
    char Pro[10][20];  //有记录值的属性名
    char Re[10][20];   //记录内容
};
struct Fore_Key
{
    char Ref_Table[10]; /*被参照表名*/
    char Ref_Pro[10];  /*外码*/
    char Pro[10];     /*被参照表中的被参照属性（也是主码）*/
};

/*分离命令*/
void DepartCom(char *CreateT,char *C)
{
    while(*CreateT == ' ')
        *CreateT ++;
    while(*CreateT != ' '&& *CreateT != ';')
    {
        *C = *CreateT;
        *CreateT ++;
        *C ++;
    }
    while(*CreateT == ' ')
        *CreateT ++;
    while(*CreateT != ' ' && *CreateT != ';')
    {
        *C = *CreateT;
        *CreateT ++;
        *C ++;
    }
    *C = '\0';
}

/*保存命令结束时‘)’的位置*/
int des(char *CreateT)
{
    int row,j;
    row = strlen(CreateT);
    j = row - 1;
    while(CreateT[j] != ')')
        j --;
    return j;
}

/*去掉‘(’之前的语句的空白符，同时保存表名*/
void DepartTable(char *CreateT,char *Com ,char *TableName)
{
    while(*CreateT != '\0' && *CreateT != '(')
    {
        if(*CreateT != ' ')
        {
            *Com = *CreateT;
            *Com ++;
        }
        *CreateT ++;
    }
    *Com = '\0';
    //此时完成了去掉空白符操作
    while (*CreateT == ' ')
        CreateT --;
    while (*CreateT != ' ')
        *CreateT --;
    *CreateT ++;
    while (*CreateT != ' ')
    {
        *TableName = *CreateT;
        *TableName ++;
        *CreateT ++;
    }
    *TableName = '/0';
}

/*把命令中的大写转化为小写*/
void change(char *Com)
{
    char temp[MAX];
    int i;
    for (i = 0; Com[i] != '\0'; i++)
    {
        if (Com[i] <= 90 && Com[i] >= 65)
            temp[i] = Com [i] + 32;
        else  temp[i] = Com [i];
    }
    temp[i] = '\0';
    strcpy(Com , temp);
}

/*将输入的属性按','分离并存入一个二维数组中*/
void Cut(char CreateT[MAX][MAX] , char CutPro[MAX][MAX],int i ,int j)
{
    //i和j记录的是')'的位置
    //先找到'('后面的属性记录
    int m1,n1,m2=0,n2=0;
    for (m1 = 0; m1 <= i ; m1 ++)
    {
        n1 = 0;
        while( CreateT[m1][n1] != '(' && CreateT[m1][n1] != '\0')
            n1++;
        if( CreateT[m1][n1] == '(' )
            break;
    }
    /*此时的CreateT[m1][n1]为'('的位置*/
    n1 ++;
    if( CreateT[m1][n1] == '\0')
    {
        m1 ++;
        n1 = 0;
    }
    while ( m1 < i )
    {
        while( n1< strlen(CreateT[m1]))
        {
            CutPro[m2][n2] = CreateT[m1][n1];
            n1 ++;
            n2 ++;
            // if (m1 == i && n1 == j) break;
            if (CreateT[m1][n1] == ',' || CreateT[m1][n1] == '\0')
            {
                //              n1 ++;
                CutPro[m2][n2] = '\0';
                m2 ++;
                n2 = 0;
                break;
            }
        }
        n1 = 0;
        m1 ++;
    }
}

/*分离并把每一行属性信息保存到结构体中*/
void PreProperty(Property Pro[MAX], char CutPro[MAX][MAX],int i)
{
    int ii,j,k;
    // ii为行数
    for (ii = 0; ii < i; ii ++ )
    {
        k = 0;
        j = 0;
        while (CutPro[ii][j] == ' ')
            j++;
        while (CutPro[ii][j] != ' ')
        {
            Pro[ii].property[k] = CutPro[ii][j];
            k++;
            j++;
        }
        Pro[ii].property[k] = '\0'; /*保存属性名*/
        k = 0;
        while (CutPro[ii][j] == ' ')
            j++;
        while (CutPro[ii][j] != ' ' && CutPro[ii][j] != '\0' && CutPro[ii][j] != '(')
        {
            Pro[ii].type[k] = CutPro[ii][j];
            k++;
            j++;
        }
        Pro[ii].type[k] = '\0'; /*保存属性类型*/
        k = 0;
        while (CutPro[ii][j] == ' ')
            j++;
        if (CutPro[ii][j] == '(')
        {
            j ++ ;
            while (CutPro[ii][j] != ')')
            {
                Pro[ii].size[k] = CutPro[ii][j];
                k++;
                j++;
            }
            j ++ ;
        }
        Pro[ii].size[k] = '\0';
        k = 0;
        while (CutPro[ii][j] == ' ')
            j++;
        while (CutPro[ii][j] != '\0')
        {
            Pro[ii].Constraint[k] = CutPro[ii][j];
            k++;
            j++;
        }
        Pro[ii].Constraint[k] = '\0';
    }
}

/*把alter命令分解并保存在结构体中*/
void AlterCom(char CreateT[MAX] , Alter *A)
{
    int k,l=0;
    while(CreateT[l] == ' ')
        l ++;
    while(CreateT[l] != ' ')
        l ++;
    while(CreateT[l] == ' ')
        l ++;
    while(CreateT[l] != ' ')
        l ++;
    /*到这里已经跳过了alter table 语句，开始保存后面的语句*/
    while(CreateT[l] == ' ')
        l ++;
    for(k=0; CreateT[l] != ' '; k++)
    {
        (*A).ATname[k] = CreateT[l];
        l ++;
    }
    (*A).ATname[k]='\0';
    
    while(CreateT[l] == ' ')
        l ++;
    for(k=0; CreateT[l] != ' '; k++)
    {
        (*A).Aoperation[k] = CreateT[l];
        l ++;
    }(*A).Aoperation[k]='\0';
    
    while(CreateT[l] == ' ')
        l ++;
    for(k=0; CreateT[l] != ';'; k++)
    {
        (*A).AA[k] = CreateT[l];
        l ++;
    }(*A).AA[k]='\0';
}

/*把insert命令分解并保存*/
void InsertCom(char CreateT[MAX] , Insert *In)
{
    int k,l=0;
    while(CreateT[l] == ' ')
        l ++;
    while(CreateT[l] != ' ')
        l ++;
    while(CreateT[l] == ' ')
        l ++;
    while(CreateT[l] != ' ')
        l ++;
    /*到这里已经跳过了insert into 语句，开始保存后面的语句*/
    while(CreateT[l] == ' ')
        l ++;
    for(k=0; CreateT[l] != ' '; k++)
    {
        (*In).Name[k] = CreateT[l];
        l ++;
    }
    (*In).Name[k]='\0';  /*保存表名*/
    
    while(CreateT[l] == ' ')
        l ++;
    if (CreateT[l] == '(')
    {
        l ++;
        for(k=0; CreateT[l] != ')'; k++)
        {
            (*In).Pro[k] = CreateT[l];
            l ++;
        }
        (*In).Pro[k]='\0';
        l ++;
    }                    /*保存属性列*/
    
    while(CreateT[l] == ' ')
        l ++;
    for(k=0; CreateT[l] != ' '; k++)
    {
        (*In).Val[k] = CreateT[l];
        l ++;
    }(*In).Val[k]='\0';  /*保存values*/
    
    while(CreateT[l] == ' ' || CreateT[l] == '(')
        l ++;
    for(k=0; CreateT[l] != ')'; k++)
    {
        (*In).ProDate[k] = CreateT[l];
        l ++;
    }(*In).ProDate[k] ='\0';
}

/*分离插入的数据*/
void CutIn(char C[MAX],char D[10][20])
{
    //把C[]中命令分离，存进D[][]数组中
    int m=0,n=0,nn=0;
    while(C[m] != '\0')
    {
        if(C[m] == 39)
            m++;
        while(C[m] != 39&& C[m] != '\0')
        {
            D[n][nn] = C[m];
            nn++;
            m++;
        }
        m ++;
        if(C[m] == ',')
        {
            n++;
            nn=0;
            m++;
        }
    }
}

/*在插入操作中分离属性列*/
void CutInP(char C[MAX],char D[10][20])
{
    //把C[]中命令分离，存进D[][]数组中
    int m=0,n=0,nn=0;
    while(C[m] != '\0')
    {
        while(C[m] != ','&& C[m] != '\0')
        {
            D[n][nn] = C[m];
            nn++;
            m++;
        }
        if(C[m] == ',')
        {
            n++;
            nn=0;
            m++;
        }
    }
}

/*将各个数据类型保存在一个二维字符串数组里*/
void DataType(char DT[10][15])
{
    strcpy(DT[0],"char");
    strcpy(DT[1],"varchar");
    strcpy(DT[2],"int");
    strcpy(DT[3],"smallint");
    strcpy(DT[4],"numeric");
    strcpy(DT[5],"real");
    strcpy(DT[6],"float");
    strcpy(DT[7],"date");
    strcpy(DT[8],"time");
}

/*将各级完整性约束保存在一个二维数组里*/
void ConName(char ConName[6][15])
{
    
    strcpy(ConName[0],"primary key");
    strcpy(ConName[1],"not null");
    strcpy(ConName[2],"unique");
    strcpy(ConName[3],"check");
    //strcpy(ConName[4][0],'\0');
    strcpy(ConName[4],"foreign key");
}

/*处理完整性约束,保存在一个二维数组中*/
void DoCon(Table T , char ConNm[10][50])
{
    int i = 0,j;
    while(i < T.number)
    {
        j = 0;
        while(T.P[i].Constraint[j] != '(' && T.P[i].Constraint[j] != '\0')
        {
            ConNm[i][j] = T.P[i].Constraint[j];
            j++;
        }
        ConNm[i][j] = '\0';
        i++;
    }
    
}

/*判断完整性约束是否合法*/
int JudgeCon(Table *T,char C[10][50],char ConNm[6][15])
{
    /*T用于把完整性约束类型保存入表，C为表内每个属性的完整性约束，ConNm用于对比*/
    int k,m,error=0;
    for (m = 0; m < T->number; m++)
    {
        (*T).P[m].ConType = 6;
        for(k = 0; k < 5; k ++) /*依次与5种完整性约束比较，若符合则将其下表赋值给T->ConType*/
        {
            if(strcmp(C[m],ConNm[k]) == 0)
            {
                (*T).P[m].ConType = k;
                break;
            }/*若全都不符合，则看其完整性约束是否为空*/
            else if(C[m][0] == '\0')
            {
                (*T).P[m].ConType = 5;
                break;
            }
        }
        if ((*T).P[m].ConType == 6)
        {
            cout<<"完整性约束 "<<C[m]<<" 不合法。"<<endl;
            error ++;
        }
    }
    return error;
}
/*外码信息的提取*/
void Ref_Info(Table T,Fore_Key *FK , int TCon)
{
    int i = 0, j = 0;
    /*提取被参照表表名*/
    while(T.P[TCon].Constraint[j] != ' ')
        j ++; /*跳过reference*/
    while(T.P[TCon].Constraint[j] == ' ')
        j ++; /*跳过空格*/
    while(T.P[TCon].Constraint[j] != ' ')
    {
        FK->Ref_Table[i] = T.P[TCon].Constraint[j];
        i ++;
        j ++;
    }/*提取被参照表名*/
    while(T.P[TCon].Constraint[j] == ' ' || T.P[TCon].Constraint[j] == '(')
        j ++; /*跳过空格和(*/
    int ii = 0;
    while(T.P[TCon].Constraint[j] != ')')
    {
        FK->Ref_Pro[ii] = T.P[TCon].Constraint[j];
        ii ++;
        j ++;
    }/*提取被参照表中的被参照属性*/
}

/*判断数据类型是否合法*/
int JudgeType(Table T,char DType[8][15])
{
    int C,k,m,error = 0;
    for (m = 0; m < T.number; m++)
    {
        C=0;
        for(k = 0; k < 9; k ++)
        {
            if(strcmp(T.P[m].type,DType[k]) == 0)
            {
                C = 1;
                break;
            }
        }
        if (C == 0)
        {
            cout<<"数据类型 "<<T.P[m].type<<" 不合法。"<<endl;
            error++;
        }
    }
    return error;
}

/*判断添加的属性是否合法*/
int JudgePro(Table T,char Pro[MAX],int *d)
{
    /*d用来记录相同属性的位置*/
    int judge;
    for (int m = 0; m < T.number-1; m++)
    {
        judge = strcmp(T.P[m].property,Pro);
        if(judge == 0)
        {
            (*d) = m;
            break;
        }
        else continue;
    }
    return judge;  /*judge = 0 则属性在原表中存在；否则不存在*/
}
/*判断删除的属性是否合法*/
int JudgePro2(Table T,char Pro[MAX],int *d)
{
    /*d用来记录相同属性的位置*/
    int judge;
    for (int m = 0; m < T.number; m++)
    {
        judge = strcmp(T.P[m].property,Pro);
        if(judge == 0)
        {
            (*d) = m;
            break;
        }
        else continue;
    }
    return judge;  /*judge = 0 则属性在原表中存在；否则不存在*/
}

/*结构体赋值函数*/
void CopyPro(Property *P1,Property *P2)
{
    strcpy(P1->property,P2->property);
    strcpy(P1->type,P2->type);
    strcpy(P1->size,P2->size);
    strcpy(P1->Constraint,P2->Constraint);
    strcpy(P1->Ref_TName  ,P2->Ref_TName);
    for(int n ; n < 20; n++)
        strcpy(P1->data[n],P2->data[n]);
    P1->ConType = P2->ConType;
}
/*输出已建好的表*/
void output2(Table T)
{
    char CC[5];
    cout<<"是否需要输出当前表的信息？[y/n]"<<endl;
    while(1) //判断是否需要输出已经建好的表
    {
        scanf("%s",CC);
        if(strcmp(CC,"y") == 0)
        {
            printf("TableName：%s\n",T.TableName);
            printf("ProNumeber：%d\n",T.number);
            printf("属性      数据类型  数据长度  完整性约束\n");
            for(int i=0; i<T.number; i++)
            {
                printf("%-10s%-10s%-10s%-30s",T.P[i].property,
                       T.P[i].type,T.P[i].size,T.P[i].Constraint);
                cout<<endl;
            }
            break;
        }
        else if(strcmp(CC,"n") == 0)       break;
        else
        {
            printf("输入命令不合法，请重新输入：\n");
            continue;
        }
    }
    getchar();
}
/*程序是否继续进行*/
void display()
{
    printf("\n是否继续？[y/n]\n");
    char CC[10];
    while(1) //判断是否需要输出已经建好的表
    {
        scanf("%s",CC);
        if(strcmp(CC,"y") == 0)
        {
            getchar();
            system("cls");
            break;
        }
        else if(strcmp(CC,"n") == 0)       exit(0);
        else
        {
            printf("输入命令不合法，请重新输入：\n");
            continue;
        }
    }
}
/*输出当前表的记录*/
void ShowRe(Table Tout)
{
    char CC[20];
    printf("是否显示当前表的记录？[y/n]\n");
    while(1)  //判断是否需要输出已经建好的表
    {
        scanf("%s",CC);
        if(strcmp(CC,"y") == 0)
        {
            for(int i=0; i<Tout.number; i++)
                printf("%-13s",Tout.P[i].property);
            cout<<endl;
            for(int ii=0; ii < Tout.Datanum; ii++)
            {
                for(int j = 0; j < Tout.number; j++)
                    printf("%-13s",Tout.P[j].data[ii]);
                cout<<endl;
            }
            break;
        }
        else if(strcmp(CC,"n") == 0)       break;
        else
        {
            printf("输入命令不合法，请重新输入：\n");
            continue;
        }
    }
}
/*输出主界面*/
void Print()
{
    cout<<"***********************************"<<endl;
    cout<<"        数据库课程设计          "<<endl;
    cout<<"              一个简单的DBMS    "<<endl;
    cout<<"      姓名：胡晓慧              "<<endl;
    cout<<"      专业：计算机12-1班        "<<endl;
    cout<<"                                "<<endl;
    cout<<"    功能：1.create table        "<<endl;
    cout<<"          2.alter table         "<<endl;
    cout<<"          3.insert data         "<<endl;
    cout<<"***********************************"<<endl;
}
/*写文件*/
void WFile(Table Tout)
{
    char Toutname[30];
    FILE *fp2;
    sprintf(Toutname,"%s.txt",Tout.TableName);
    if((fp2=fopen(Toutname,"w"))==NULL)/*打开文件写模式*/
    {
        printf("文件无法正常打开。\n");/*判断文件是否正常打开*/
        exit(0);
    }
    fwrite(&Tout,sizeof(struct Table),1,fp2);
    fclose(fp2);
    printf("操作成功！\n");
}

int main()
{
    
    while(1)
    {
        Print();
        cout<<"请选择：                      "<<endl;
        cout<<"        1.进行表的相关操作        "<<endl;
        cout<<"        2.显示当前已建表的属性    "<<endl;
        cout<<"        3.显示当前已建表的记录内容"<<endl;
        cout<<"        4.退出                    "<<endl;
        cout<<"***********************************"<<endl;
        int  choice;
        cin>>choice;
        if (choice == 4)
            exit(0);
        else if(choice == 2) /*显示当前已建表的属性*/
        {
            char TNa[20];
            cout<<"请输入需要打开的表名："<<endl;
            cin>>TNa;
            FILE *fp2;
            Table RTable;  /*保存被参照表*/
            sprintf(TNa,"%s.txt",TNa);
            if((fp2=fopen(TNa,"rb"))==NULL)/*打开文件读模式*/
            {
                printf("该表不存在。");/*判断文件是否正常打开*/
                display();
                continue;
            }
            fread(&RTable,sizeof(struct Table),1,fp2);
            fclose(fp2);
            output2(RTable);
            display();
        }
        else if(choice == 3)  /*显示当前已建表的记录内容*/
        {
            char TNa[20];
            cout<<"请输入需要显示内容的表名："<<endl;
            cin>>TNa;
            FILE *fp2;
            Table RTable;  /*保存被参照表*/
            sprintf(TNa,"%s.txt",TNa);
            if((fp2=fopen(TNa,"rb"))==NULL)/*打开文件读模式*/
            {
                printf("该表不存在。");/*判断文件是否正常打开*/
                display();
                continue;
            }
            fread(&RTable,sizeof(struct Table),1,fp2);
            fclose(fp2);
            for(int i=0; i<RTable.number; i++)
                printf("%-13s",RTable.P[i].property);
            cout<<endl;
            for(int ii=0; ii < RTable.Datanum; ii++)
            {
                for(int j = 0; j < RTable.number; j++)
                    printf("%-13s",RTable.P[j].data[ii]);
                cout<<endl;
            }
            display();
        }
        else if (choice == 1)  /*进行表的相关操作*/
        {
            Table T;
            char s[MAX][MAX];
            char Com[MAX],C[15],P[MAX][MAX];
            int len,i,j,flag;
            char DType[10][15];
            DataType(DType);/*将各个数据类型赋值到二维字符串数组中*/
            
            cout<<"请输入sql语句,并以“;”结束"<<endl;
            getchar();
            /*输入SQL命令，并存进一个二维数组中*/
            for(i=0; i<10; i++)
            {
                cin.getline(s[i],MAX);
                len = strlen(s[i]);
                s[i][len] = '\0';
                if(strcmp((s[i]+len-1),";")==0)
                    break; /* 当输入";"时结束 */
            }
            /*分离命令并判断命令类型*/
            DepartCom(s[0] , C );
            change(C);
            /*判断是建表命令还是修改表命令*/
            if(strcmp(C,"createtable") == 0) flag = 0;
            else if(strcmp(C,"altertable") == 0) flag = 1;
            else if (strcmp(C,"insertinto") == 0) flag = 3;
            else flag = 2;
            
            /*建表命令*/
            if(flag == 0)
            {
                int c; /*判断数据类型是否合法的标志*/
                DepartTable(s[0] , Com , T.TableName);
                change(Com);
                Cut(s,P,i,j);
                T.number = i-1;
                PreProperty(T.P , P , T.number); /*将命令中的属性分离保存进结构体中*/
                /*判断是否有表级完整性约束*/
                char Pro[10][20];
                int TCon = 100;  /*记录外码语句的位置*/
                for(int m = 0; m < T.number; m ++)
                {
                    strcpy(Pro[m],T.P[m].property); /*把属性名称复制到一个二维数组中*/
                    change(Pro[m]);   /*数组中的属性名称转化为小写*/
                    if(strcmp(Pro[m],"foreign") == 0 && strcmp(T.P[m].type,"key") == 0)
                    {
                        T.P[m].ConType = 4;  /*表级完整性约束_外码*/
                        T.number --;
                        TCon = m;
                    }
                    else if (strcmp(Pro[m],"primary") == 0 && strcmp(T.P[m].type,"key") == 0)
                    {
                        T.P[m].ConType = 0;     /*表级完整性约束_主键*/
                        T.number --;
                        TCon = m;
                    }
                }
                /*处理表级完整性约束*/
                int ff = 0;
                if(TCon != 100)
                {
                    Fore_Key FK;
                    memset(&FK,'\0',sizeof(FK));
                    strcpy(FK.Pro ,T.P[TCon].size);
                    Ref_Info(T,&FK,TCon);
                    
                    /*判断被参照表是否存在*/
                    FILE *fp2;
                    Table Ref_T;  /*保存被参照表*/
                    char Ref_Ta[20];
                    sprintf(Ref_Ta,"%s.txt",FK.Ref_Table);
                    if((fp2=fopen(Ref_Ta,"rb"))==NULL)/*打开文件读模式*/
                    {
                        printf("被参照表不存在。");/*判断文件是否正常打开*/
                        display();
                        continue;
                    }
                    fread(&Ref_T,sizeof(struct Table),1,fp2);
                    fclose(fp2);
                    int m;
                    for (m = 0; m < Ref_T.number; m++)
                    {
                        /*判断外码属性是否存在于被参照表*/
                        if (strcmp(Ref_T.P[m].property,FK.Ref_Pro) == 0)
                        {
                            if(Ref_T.P[m].ConType == 0)  /*判断该属性在被参照表中是否为主码*/
                            {
                                ff = 1;   /*外码合法*/
                                break;
                            }
                            else ff = -1;
                        }
                    }
                    if(ff == -1)
                    {
                        printf("%s属性不能做外码。",FK.Ref_Pro);
                        ff = 2;
                        display();
                        continue;
                    }
                    else if(ff == 0)
                    {
                        printf("%s属性在被参照表中不存在。",FK.Ref_Pro);
                        ff = 2;
                        display();
                        continue;
                    }
                    
                    if(ff == 1)
                    {
                        for(int m = 0; m < T.number; m++)
                            if (strcmp(T.P[m].property,FK.Pro) == 0)
                            {
                                strcpy(T.P[m].Ref_TName,FK.Ref_Table);
                                strcpy(T.P[m].Ref_ProNm,FK.Ref_Pro);
                                T.P[m].ConType = 4;
                                strcpy(T.P[m].Constraint,"foreign key");
                            }
                    }
                }
                
                /*判断完整性约束是否合法*/
                char ConNm[10][50],CName[6][15];
                int error;
                /*ConNm保存表中的完整性约束名*/
                ConName(CName);     /*CName保存所有完整性约束类型*/
                DoCon(T,ConNm);   /*把完整性约束名存入二维数组中*/
                error = JudgeCon(&T,ConNm,CName);  /*判断完整性约束类型*/
                if(error != 0)
                {
                    printf("有 %d 个不合法的完整性约束。\n请重新输入！",error);
                    cout<<endl;
                    display();
                    continue;
                }
                /*判断数据类型是否合法*/
                c = JudgeType(T,DType);
                if(c != 0)
                {
                    printf("有 %d 个不合法的数据类型。\n请重新输入！",c);
                    cout<<endl;
                    display();
                    continue;
                }
                T.Datanum = 0;  /*表中记录数为0*/
                WFile(T);  /*将表存文件*/
                output2(T);
            }
            
            /*修改表命令*/
            else if(flag == 1)
            {
                FILE *fp2;
                Table Tout;
                Alter A;
                char Scom[MAX],Toutname[30];
                int flag2;
                
                strcpy(Scom,s[0]);
                AlterCom(Scom,&A);
                
                /*判断表文件是否存在*/
                sprintf(Toutname,"%s.txt",A.ATname);
                if((fp2=fopen(Toutname,"rb"))==NULL)/*打开文件读模式*/
                {
                    printf("表文件不存在。");/*判断文件是否正常打开*/
                    //cout<<endl;
                    display();
                    continue;
                }
                fread(&Tout,sizeof(struct Table),1,fp2);
                fclose(fp2);
                
                /*判断命令类型*/
                change(A.Aoperation);
                if(strcmp(A.Aoperation,"add")==0) flag2=0;
                else if(strcmp(A.Aoperation,"drop")==0) flag2=1;
                else if(strcmp(A.Aoperation,"modify")==0) flag2=2;
                else flag2 = 3;
                
                /*进入add命令操作*/
                if(flag2 == 0)
                {
                    char fpname[30];
                    char AddPro[0][MAX];
                    strcpy(AddPro[0],A.AA);
                    Tout.number ++;
                    PreProperty(Tout.P+(Tout.number - 1),AddPro,1);
                    
                    /*判断添加的属性是否合法*/
                    int judge,d1;
                    judge = JudgePro(Tout,Tout.P[Tout.number-1].property,&d1);
                    if(judge == 0) /*judge为0，则添加的属性在原表中已经存在*/
                    {
                        printf("添加的属性与表中第 %d 个属性重复。\n",d1+1);
                        memset(&Tout.P[Tout.number-1], '\0', sizeof(Tout.P[Tout.number-1]));
                        Tout.number--;
                        output2(Tout);
                        display();
                        continue;
                    }
                    /*判断添加属性的数据类型是否合法*/
                    int c; /*判断数据类型是否合法的标志*/
                    c = JudgeType(Tout,DType);
                    if(c != 0)
                    {
                        display();
                        continue;
                    }
                    /*将合法的添加操作写入文件*/
                    sprintf(fpname,"%s.txt",Tout.TableName);
                    if((fp2=fopen(fpname,"w"))==NULL)/*打开文件写模式*/
                    {
                        printf("cannot open the file.\n");/*判断文件是否正常打开*/
                        exit(0);
                    }
                    fwrite(&Tout,sizeof(struct Table),1,fp2);
                    fclose(fp2);
                    printf("操作成功！\n");
                    output2(Tout);
                }
                
                /*进入modify命令操作_修改列的数据类型*/
                else if(flag2 == 2)
                {
                    char fpname[30];
                    char ModPro[0][MAX];
                    Property P;
                    strcpy(ModPro[0],A.AA);
                    PreProperty(&P,ModPro,1);
                    /*判断所要修改的属性是否合法*/
                    int judge,d2; /*d2记录所要修改的合法属性在表中的位置*/
                    judge = JudgePro(Tout,P.property,&d2);
                    if(judge != 0)  /*judge不为0则要修改的属性在原表中不存在*/
                    {
                        printf("所要修改的属性不存在。\n");
                        output2(Tout);
                        display();
                        continue;
                    }
                    /*判断修改属性的数据类型是否合法*/
                    int c=0; /*判断数据类型是否合法的标志*/
                    for(int k = 0; k < 9; k ++)
                    {
                        if(strcmp(P.type,DType[k]) == 0)
                        {
                            c = 1;
                            break;
                        }
                    }
                    if (c != 1)
                    {
                        printf("数据类型 %s 不合法。\n",P.type);
                        display();
                        continue;
                    }
                    /*将合法的修改操作写入文件*/
                    strcpy(Tout.P[d2].type,P.type);
                    strcpy(Tout.P[d2].size,P.size);
                    sprintf(fpname,"%s.txt",Tout.TableName);
                    if((fp2=fopen(fpname,"w"))==NULL)/*打开文件写模式*/
                    {
                        printf("cannot open the file.\n");/*判断文件是否正常打开*/
                        exit(0);
                    }
                    fwrite(&Tout,sizeof(struct Table),1,fp2);
                    fclose(fp2);
                    printf("操作成功！\n");
                    output2(Tout);
                }
                
                /*进入drop命令操作_删除一列*/
                else if(flag2 == 1)
                {
                    char fpname[30];
                    char DropPro[0][MAX];
                    Property P;
                    strcpy(DropPro[0],A.AA);
                    PreProperty(&P,DropPro,1);
                    /*判断所要删除的属性是否合法*/
                    int judge,d2; /*d2记录所要删除的合法属性在表中的位置*/
                    judge = JudgePro2(Tout,P.property,&d2);
                    if(judge != 0)  /*judge不为0则要修改的属性在原表中不存在*/
                    {
                        printf("所要删除的属性不存在。\n");
                        output2(Tout);
                        display();
                        continue;
                    }
                    memset(&Tout.P[d2], '\0', sizeof(Tout.P[d2])); /*要删除的属性结构体清空*/
                    for(int k = d2+1; k < Tout.number; k++)  /*把后面的结构体前移*/
                        CopyPro(&(Tout.P[k-1]),&(Tout.P[k]));
                    memset(&Tout.P[Tout.number-1], '\0', sizeof(Tout.P[Tout.number-1])); /*把最后一个结构体清空*/
                    Tout.number --;
                    /*将合法的修改操作写入文件*/
                    sprintf(fpname,"%s.txt",Tout.TableName);
                    if((fp2=fopen(fpname,"w"))==NULL)/*打开文件写模式*/
                    {
                        printf("cannot open the file.\n");/*判断文件是否正常打开*/
                        exit(0);
                    }
                    fwrite(&Tout,sizeof(struct Table),1,fp2);
                    fclose(fp2);
                    printf("操作成功！\n");
                    output2(Tout);
                }
            }
            
            /*插入数据命令*/
            else if (flag == 3)
            {
                FILE *fp2;
                Table Tout;
                Insert In;
                char Scom[MAX],Toutname[30];
                int flag2;
                
                strcpy(Scom,s[0]);
                InsertCom(Scom,&In); /*把表命令分离并保存在Insert结构体中*/
                
                /*判断表文件是否存在并读取文件内容*/
                sprintf(Toutname,"%s.txt",In.Name);
                if((fp2=fopen(Toutname,"rb"))==NULL)/*打开文件读模式*/
                {
                    printf("表文件不存在。");/*判断文件是否正常打开*/
                    display();
                    continue;
                }
                fread(&Tout,sizeof(struct Table),1,fp2);
                fclose(fp2);
                /*判断Insert.Pro[]是否为空*/
                int mark;
                if(In.Pro[0] == '\0') mark = 0; /*mark为0则全部属性均有记录*/
                else mark = 1;     /*mark为1则有属性为空*/
                
                /*判断values值是否合法*/
                change(In.Val);
                if(strcmp(In.Val,"values") != 0)
                {
                    printf("输入的命令不合法。\n");
                    display();
                    continue;
                }
                
                char InD[10][20];
                memset(&InD,'\0',sizeof(InD));
                CutIn(In.ProDate,InD);  /*把插入的记录内容分离并存入InD数组中*/
                Tout.Datanum ++;  /*表中记录的个数增加*/
                
                if(mark == 0)
                {
                    /*此时所有属性都有记录值*/
                    for(int y=0 ; y < Tout.number; y ++)
                        strcpy(Tout.P[y].data[Tout.Datanum-1],InD[y]);
                }
                else
                {
                    /*此时部分属性为空值*/
                    Inrecord IR;
                    CutInP(In.Pro,IR.Pro);    /*将有记录值的属性分离到数组中*/
                    CutIn(In.ProDate,IR.Re);  /*将记录值分离到数组中*/
                    
                    /*将数据写到相应的属性结构体中*/
                    int yy = 0;
                    for(int y = 0; IR.Pro[y][0] != '\0'; y ++)
                    {
                        if(strcmp(IR.Pro[y],Tout.P[yy].property) == 0)
                        {
                            strcpy(Tout.P[yy].data[Tout.Datanum-1],IR.Re[y]);
                            yy ++;
                        }
                        else yy ++;
                    }
                }
                
                /*判断插入的数据是否符合约束条件*/
                int error2 = 0;
                for (int y = 0; y < Tout.number; y ++)  /*插入数据的第y个属性是否满足约束条件*/
                {
                    if (Tout.P[y].ConType == 0)  /*primary key*/
                    {
                        /*非空且值唯一*/
                        if (Tout.P[y].data[Tout.Datanum-1][0] == '\0') /*非空性*/
                        {
                            printf("主键值不能为空！请重新输入。\n");
                            error2 ++;
                            break;
                        }
                        for(int yy = 0; yy < Tout.Datanum-1; yy ++)  /*唯一性——与之前插入的数据比较*/
                        {
                            if(strcmp(Tout.P[y].data[Tout.Datanum-1],Tout.P[y].data[yy]) == 0)
                            {
                                printf("主键值与第%d条记录主键值重复！请重新输入。\n",yy+1);
                                error2 ++;
                                break;
                            }
                        }
                    }
                    else if (Tout.P[y].ConType == 1)  /*not null*/
                    {
                        if (Tout.P[y].data[Tout.Datanum-1][0] == '\0') /*非空性*/
                        {
                            printf("%s属性值不能为空！请重新输入。\n",Tout.P[y].property);
                            error2 ++;
                            break;
                        }
                    }
                    else if (Tout.P[y].ConType == 2)  /*unique*/
                    {
                        for(int yy = 0; yy < Tout.Datanum-1; yy ++)  /*唯一性——与之前插入的数据比较*/
                        {
                            if(strcmp(Tout.P[y].data[Tout.Datanum-1],Tout.P[y].data[yy]) == 0)
                            {
                                printf("%s属性值应唯一！请重新输入。\n",Tout.P[y].property);
                                error2 ++;
                                break;
                            }
                        }
                    }
                    else if (Tout.P[y].ConType == 4)  /*foreign key*/
                    {
                        /*外码为空或者与被参照表中的值相等*/
                        if (Tout.P[y].data[Tout.Datanum-1][0] == '\0') /*可以为空*/
                            break;
                        else  /*判断是否与被参照表中的值相等*/
                        {
                            /*先读取被参照表*/
                            FILE *fp2;
                            Table Ref_T;  /*保存被参照表*/
                            char Ref_Ta[20];
                            memset(Ref_Ta,'\0',sizeof(Ref_Ta));
                            sprintf(Ref_Ta,"%s.txt",Tout.P[y].Ref_TName);
                            if((fp2=fopen(Ref_Ta,"rb"))==NULL)/*打开文件读模式*/
                            {
                                printf("被参照表不存在。\n");/*判断文件是否正常打开*/
                                error2 ++;;
                                continue;
                            }
                            fread(&Ref_T,sizeof(struct Table),1,fp2);
                            fclose(fp2);
                            /*再判断值是否相等*/
                            int judge = 100;
                            for(int m = 0; m < Ref_T.number; m ++) /*找到外码所对应的属性在被参照表中的位置*/
                                if (strcmp(Tout.P[y].Ref_ProNm,Ref_T.P[m].property) == 0)
                                {
                                    judge = m;
                                    break;
                                }
                            if(judge != 100)  /*找到外码在被参照表中的位置*/
                            {
                                int kk = 0;
                                for (int n = 0; n < Ref_T.Datanum; n ++)
                                {
                                    /*依次比较插入记录的值在被参照表中是否存在*/
                                    if(strcmp(Tout.P[y].data[Tout.Datanum-1],Ref_T.P[judge].data[n]) == 0)
                                    {
                                        kk = 1;
                                        break;
                                    }
                                }
                                if(kk == 0)
                                {
                                    cout<<"在被参照表中找不到与插入记录的外码相等的元组！\n"<<endl;
                                    error2 ++;;
                                }
                            }
                            else
                            {
                                cout<<"外码在被参照表中不存在！\n"<<endl;
                                error2 ++;;
                                break;
                            }
                        }
                    }
                    if(error2 != 0)
                        break;
                }
                if(error2 != 0)
                {
                    display();
                    continue;
                }
                /*把插入后的数据写入文件中*/
                WFile(Tout);
                ShowRe(Tout);
                printf("\n此时表中的记录个数为 %d.\n",Tout.Datanum);
            }
            /*输入不合法命令*/
            else if(flag == 2)
            {
                cout<<"输入的命令不合法，请重新输入。";
            }
            display();
        }
    }
    return 0;
}
