#include "head.h"

#ifndef LEXER_H
#define LEXER_H

#define tab '\t'
#define blank ' '

class Lexer
{
public:
    Lexer(char *SLCode);
    char nextchar ();
    void init();
    bool isKeyWord(string str);
    bool IdDFA();
    bool NumDFA();
    void Tokener();//线性分析器
    string GetTheWord();
    void WordDeal();
    void printOut();
    void lex();


private:
    int lexmeBeginning,index;
    string sourceCode;
    int len ;

    string keyWord[100];

    vector<string> word;
    vector<int> wordType;//0:关键字 1:标示符 2:数字 3:运算符
    int wordNum;

    bool ans;

};

#endif // LEXER_H
