#include "head.h"
#include "SQL.h"

#ifndef TABLE_H
#define TABLE_H

class Table
{
public:

	Table();
	Table(SQL *sql);
	Table(string fname);

	void cmSave();
	void cmInsert(SQL *sql);
	void cmAlter(SQL *sql);
	void cmDelete(SQL* sql);
	void cmUpdate(SQL* sql);
	void cmShow();
	void cmDrawLine();
	void cmDrawCol(int i);
protected:
    string name;//����

	int cNum;//���Ը���

	vector<string> cName;//��������

	vector<string> cType;//��������

	vector<int> length;//������󳤶�

	int rNum;//��¼�ĸ���

	vector<string> record;//���м�¼
private:
};

#endif // TABLE_H
