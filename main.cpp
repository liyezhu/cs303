#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>
#include <list>
#include"Term.h"

using namespace std;

int main() {
	list<Term> result;
	list<Term> first = enterPolynomial();
	list<Term> second = enterPolynomial();
	result = addPolynomial(first, second);
	display(result);
	system("pause");
	
	return 0;


}