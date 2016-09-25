#include<iostream>
#include<list>


using namespace std;


class Term
{
private:
	int exponent;
	int coefficient;
public:
	friend bool operator < (const Term& lhs, const Term& rhs);
	friend bool operator > (const Term lhs, const Term rhs);
	friend bool operator == (const Term lhs, const Term rhs);
	friend Term operator + (const Term lhs, const Term rhs);
	Term(int ex, int co);
};


Term::Term(int ex, int co) {
	exponent = ex;
	coefficient = co;
};

bool operator < (const Term& lhs, const Term& rhs) {
	return lhs.exponent<rhs.exponent;
}


bool operator > (const Term lhs, const Term rhs) {
	return lhs.exponent>rhs.exponent;
}
bool operator == (const Term lhs, const Term rhs) {
	return lhs.exponent == rhs.exponent;
}
Term operator + (const Term lhs, const Term rhs) {
	Term newterm(lhs.exponent, lhs.coefficient + rhs.coefficient);
	return newterm;
}

testing git