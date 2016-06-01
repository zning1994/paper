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
    string name;//表名

	int cNum;//属性个数

	vector<string> cName;//属性名称

	vector<string> cType;//属性类型

	vector<int> length;//属性最大长度

	int rNum;//记录的个数

	vector<string> record;//所有记录
private:
};

#endif // TABLE_H
