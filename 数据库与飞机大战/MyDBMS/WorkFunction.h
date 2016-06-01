#ifndef WORKFUNCTION_H_INCLUDED
#define WORKFUNCTION_H_INCLUDED

void createTable(SQL* sql);/*创建表*/
void insertRecord(SQL *sql);/*插入记录*/
void alterTable (SQL *sql); /*添加列 或删除列*/
void deleteRecord(SQL *sql);/*删除记录*/
void showTable (string name);/*显示表*/
void dropTable(string name);/*删除表*/


#endif // WORKFUNCTION_H_INCLUDED
