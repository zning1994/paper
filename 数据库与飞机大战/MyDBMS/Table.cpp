#include "Table.h"

Table::Table()
{
    //ctor
}
Table :: Table(SQL *sql)
{
    if(sql->Get(3)!="(" || sql->Get(-2)!=")")
	{
        cout << sql->Get(-2) << endl;
		cout<<"Syntax Error: In Create Table" <<endl;
		return;
	}//error

	name = sql->Get(2);
	cNum = 0;

	int i = 4;//直接跳过（

	while(true)
	{
		cName.push_back(sql->Get(i++));
		cType.push_back(sql->Get(i++));
		if(sql->Get(i-1) == "varchar" ||sql->Get(i-1) == "char")
		{
			if(sql->Get(i)!="(" || sql->Get(i+2)!=")")
			{
				cout<< "Syntax Error: In Create Table" <<endl;
				return ;
			}
			i=i+3;//越过（）
		}
		cNum++;
		if(sql->Get(i) == ")")
			break;
		else if(sql->Get(i) != ",")
		{
		    cout << sql->Get(i)<<endl;;
			cout<< "Syntax Error: In Create Table" <<endl;
			return ;
		}
		i++;//越过,
	}
	rNum = 0;
	cmSave();
}

Table :: Table(string putInName)
{
    name = putInName;
    string fname = putInName + FILE_EXTENSION;
    FILE *fp = fopen(fname.c_str(),"rt");

	char buffer[100];
	string buf;
	fscanf(fp,"%d",&cNum);
	for(int i = 0; i < cNum;i++)
	{
		fscanf(fp,"%s",buffer);
		buf = buffer;
		cName.push_back(buf);
		fscanf(fp,"%s",buffer);
		buf = buffer;
		cType.push_back(buf);
	}
	fscanf(fp,"%d",&rNum);
	for(int i = 0;i < cNum*rNum; i++)
	{
		fscanf(fp,"%s",buffer);
		record.push_back(buffer);
	}
	fclose(fp);
}

void Table :: cmInsert(SQL *sql)
{
    if(sql->Get(4)!="(" || sql->Get(-2)!=")")
	{

		cout<<"Syntax Error: In insert record" <<endl;
		return;
	}
	int i = 5,count = 0;
	while(true)
	{
		record.push_back(sql->Get(i++));
		count++;
		if(sql->Get(i) == ")")
			break;
		else if(sql->Get(i)!=",")
		{
			cout<< "Syntax Error: In insert record" <<endl;
			return;
		}
		i++; //越过,
	}
	if(count == cNum)
	{
		rNum++;
		cmSave();
	}
	else
	{
		cout<<"Error: The number of values isn't equls to the number of attribute"<<endl;
		return;
	}
}
void Table :: cmAlter(SQL *sql)
{
    string name = sql->Get(4);
    string type = sql->Get(5);
	if (sql -> Get(3) == "add")
	{

	    for(int i = 0; i < cNum; i++)	//判属性重
		{
			if(name == cName[i])
			{
				if(type == cType[i])
				{
					cout<<"The same attribute!"<<endl;
					return ;
				}
			}
			i++;
		}

	    cName.push_back(sql->Get(4));
        cType.push_back(sql->Get(5));
        cNum ++;
        for(int i = 0;i < rNum; i++)//为每一条记录添加属性
			record.insert(record.begin() + i*cNum + cNum - 1, "NULL" );

    }
    else if (sql -> Get(3) == "drop")
    {
        for(int i = 0; i < cNum; i++)
		{
			if(cName[i] == name && cType[i] == type)
			{
				cName.erase(cName.begin() + i);
				cType.erase(cType.begin() + i);
				cNum--;
				for(int j = i; j < cNum*rNum; j += cNum)
				{
				//	cout<<record[mark]<<endl;
					record.erase(record.begin() + j);
				}
				cmSave();
				return ;
			}
		}
		cout<<"Error: The attribute isn't found"<<endl;
    }

    cmSave ();

}
void Table :: cmDelete(SQL* sql)
{
    int mark ;
    bool flag1 ,flag2 ;
    flag1 = flag2 = false;
	for(int i = 0; i < cNum; i++)
	{
		if(cName[i] == sql->Get(4))
		{
			mark = i;
			flag1 = true;
			break;
		}
	}
	if(flag1 == false)
	{
		cout<<"Not found the attribute"<<endl;
		return ;
	}
	for(int i = 0; i < rNum; i++)
	{
		if(record[i*cNum + mark] == sql->Get(6) )//删除当前记录
		{
		    flag2 = true;
			for(int j = 0; j < cNum; j++)
			{
				record.erase(record.begin()+i*cNum);
			}
			rNum--;
			i--;
		}
	}
	if(flag2 == false)
	{
		cout<<"Not found the value"<<endl;
		return ;
	}
	else
	{
		cout<<"Delete record sccess!"<<endl;
		cmSave();
	}


}
void Table :: cmSave()
{
    string fname = name + FILE_EXTENSION;
	FILE *fp = fopen(fname.c_str(),"wt");
	fprintf(fp,"%d \n",cNum);

	for(int i = 0;i < cNum; i++)
	{
		fprintf(fp,"%s ",cName[i].c_str());
		fprintf(fp,"%s ",cType[i].c_str());
	}
	fprintf(fp,"\n");
	fprintf(fp,"%d\n",rNum);
	for(int i = 0; i < rNum; i++)
	{
		for(int j = 0; j < cNum; j++)
		{

            fprintf(fp,"%s ",record[i*cNum+j].c_str());

		}
		fprintf(fp,"\n");
	}
	fclose(fp);

	cout<<"Save success!"<<endl;
}


void Table :: cmDrawLine()
{

	for(int i = 0; i < cNum; i++)
	{
		cout << "+";
		for(int j = 0; j < length[i]; j++)
		{
			cout << "-";
		}
	}
	cout << "+" << endl;

}

void Table :: cmDrawCol(int rowNum)
{

	for(int i = 0; i < cNum; i++)
	{
		cout << "|";
		cout << record[rowNum*cNum+i];

		for(int j = 0; j < length[i] - record[rowNum*cNum+i].length(); j++)
		{
			cout << " ";
		}
	}
	cout << "|" << endl;
}

void Table :: cmShow()
{

	length.clear();
	for(int i = 0; i < cNum; i++)
	{
		length.push_back(cName[i].length());
		for(int j = 0; j < rNum; j++)
		{
			if(length[i] < record[j*cNum+i].length())
				length[i] = record[j*cNum+i].length();
		}

	}
	cmDrawLine();
	for(int i = 0; i < cNum; i++)
	{
		cout << "|";
		cout << cName[i];
	}
	for(int i = 0; i < length[cNum-1] - cName[cNum-1].length(); i++)
	{
		cout << " ";
	}
	cout << "|" << endl;
	for(int i = 0; i < rNum; i++)
	{
		cmDrawLine();
		cmDrawCol( i );
	}
	cmDrawLine();
}
