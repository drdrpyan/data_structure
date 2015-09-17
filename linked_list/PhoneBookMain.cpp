#include <iostream>
#include "Chain.h"
#include "PhoneBook.h"
using namespace std;

PhoneBook PB;

int main(void)
{
	cout << "===== 전화번호부 =====" << endl << endl;

	int flag;
	do{
		cout << endl << "1.내용보기 2.번호추가 3.번호삭제 4.종료" << endl;
		do{
			cout << "(1~4) : ";
			cin >> flag;
		}while(flag<0 && flag>5);

		//내용보기
		if(flag==1)
		{
			int flag;
			cout << endl << "1.전체보기 2.(a~z) 3.뒤로" << endl;
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
		//삽입
		else if(flag==2)
		{
			string name;
			string number;
			cout << endl;
			cout << "이름 : ";
			cin >> name;
			cout << "전화번호 : ";
			cin >> number;
			PB.insertData(name,number);
		}
		
		//삭제
		else if(flag==3)
		{
			string name;
			cout << endl;
			cout << "이름 : ";
			cin >> name;
			PB.removePerson(name);
		}
	}while(flag!=4);

	return 0;
}