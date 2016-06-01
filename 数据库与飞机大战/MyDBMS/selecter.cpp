#include "head.h"
#include "Table.h"
#include "SQL.h"
#include "WorkFunction.h"
/*************************
选择函数文件
*************************/

void Select()
{
    char s[1000];
    gets(s);
    SQL *sql=new SQL(s);
    if (!sql->Judge()) return ;

    if (sql->Get(0) == "create" && sql->Get(1) == "table")
        createTable(sql);//create table s (num int ,name char(10))

    else if(sql->Get(0) == "insert" && sql->Get(1) == "into" && sql->Get(3) == "values")
        insertRecord(sql);//insert into s values ()

    else if (sql->Get(0) == "show")
        showTable(sql->Get(1)); //show s

    else if (sql->Get(0) == "drop" && sql->Get(1) == "table")
        dropTable (sql->Get(2));//drop table s

    else if (sql->Get(0) =="alter" && sql->Get(1) == "table")
        alterTable (sql);//alter table s (add name type)/(drop name type)

    else if (sql->Get(0) =="delete" && sql->Get(1) == "from" && sql->Get(3) == "while")
        deleteRecord(sql);//delete from s while name = name1
    else cout << "The code is error!" << endl;
}
