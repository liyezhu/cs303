#include<iostream>
#include<string>
#include<list>

#define DEG 100	//for polynomials of max degree = 99
using namespace std;

class Term
{
private:
	int exponent;
	double coefficient;
public:
	friend bool operator < (const Term& lhs, const Term& rhs);
	friend bool operator > (const Term lhs, const Term rhs);
	friend bool operator == (const Term lhs, const Term rhs);
	friend ostream &operator<<(ostream &output, const Term term);
	friend Term operator + (const Term lhs, const Term rhs);
	Term(int ex, double co);
};

list<Term> addPolynomial(list<Term> a, list<Term> b);
list<Term> enterPolynomial();
void display(list<Term> result);

