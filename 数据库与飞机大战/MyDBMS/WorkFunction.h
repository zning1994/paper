#ifndef WORKFUNCTION_H_INCLUDED
#define WORKFUNCTION_H_INCLUDED

void createTable(SQL* sql);/*������*/
void insertRecord(SQL *sql);/*�����¼*/
void alterTable (SQL *sql); /*����� ��ɾ����*/
void deleteRecord(SQL *sql);/*ɾ����¼*/
void showTable (string name);/*��ʾ��*/
void dropTable(string name);/*ɾ����*/


#endif // WORKFUNCTION_H_INCLUDED
