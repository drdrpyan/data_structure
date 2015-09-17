#include <iostream>
using namespace std;

//저장될 입금 정보를 나타낼 클래스
class transaction
{
	friend class Bank;
private:
	struct tm date;
	double money;
public:
	transaction(void)
	{
	}
	transaction(const transaction& ref) : date(ref.date), money(ref.money)
	{
	}
	transaction(struct tm date, double money) : date(date), money(money)
	{
	}
	~transaction()
	{
	}
	void PrintData(void)
	{
		cout << date.tm_mon+1 << ' ' << date.tm_mday << ' ' << date.tm_year+1900 << ' ' << money;
	}
};

//큐
template<class T>
class Queue
{
private:
	int front, rear;
	int capacity;
	T* items;
public:
	Queue(int capacity = 10) : 
		capacity(capacity), front(0), rear(0)
	{
		items = new T[capacity];
	}
	Queue(const Queue<T>& ref) :
		capacity(ref.capacity), front(ref.front), rear(ref.rear)
	{
		items = new items[capacity];
		copy(ref.items, ref.items+capacity-1, items);
	}
	~Queue()
	{
		delete[] items;
	}

	void ChangeCapacity(int newSize)
	{
		if(newSize > capacity)
			throw "newSize > capacity";
	
		T* temp = new T[newSize];
		if(front == rear)
		{
			delete[] items;
			items = temp;
		}
		else if(front < rear)
		{
			std::copy(items+front, items+rear-1, temp);
			delete[] items;
			items = temp;
		}
		else
		{
			std::copy(items+front, items+capacity, temp);
			std::copy(items, items+rear, items+capacity-front);
			delete[] items;
			items = temp;
		}

		front = 0;
		rear = CurrentSize();
	}
	void Push(const T& item)
	{
		if(front == (rear+1)%capacity)
			ChangeCapacity(capacity+5);
		items[rear++] = item;
		rear %= capacity;
	}
	T Pop(void)
	{
//오류발생으로 주석 처리
//		if((front+1)%capacity == rear)
//			throw "Queue is empty";
		T temp(items[front++]);
		front %= capacity;
		return temp;
	}

	void backPush(const T& item)
	{
		front = (front-1+capacity)/capacity;
		items[front] = item;
	}

	int CurrentSize(void)
	{
		if(front == rear)
			return 0;
		else if(front < rear)
			return rear-front;
		else
			return capacity-front+rear;
	}
};

//입,출금 동작을 하는 클래스
class Bank
{
private:
	struct tm today;
	Queue<transaction>* balance;
	double totalBalance;
	double interest;
	double rate;

	double ComputeInterest(const tm& depositDay, const tm& widthrowalDay, double money)
	{
		//윤년계산 생략
		return money*((double)((widthrowalDay.tm_year*365+widthrowalDay.tm_yday)
			- (depositDay.tm_year*365+depositDay.tm_yday))/30*(rate/12));
	}
public:
	Bank(int mm, int dd, int yy, double rate) : rate(rate), totalBalance(0), interest(0)
	{
		today = inputDate(mm, dd, yy);
		balance = new Queue<transaction>;
	}
	Bank(const struct tm& today, double rate) : today(today), rate(rate), totalBalance(0), interest(0)
	{
		balance = new Queue<transaction>;
	}
	~Bank()
	{
		delete balance;
	}
	static tm inputDate(int mm, int dd, int yy)
	{
		int accum[12] = {0, 31, 59,90,120,151,181,212,243,273,304,334};
		tm date;
		date.tm_mon = mm-1;
		date.tm_mday = dd;
		date.tm_year = yy-1900;
		date.tm_yday = accum[date.tm_mon]+date.tm_mday;

		return date;
	}
	void Deposit(const struct tm& date, double m)
	{
		transaction item(date,m);
		balance->Push(item);
		totalBalance += m;
	}
	void Widthrowal(const struct tm& date, double m)
	{
		transaction temp = balance->Pop();
		while(temp.money<m)
		{
			totalBalance -= temp.money;
			m -= temp.money;
			interest += ComputeInterest(temp.date, date, temp.money);
			temp = balance->Pop();
		}
		totalBalance -= m;
		temp.money -= m;
		interest += ComputeInterest(temp.date, date, temp.money);
		if(temp.money > 0)
			balance->backPush(temp);
	}
	double Balance(void)
	{
		double totalInterest=interest;
		Queue<transaction> tempQ;
		transaction temp;
		int size = balance->CurrentSize();
		for(int i=0; i<size; ++i)
		{
			temp = balance->Pop();
			totalInterest+=ComputeInterest(temp.date, today, temp.money);
			tempQ.Push(temp);
		}
		for(int i=0; i<size; ++i)
		{
			balance->Push(tempQ.Pop());
		}
		
		return totalBalance + totalInterest;
	}
};

//메인
int main(void)
{
	int mm,dd,yy;
	double rate;
	cout << "Today's date: ";
	cin >> mm >> dd >> yy;
	cout << "Interest rate per year (%) : ";
	cin >> rate;
	Bank bank(Bank::inputDate(mm,dd,yy), rate/100);
	cout << endl << endl;

	int choice=0;
	double money;
	enum {DEPOSIT=1, WIDTHROWAL, BALANCE, QUIT};
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(2);
	while(1)
	{
		cout << "Menu : 1) deposit  2) widthrowal  3) balance  4) quit" << endl;
		cout << "Your choice : ";
		cin >> choice;
		cout << endl << endl;

		switch(choice)
		{
		case DEPOSIT:
			cout << "The date of deposit : ";
			cin >> mm >> dd >> yy;
			cout << "Amounts ($) : ";
			cin >> money;
			cout << endl << endl;
			bank.Deposit(Bank::inputDate(mm,dd,yy), money);
			break;
		case WIDTHROWAL:
			cout << "The date of widthrowal : ";
			cin >> mm >> dd >> yy;
			cout << "Amount ($) : ";
			cin >> money;
			cout << endl << endl;
			bank.Widthrowal(Bank::inputDate(mm, dd, yy), money);
			break;
		case BALANCE:
			cout << "The current balance = $" << bank.Balance() << endl << endl;
			break;
		case QUIT:
			cout << "Bye~";
			break;
		}
		break;
	}

	return 0;
}