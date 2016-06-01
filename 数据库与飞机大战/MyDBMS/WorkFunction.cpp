#include "head.h"
#include "Table.h"
#include "SQL.h"
/*************************
功能函数文件
*************************/

bool hasfile(string name)
{
    string fname = name + FILE_EXTENSION;
    FILE *fp = fopen(fname.c_str(),"rt");
    if(fp == NULL)
    {
        cout<<"Error:The table "<<name<<" isn't exist"<<endl;
        return false;
    }

    fclose(fp);
    return true;
}

void createTable(SQL* sql)
{
    Table *table ;
    string fname = sql->Get(2) + FILE_EXTENSION;
    FILE *fp = fopen(fname.c_str(),"rt");
    if(fp != NULL)
    {
        cout<<"Error:The Table '"<<sql->Get(2)<<"' already exist"<<endl;
        fclose(fp);
        return ;
    }
    else
    {
        table = new Table(sql);
        delete(table);
    }

}

void insertRecord(SQL *sql)
{
    Table *table;
    if(hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->cmInsert(sql);
        delete(table);
    }
    else return;

}
void alterTable (SQL *sql)
{
    Table *table ;
    if (hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->cmAlter(sql);
        delete(table);
    }
    else return ;
}

void deleteRecord(SQL *sql)
{
    Table *table ;
    if (hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->cmDelete(sql);
        delete(table);
    }
    else return ;
}

void showTable (string name)
{
    Table *table;
    if(hasfile(name))
    {
        table = new Table(name);
        table->cmShow();
        delete(table);
    }
    else return;
}
void dropTable(string name)
{
    Table *table;
    string fname = name + FILE_EXTENSION;
    if (hasfile(name))
    {
        string str ="del /Q ";
        str += fname;
        //table = new Table (name);
        system(str.c_str());
    }
    else return ;

}
