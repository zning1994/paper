#include "Lexer.h"

Lexer::Lexer(char *SQLCode)
{
    sourceCode = SQLCode;
    init();

}

void Lexer :: init()
{
    string a[100] = {"create","table","insert","into","values","drop","show",
                    "alter","delete","from","while","int","double","char"};
    for (int i = 0; i < 13; i++)
        keyWord[i] = a[i];

    len = sourceCode.length ();
    lexmeBeginning = 0;
    index = 0;
    wordNum = 0;
    ans = true;

}


bool Lexer :: isKeyWord(string str)
{
    for (int i = 0; i < 13; i++)
        if (str == keyWord[i])
            return true;

    return false;
}
char Lexer :: nextchar ()
{
    if (index == len) return '#';
    else return sourceCode[index++];
}


bool Lexer :: IdDFA()
{
    int state = 0;
    char ch;
    while (true)
    {
        switch (state)
        {
        case 0:     ch = nextchar();
            if (ch == tab || ch == blank )
            {
                state = 0;
                lexmeBeginning ++;
            }
            else if (isalpha(ch))
            {
                state= 1;
            }
            else
            {
                index = lexmeBeginning;
                state = 3;
            }

            break;
        case 1:     ch = nextchar();
            if (isalnum(ch))
            {
                state = 1;
            }
            else if (ch == '#')
            {
                index --;
                state = 2;
            }
            else
            {
                index -= 2;
                state = 2;
            }

            break;
        case 2:
            return true;
            break;
        case 3:
            return false;
        default :
            return false;

        }
    }

}
bool Lexer :: NumDFA()//占时不支持小数
{
    int state = 0;
    char ch;
    while (true)
    {
        switch (state)
        {
        case 0:     ch = nextchar();
            if (ch == tab || ch == blank )
            {
                state = 0;
                lexmeBeginning ++;
            }
            else if (isdigit(ch)) state = 1;
            else
            {
                index = lexmeBeginning;
                state = 5;
            }
            break;
        case 1:     ch = nextchar();
            if (isdigit(ch)) state = 1;
            else if (ch == '.') state = 2;
            else state = 4;
            break;
        case 2: ch = nextchar();
            if (isdigit(ch)) state = 3;
            else state = 5;

        case 3: ch = nextchar();
            if (isdigit(ch)) state = 3;
            else state = 4;
        case 4:
            index -= 2;
            return true;
            break;
        case 5:
            return false;

        default :
            return false;
        }
    }
}

string Lexer :: GetTheWord()
{
    string a;
    a.assign(sourceCode,lexmeBeginning,index - lexmeBeginning + 1);

    lexmeBeginning = ++index ;
    wordNum ++;
    return a ;
}

void Lexer :: Tokener()
{
    string buf;
    while (index < len)
    {

        if (IdDFA())
        {
            buf = GetTheWord();
            word.push_back(buf);
            wordType.push_back(1);
        }
        else if (NumDFA())
        {
            buf = GetTheWord();
            word.push_back(buf);
            wordType.push_back(2);
        }
        else
        {
            buf = nextchar();
            word.push_back(buf);
            wordType.push_back(3);
            wordNum ++;
            lexmeBeginning++;
        }
    }
}
void Lexer :: WordDeal()
{

    for (int i = 0; i < wordNum; i++)
    {

        if (wordType[i] == 1 && i > 0)
        {
            if (word[i-1] == "'" && word[i+1] == "'")
            {
                string buf = "'" + word[i] +"'";
                word[i] = buf;
                //cout << word[i] << endl;
                word.erase(word.begin() + i+1);
                wordType.erase(wordType.begin() + i+1);

                word.erase(word.begin() + i-1);
                wordType.erase(wordType.begin() + i-1);

                wordNum -= 2;
            }
        }
        if (word[i] == "char" && word[i+1] == "(" && word[i+3] == ")")
        {
            //cout << "a" << endl;
            if (wordType[i+2] == 2)//bug
            {
                string buf = "char(" + word[i+2] +")";
                int t = 4;
                while (t--)
                {
                    word.erase(word.begin() + i);
                    wordType.erase(wordType.begin() + i);
                }

                word.insert(word.begin() + i, buf);
                wordType.insert(wordType.begin() + i, 0);
                wordNum -= 3;
            }
            else ans = false;
        }
        //if ()
    }

    for (int i = 0; i < wordNum; i++)
    {
        if (isKeyWord(word[i]))
        {
            wordType[i] = 0;
        }
    }
    if (wordType[0] != 0)
        ans = false;
    if (word[wordNum-1] != ";")
        ans = false;


}
void Lexer :: lex()
{
    Tokener();
    WordDeal();
    printOut();

}
void Lexer :: printOut()
{
	FILE *fp = fopen("lex.out","wt");
	fprintf (fp,"%d\n",ans);
	fprintf(fp,"%d\n",wordNum);
    for (int i = 0; i < wordNum; i++)
    {
        fprintf(fp,"%s %d\n",word[i].c_str(),wordType[i]);
    }
    fclose(fp);

}

