#include "SQL.h"


SQL :: SQL(char *str)
{


    Lexer *l = new Lexer (str);
    l->lex();

    ScanWord();

}

bool SQL :: Judge()
{
    if (flag) return true;
    else
    {
        cout << "Error: In lexical analysis!" << endl;//�ʷ��������ɹ�
        return false;
    }
}

void SQL :: ScanWord()
{
    int n,type;
    string buf;
    char buffer[100];
    FILE *fp = fopen("lex.out","rt");

    fscanf (fp,"%d",&flag);
    fscanf (fp,"%d",&n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fp,"%s",buffer);
		buf = buffer;
        fscanf(fp,"%d",&type);

        sql.push_back (buf);
        this->type.push_back (type);
    }

    fclose(fp);
}
string SQL :: Get(int i)
{
	if(i >= (int)sql.size())  //size����ֵ��Ϊ����
		return  "";
	else if(i < 0)
		return sql[sql.size() + i];
	else return sql[i];
}

int SQL::GetSize()
{
	return sql.size();
}
