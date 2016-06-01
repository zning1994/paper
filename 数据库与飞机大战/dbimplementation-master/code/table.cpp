#include "table.h"
#include "const.h"
#include<iostream>
#include <map>
#include<vector>
#include<fstream>
using namespace std;
/*table�Ĺ��캯��
 * table(string DatabaseName,string TableName)
 * string DatabaseName ���ݿ���
 * string TableName     ����
 * ˼·����Ϊһ�ű�ֻ������һ���ݿ⣬�����ڴ�����ʱ��Ĭ��ѡ�����ݿ�
 * �����������database����Ϊ���࣬������Ϊ���ԭ�򣬸�Ϊdatabase��Ϊȫ�ֱ�������Ϊͬһʱ��ֻ��ѡ��һ�����ݿ⣬Ȼ�����������ݿ�����б���и��ֲ���
 * Ĭ�Ϲ��캯��test���ݿ��test��
 */
table::table(string DatabaseName,string TableName)
{
	this->table_name = TableName;
	this->database_name = DatabaseName;
	//cout<<"����table�Ĺ��캯��\n";
}
/* ��ʾģʽ�ļ�
 * void read_schema()
 * ˼·���򵥵Ķ�ȡ�ļ�
 */
void table::read_schema()
{
	string file= "database/"+this->database_name+"/"+this->table_name+".schema";
	char ch[1024];
	ifstream infile;
	infile.open(file);
	if(infile.is_open())
	{
		//cout<<"show schema "<<file<<endl;
		cout<<"+--------------------------------------------------------+\n";
		cout<<"| Filed	           |     Type         |          Null    |\n";
		cout<<"+--------------------------------------------------------+\n";
		int i=0;
		for(i=0;i<3;i++)
		infile.getline(ch,1022,'#');
		 i =0;
		while(!infile.eof())
		{
			infile.getline(ch,1022,'#');
			cout<<"| ";
			string s = ch;
			if((i+1)%3!=0) // i != 2,5,8  (i+1)%3!=0
			   s.append(17-s.length(),' ');
			
			i++;
			cout<<s;
		}
		cout<<"\n+--------------------------------------------------------+\n";
	}
	else
	{
		string file= "database/"+this->database_name+"/"+this->table_name+".schema";
	    cout<<"\n�ļ�λ�ã�"<<file;
		cout<<"\nNo this table\n";
	}
	infile.close();	
}

/*��ȡTPH�ļ�����������schema��table�ļ�
 * int load(const char *filename)
 * filename  ��Ҫ������ļ�������
 * ���ӣ�load test.txt ����test.txt�ļ���Ȼ������� test.schema��test.table�����ļ�
 * ˼·���ȶ�ȡ��һ�У���Ϊ��ģʽ��Ϣ��������ģʽschema�ļ��У�ʣ�µı��浽table�ļ���
 *       ����������MySQL��MyIsAm����ķ�ʽ����ʵҲ������InnoDB������ֱ�ӽ������ļ���֯��B+���浽�ļ��С�
 * ��չ��û�ܸ����ֶ������Զ�ƥ�䵽���ͣ���Ϊû�����ж�
 */
int table::load(const char *filename)
{
	 char *page=new char[4096];
	 for(int i =0;i<4096;i++)
		 page[i]='0';
	 FILE *fp;
	 //����Ҫװ����ļ�
	 fp=fopen(filename,"r");
	 if(fp==NULL)
	 {
		cout<<"error\n";
		return false;
	 }
	 string file= filename;
	 file = file.substr(0,file.find_first_of("."));
	 string head="#TABLENAME#"+file+"\n";
	 string file2 = "database/"+this->database_name+"/"+file+".schema";
	 const char *name2=file2.c_str();
	 
	 file = "database/"+this->database_name+"/"+file+".table";
	 const char *name=file.c_str();
	
	 //����װ�����ļ���
	 FILE *fp1=fopen(name,"w+b");
	 FILE *fp2=fopen(name2,"w+b");
	 //��ʼ��ҳ�е����ݽṹ
	 PageHeader *page_header=(PageHeader *)page;
	 ////Ԫ������0
	 page_header->tuple_count=0;
	 ////Ԫ����Ϣλ��offset
	 page_header->slot_location=4096;
	 ////��Ԫ��ָ��ָ���һ��λ��
	 char *tuple=page+8;
	 ///���ÿ�������С
	 int free_page_space=4096-8;
	 PageSlot *tuple_info=(PageSlot *)(page+4096);
	 int offset=8;//��һ��Ԫ����ҳ��ƫ��Ϊ8
	 ////��ȡ��һ���ļ�װ��ģʽ��Ϣ
	 fgets(tuple,256,fp);
     int tuplesize=strlen(tuple);
	 ///ת����string������ȽϷ���
	 string tuplehead = tuple;
	 string temp;
	 ////�����whileѭ�������һ��ģʽ��Ϣ��װ��
		int position=0;
		int num=0;
		int temp2;
		////����string�����ú���ѭ������
		while((position=tuplehead.find_first_of("|",position))!=string::npos)  
		{  
		if(num==0)
		{
			
			temp=tuplehead.substr(0,position);
			////����û����TPH�ļ����ж��ֶ����ͣ�Ĭ��ΪVARCHAR
			head = head +"#"+temp+"#"+"VARCHAR(";
			temp =int2str(temp.length());
			head = head +temp+")#NOT NULL\n";
			temp2=position;
		}
		else
		{
			temp=tuplehead.substr(temp2+1,position-temp2-1);
			head = head +"#"+temp+"#"+"VARCHAR(";
			temp =int2str(temp.length());
			head = head +temp+")#NOT NULL\n";
			temp2=position;
		}
			position++;
			num++;
			
		}
		
		temp=tuplehead.substr(temp2+1,tuplehead.length()-tuplehead.find_last_of("|")-2);
		head = head +"#"+temp+"#"+"VARCHAR(";
		temp =int2str(temp.length());
		head = head +temp+")#NOT NULL\n";
		////����ת�����
		///ģʽ�ļ�װ����ϣ�д��sechma�ļ�
		const char*tt = head.c_str();
		fwrite(tt,sizeof(char),strlen(tt),fp2);


	 //��ʼװ���ļ�
	 while(true)
	 {   
		 
		 //��ҳ���㹻�ռ����Ԫ��װ��
		 if(free_page_space>=MAX_TUPLE_SIZE )
		 {
			 //�ļ���û����ĩβ
			 if(fgets(tuple,250,fp)!=NULL)
			 {   
				//��Ԫ�����װ��
				tuple_info--;
				tuple_info->tuple_size=strlen(tuple)+1;//
				tuple_info->tuple_offset=offset;
				offset+=strlen(tuple)+1;
				free_page_space=free_page_space-strlen(tuple)-1-sizeof(PageSlot);
				tuple+=strlen(tuple)+1;//��¼��һ��Ԫ�����ʼ��ַ
				page_header->tuple_count++;
				page_header->slot_location-=sizeof(PageSlot);
			}
			 //�ѵ��ļ�β�˳�ѭ��
			else
			{
				fwrite(page,sizeof(char),4096,fp1);
				break;
			}
		 }
		 //û���㹻�Ŀռ����Ԫ��װ����Ҫ����ҳ�����������ղ���
		 else
		 {   
			 //д����ҳ�����еط�û��ȥ���
			 fwrite(page,sizeof(char),4096,fp1);
			 //�ָ�ҳ�ڵ����ݽṹ��ʼ״̬
			 free_page_space=4096-8;
			 page_header->tuple_count=0;
	         page_header->slot_location=4096;
			 tuple_info=(PageSlot *)(page+4096);
			 offset=8;
			 tuple=page+8;
		 }
	 }
	 //װ�������test�Ĳ��ԣ�ע�⣬���´����ǿ���ʡ�Եģ��������ֻ�����˲���д���Ƿ�ɹ�
	 fseek(fp1,4096*444,0);
	 fread(page,sizeof(char),4096,fp1);
     tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot));  
     page_header=(PageHeader *)page;
	 ///�����load�˶���Ԫ�顣
	 cout<<"Ԫ������"<<page_header->tuple_count<<endl; 
	  for(int i=1;i<=page_header->tuple_count;i++)
	 {
		 tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot)*i);  
		 cout<<page+(tuple_info)->tuple_offset<<endl;
	 }
	 delete []page;
	 page=NULL;
	 fclose(fp);
	 fclose(fp1);
	 fclose(fp2);
	 return true;
	
}
/*ѡ����
 * int table::select(string table_name,string projection)
 * string table_name	����������test
 * string projection    ͶӰ�ֶ��� ����id,name
 * ˼·������ѡ������Ȼ����ͨ�����������������Ľ������ʾ�����ú��������Ӵ�
 * ��չ��ѡ����ʱ�����ޣ�����������Ӧ����ͨ��id�����ж��ζ�ȡ��
 */
int table::select(string table_name,string projection)
{
	///����ʹ��ͶӰ��ѡ��;
	vector<string> touying;
	int all=0;
	////�����select * from test��������ʾ�����ֶ�
	if(projection=="*")
	{
		all=1;
	}
	else
	{
		///����������˵���projection��ͶӰ������ı����ֵ�����Լ���push_back�Ա�֤��ʾ�Լ���Ҫ��ͶӰ�ֶ�
		touying.push_back(projection);
		//touying.push_back("name");
		//cout<<projection<<endl;
		int position=0;
		int num=0;
		int temp2;
		while((position=projection.find_first_of(",",position))!=string::npos)  
		{  
		if(num==0)
		{
			temp2=position;
		}
		else
		{
			
			temp2=position;
		}
			position++;  
			num++;
		}
		
	}
	///����ͶӰ���·�����1.���ж�ȡʲô�ֶΣ�Ȼ����ݳ���ȥȡ��Ҫ��
	///2.�������ڵ�ÿ���ֶζ�ȡ����
	//string xuanze="22";  ////ֻ����һ��ͶӰ�����������Ӧ�����������ĺ�������ѡ��ʱ�䲻��û����

	//1.��ȡ�ñ��ģʽ��Ϣ��
	table_name ="database/"+this->database_name+"/"+table_name+".table";
	const char * name=table_name.c_str();
	char *page=new char[4096];
	FILE *fp1=fopen(name,"r+b");
	 if(fp1 ==NULL)
	 {
		cout<<"�ñ�����";
		return false;
	 }
	 //��ʼ��ҳ�е����ݽṹ
	// char *tuple;
	 PageSlot *tuple_info;
	 fread(page,sizeof(char),4096,fp1);
     tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot));  
     PageHeader * page_header=(PageHeader *)page; 
	 //1.�������ͷ
	 //cout<<"+--------------------------------------------------------+\n";
	 string file= "database/"+this->database_name+"/"+this->table_name+".schema";
	char ch[1024];
	ifstream infile;
	infile.open(file);
	int i=0;
	int j=0;
	unsigned int k=0;
	vector<string>s(30);
	vector<int>ziduan_length(30);
	if(infile.is_open())
	{
		for(i=0;i<3;i++)
			infile.getline(ch,1022,'#');
		i =0;
		
		while(!infile.eof())
		{
			infile.getline(ch,1022,'#');	
			s[i]= ch;
			if((i)%3==0)
			{
				s[i].append(17-s[i].length(),' ');
				if(all ==1)
				{
					touying.push_back(s[i]);
				}
			}
			if((i)%3==1)
			{
				ziduan_length[i/3] =ziduan(s[i]);
			}
			i++;
			
		}


		i /=3;
		for(k=0;k<touying.size();k++)
		{
			touying[k]=touying[k].append(17-touying[k].length(),' ');
		}
		
		cout<<"\n+";
		for(j=0;j<i;j++)
		{
			for(k=0;k<touying.size();k++)
			{
				if(s[j*3]==touying[k])
				cout<<"-------------------";
			}
		}
		cout<<"+\n";
		cout<<"| ";
		for(j=0;j<i*3;j+=3)
		{	
			for(k=0;k<touying.size();k++)
			{
				if(s[j]==touying[k])
				{
					cout<<" "<<s[j]<<"|";
				}
			}
		}
		cout<<"\n+";
		for(j=0;j<i;j++)
		{
			for(k=0;k<touying.size();k++)
			{
				if(s[j*3]==touying[k])
				cout<<"-------------------";
		
			}
		}
		cout<<"+\n";
	}
	 //2.���Ԫ��,������Կ���ͶӰ��ѡ������ֻ���ǵ�ͶӰ����Ϊѡ����Ҫ����ĺ���������������
	string tuple;
	string temp;
	string tempo;
	 for(int t=1;t<=page_header->tuple_count;t++)
	 {
		tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot)*t); 
		tuple=page+(tuple_info)->tuple_offset;

		for(k=0;k<touying.size();k++)
		{
			if(s[0]==touying[k])
			{
				temp = tuple.substr(0,ziduan_length[0]); ///0.5
					cout<<"| "<<temp.append(17-temp.length(),' ');
			}
		}
		int templ=1;
		//cout<<i<<endl;
		for(int zdl=0;zdl<i-1;zdl++)
		{
			for(k=0;k<touying.size();k++)
			{
				if(s[(zdl+1)*3]==touying[k])
				{
				
					templ+=ziduan_length[zdl];
					temp = tuple.substr(templ,ziduan_length[zdl+1]);  /// 6,8 
					
					tempo=temp;

					//if(temp==xuanze)
				//	{
						cout<<"| "<<temp.append(17-temp.length(),' ');
					//}	
				}
			}
		}

		//if(tempo==xuanze)
		//{
			cout<<" |";
		cout<<"\n+";
		for(int j=0;j<i;j++)
		{
			for(k=0;k<touying.size();k++)
			{
				if(s[j*3]==touying[k])
					cout<<"-------------------";
		
			}
		}
		cout<<"+\n";
	//	}
	 }
	 //3.�������
	 cout<<"������Ԫ������"<<page_header->tuple_count<<endl; 
	 return true;
}
/*
 *	���봦��
 *  int insert(string table_name,string tuples)
 *  table_name    �������
 *  tuples        �����Ԫ����
 *  ˼·����ȡ�ļ�֪��������д�룬��ȡoffset Ȼ����д���ļ����м���Ҫ2��I/O
 *  ��չ�����ͬʱ������Ԫ��Ļ�����Ҫ��ε����⺯����Ҳ���Ƕ������������2�η�װ���ɡ�
 *   ����ʹ��multimapʵ�ֶ�����ݵ���֯
 *  �ɻ�: û���ҵ�����ͬʱ�ļ���д��ģʽ��a��ģʽ��׷�ӣ�fseekû��Ч������
 */
int table::insert(string table_name,string tuples)
{
	//0.��������
	string table_name2 ="database/"+this->database_name+"/"+table_name+".table";
	 table_name ="database/"+this->database_name+"/"+table_name+".table";
	const char * name=table_name.c_str();
	char *page=new char[4096];
	FILE *fp1=fopen(name,"r+b");
	
	 if(fp1 ==NULL)
	 {
		cout<<"�ñ�����";
		return false;
	 }
	 //��ʼ��ҳ�е����ݽṹ
	 char *tuple;
	 PageSlot *tuple_info;
	 fread(page,sizeof(char),4096,fp1);
     tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot));  
     PageHeader * page_header=(PageHeader *)page;	 
	 int freeoffset=8;
	 for(int i=1;i<=page_header->tuple_count;i++)
	 {
		 tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot)*i);  
		  freeoffset+=(tuple_info)->tuple_size;

	 }
	 fclose(fp1);
	 
	const char * name2=table_name2.c_str();
	 FILE *fp2=fopen(name2,"w+b");
	 tuple=page+freeoffset;
	strcpy(tuple,tuples.c_str());
	int offset =tuple_info->tuple_offset;
	tuple_info--;
	tuple_info->tuple_size=tuples.length()+1;
	tuple_info->tuple_offset=offset+tuple_info->tuple_size;
	//tuple+=strlen(tuple)+1;//��¼��һ��Ԫ�����ʼ��ַ
	page_header->tuple_count++;
	///����д�ص�����ļ�����
	fwrite(page,sizeof(char),4096,fp2);
	delete []page;
	fclose(fp2);

return true;
}

/* ��������
 * int index(string table_name)
 * string table_name �������
 * ˼·�������ϴ洢��Ԫ�������ֱ��λ�ã�������֤4KB��Ҳ���Ǹպ�һ��I/O��Ȼ����ȥ�����϶�ȡ����һ��I/0��һ��2��I/O
 * ��չ��Ӧ��ʹ��B+����֯����������ʱ�����ޣ�û��ʵ�֣�ֻ�м򵥵�˳��������
 */
int table::index(string table_name)
{
	string tablename ="database/"+this->database_name+"/"+table_name+".table";
	string indexname ="database/"+this->database_name+"/"+table_name+".index";
	const char * iname=indexname.c_str();
	const char * tname=tablename.c_str();
	char *page=new char[4096];
	char *page2=new char[4096];
	FILE *fp1=fopen(iname,"r+b");
	FILE *fp2=fopen(tname,"r+b");
	//���ﹲ������2��I/O
	 if(fp1 ==NULL)
	 {
		cout<<"�ñ�����";
		return false;
	 }
	 //��ʼ��ҳ�е����ݽṹ
	 string tuple;
	 PageSlot *tuple_info;
	 fread(page,sizeof(char),4096,fp1);
	 fread(page2,sizeof(char),4096,fp2);
     tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot));  
     PageHeader * page_header=(PageHeader *)page;	 
	 int offset=8;
	 cout<<"+------------+"<<endl;
	 cout<<"|id   |name  |"<<endl;
	 cout<<"|";
	 for(int i=1;i<=page_header->tuple_count;i++)
	 {
		 tuple_info=(PageSlot *)(page+4096-sizeof(PageSlot)*i);
		  string tuple=page+(tuple_info)->tuple_offset;
		  char buf[10];
			strcpy(buf,tuple.substr(tuple.find("|")+1,tuple.length()-tuple.find("|")).c_str());
			sscanf(buf,"%d",&offset);
		  ////������������������Ӧ��ʹ��B+������֯�ڴ��е�������
		 cout<<page2+offset<<"|";
	 }
	 cout<<"\n+-----------+"<<endl;
	 ///�����ڴ�
	 delete []page;
	 delete []page2;
	 ///�������ָ��
	 page=NULL;
	 page2=NULL;
	 ///�ر��ļ�
	 fclose(fp1);
	 fclose(fp2);
	return 0;
}
