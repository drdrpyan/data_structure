#include <iostream>
#include <string>
#include "Chain.h"
using std::string;
using std::cout;
using std::endl;
using std::ostream;
#ifndef PHONEBOOK
#define PHONEBOOK

struct PNdata
{
	string name;
	string number;

	bool operator<(const PNdata& ref)
	{
		return name < ref.name;
	}
	bool operator>(const PNdata& ref)
	{
		return name > ref.name;
	}
	bool operator==(const PNdata& ref)
	{
		return name==ref.name;
	}
	bool operator!=(const PNdata& ref)
	{
		return name!=ref.name;
	}
	friend ostream& operator<<(ostream& os, const PNdata& data)
	{
		return os << "이름 : " << data.name << "\n전화번호 : " << data.number << "\n";
	}
};

class PhoneBook
{
private:
	Chain<PNdata> PNlist[26];
public:
	PhoneBook();
	void insertData(string Name, string Pnumber);
	void printData() const;
	void printData(char C) const;
	void removePerson(string Name);
//	void searchName(string Name) const;
};

PhoneBook::PhoneBook()
{
}
void PhoneBook::insertData(string Name, string Pnumber)
{
	PNdata insData = {Name, Pnumber};
	PNlist[Name[0]-'a'].insertOrderd(insData);
}
void PhoneBook::printData() const
{
	for(int i=0; i<26; ++i)
	{
		cout << "== " << (char)('a'+i) << " ==" << endl; 
		PNlist[i].printAll();
	}
}
void PhoneBook::printData(char C) const
{
	cout << "== " << C << " ==" << endl; 
	PNlist[C-'a'].printAll();
}
void PhoneBook::removePerson(string Name)
{
	PNdata target={Name,0};
	PNlist[Name[0]-'a'].removeNode(target);
}
//void PhoneBook::searchName(string Name) const
//{
//	PNdata target = {Name,0};
//	cout << PNlist[Name[0]-'a'].search(target);
//}
#endif