#include "head.h"
#include "Lexer.h"

#ifndef SQL_H
#define SQL_H


class SQL
{
protected:
    bool flag;
    vector<int> type;
    vector<string> sql;  //存输入的指令
public:

    SQL(char *s);
    void ScanWord();
    bool Judge();
    string Get(int i); //得到第i个有效词
    int GetSize();

};

#endif // SQL_H
