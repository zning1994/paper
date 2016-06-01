#include "head.h"
#include "Lexer.h"

#ifndef SQL_H
#define SQL_H


class SQL
{
protected:
    bool flag;
    vector<int> type;
    vector<string> sql;  //�������ָ��
public:

    SQL(char *s);
    void ScanWord();
    bool Judge();
    string Get(int i); //�õ���i����Ч��
    int GetSize();

};

#endif // SQL_H
