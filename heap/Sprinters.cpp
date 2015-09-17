#include "MinHeap.h"
#include <iostream>
#include <string>
//using std::cout;
//using std::cin;
//using std::endl;
//using std::string;
using namespace std;

struct SprinterRecord
{
	string name;
	double time;
	void init()
	{
		char buffer[40];
		cout << "Name : ";
		fflush(stdin);
		getline(cin,name);
		cout << "Record(X.XX sec) : ";
		cin >> time;
	}
	bool operator>(const SprinterRecord& sr)
	{
		return time > sr.time;
	}
	bool operator<(const SprinterRecord& sr)
	{
		return time < sr.time;
	}
	bool operator>=(const SprinterRecord& sr)
	{
		return time >= sr.time;
	}
	bool operator<=(const SprinterRecord& sr)
	{
		return time <= sr.time;
	}
};

int main(void)
{
	MinHeap<SprinterRecord> mh;
	int choice;

	while(1)
	{
		cout << "1.Insert 2.Delete 3.ShowData 4.Quit" << endl;
		cin >> choice;

		if(choice == 1)
		{
			SprinterRecord r;
			r.init();
			mh.Push(r);
		}
		else if(choice==2)
			mh.Pop();
		else if(choice==3)
			for(int i=1; i<=mh.getHeapSize(); ++i)
				cout << '<' << mh[i].name << ", " << mh[i].time  << '>' << endl;
		else
			break;
	}
	return 0;
}