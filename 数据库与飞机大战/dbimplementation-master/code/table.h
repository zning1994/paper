#ifndef TABLE_H
#define TABLE_H
#include "string"
using namespace std;
class table
{
	public:
	table(string DatabaseName="test",string TableName="test");	//���캯��
	void read_schema();											//��ȡģʽ��Ϣ
	int load(const char*filename);								//�ⲿTPH���ɵ��ļ�
	int select(string table_name,string projection);			//����ѡ����
	int insert(string table_name,string tuples);				//����
	int index(string table_name);
	private:
	string table_name;
	string database_name;
};


#endif