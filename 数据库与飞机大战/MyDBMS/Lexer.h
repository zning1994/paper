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
    void Tokener();//���Է�����
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
    vector<int> wordType;//0:�ؼ��� 1:��ʾ�� 2:���� 3:�����
    int wordNum;

    bool ans;

};

#endif // LEXER_H
