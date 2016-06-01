#include "head.h"
#include "Lexer.h"
/*************************
主函数
*************************/
void Select();

int main()
{

    while (cout << "mysql> ")
    {
        Select();

    }
    /*
    char a[1000];
    while (gets(a))
    {
        Lexer *l = new Lexer (a);
        //cout << l->NumDFA()<<endl;
        l->debug();
    }*/


    return 0;
}
