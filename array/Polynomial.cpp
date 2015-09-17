#include <iostream>
using namespace std;

class Polynomial;
class Term
{
	friend Polynomial;
	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
private:
	float coef;
	int exp;
};
class Polynomial
{
private:
	Term *termArray;
	int capacity;
	int terms;
public:
	Polynomial(int terms);
	Polynomial(const Polynomial& ref);
	~Polynomial();
	void NewTerm(const float theCoeff, const int theExp);
	friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
};

Polynomial::Polynomial(int terms=0) : terms(terms)
{
	if(terms==0)
		capacity = 1;
	else
		capacity = terms;

	termArray = new Term[capacity];
}
Polynomial::Polynomial(const Polynomial& ref) : terms(ref.terms), capacity(ref.capacity)
{
	termArray = new Term[capacity];
}
Polynomial::~Polynomial()
{
	delete[] termArray;
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if(terms == capacity)
	{
		capacity *= 2;
		Term *temp = new Term[capacity];
		copy(termArray,termArray+terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
{
	Polynomial result;
	int p1Pos=0, p2Pos=0;

	while((p1Pos<p1.terms) && (p2Pos<p2.terms))
		if(p1.termArray[p1Pos].exp == p2.termArray[p2Pos].exp)
		{
			float t = p1.termArray[p1Pos].coef + p2.termArray[p2Pos].coef;
			if(t)
				result.NewTerm(t,p1.termArray[p1Pos].exp);
			p1Pos++;
			p2Pos++;
		}
		else if(p1.termArray[p1Pos].exp < p2.termArray[p2Pos].exp)
		{
			result.NewTerm(p2.termArray[p2Pos].coef, p2.termArray[p2Pos].exp);
			p2Pos++;
		}
		else
		{
			result.NewTerm(p1.termArray[p1Pos].coef, p1.termArray[p1Pos].exp);
			p1Pos++;
		}

	for( ; p1Pos<p1.terms; p1Pos++)
		result.NewTerm(p1.termArray[p1Pos].coef, p1.termArray[p1Pos].exp);
	for( ; p2Pos<p2.terms; p2Pos++)
		result.NewTerm(p2.termArray[p2Pos].coef, p2.termArray[p2Pos].exp);

	return result;
}