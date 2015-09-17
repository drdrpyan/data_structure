#include <iostream>
#include "Chain.h"
#include "PhoneBook.h"
using namespace std;

PhoneBook PB;

int main(void)
{
	cout << "===== ��ȭ��ȣ�� =====" << endl << endl;

	int flag;
	do{
		cout << endl << "1.���뺸�� 2.��ȣ�߰� 3.��ȣ���� 4.����" << endl;
		do{
			cout << "(1~4) : ";
			cin >> flag;
		}while(flag<0 && flag>5);

		//���뺸��
		if(flag==1)
		{
			int flag;
			cout << endl << "1.��ü���� 2.(a~z) 3.�ڷ�" << endl;
			do{
				cout << "(1~3) : ";
				cin >> flag;
			}while(flag<0 && flag>4);

			if(flag==1)
			{
				cout << endl;
				PB.printData();
			}
			else if(flag==2)
			{
				char C;
				do{
					cout << "(a~z) : ";
					cin >> C;
				}while(C<'a' && C>'z');
				cout << endl;
				PB.printData(C);
			}
		}
		//����
		else if(flag==2)
		{
			string name;
			string number;
			cout << endl;
			cout << "�̸� : ";
			cin >> name;
			cout << "��ȭ��ȣ : ";
			cin >> number;
			PB.insertData(name,number);
		}
		
		//����
		else if(flag==3)
		{
			string name;
			cout << endl;
			cout << "�̸� : ";
			cin >> name;
			PB.removePerson(name);
		}
	}while(flag!=4);

	return 0;
}