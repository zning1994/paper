#include <iostream>
#include <fstream.h>
#include <math.h>
#include "file_operate.h"
#include "display.h"
#include "insert.h"
#include "describe.h"
#include "delete.h"
#include "update.h"
#include "create.h"
#include "select.h"
using namespace std;

int main()
{
    int order;
    while(1)
    {
        cout<<"========================================================="<<endl;
        cout<<"=+++++++++++++++++++�������ݿ����ϵͳ++++++++++++++++++="<<endl;
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"=\t 1��display\t 2��describe\t 3������\t="<<endl;
        cout<<"=\t 4��ɾ��\t 5������\t 6������\t="<<endl;
        cout<<"=\t 0���˳�\t 7����ֵ����\t 8��ͶӰ\t="<<endl;
        cout<<"========================================================="<<endl;
        cout<<"������������ţ�";
        cin>>order;

        switch (order)
        {
        case 1:
            display();
            break;
        case 2:
            describe();
            break;
        case 3:
            insert();
            break;
        case 4:
            Delete();
            break;
        case 5:
            update();
            break;
        case 6:
            Create();
            break;
        case 7:
            equi_join();
            break;
        case 8:
            Projection();
            break;
        case 0:
            cout<<"�ټ�!";
            return 0;
            break;
        }
    }
}
