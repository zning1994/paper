#include"string"
#include<fstream>
using namespace std;
///ȥ���ո�ĺ���
string trim(string &s)
{
const string &space =" \f\n\t\r\v" ;
string r=s.erase(s.find_last_not_of(space)+1);
return r.erase(0,r.find_first_not_of(space));
}
//��ʾ�����ĺ���
void print_help()
{
	char ch;
	char*file="readme.txt";
				ifstream infile;
				infile.open(file);

				if(infile.is_open())
				{
	//	cout<<"this is the file :"<<file<<endl;
		while(infile.get(ch))
			cout<<ch;
	}
	infile.close();
}

