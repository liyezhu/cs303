#include<iostream>
#include<string>
#include<list>
#include"Term.h"

#define DEG 100	//for polynomials of max degree = 99
using namespace std;


Term::Term(int ex, double co){
	exponent = ex;
	coefficient = co;
}

ostream &operator<<(ostream &output, const Term term)
{
	if (term.coefficient<0)
		output << term.coefficient << "x^" << term.exponent;
	else if (term.coefficient>0)
		output << "+" << term.coefficient << "x^" << term.exponent ;
	return output;
}

bool operator < (const Term& lhs, const Term& rhs){
	return lhs.exponent<rhs.exponent;
}


bool operator >(const Term lhs, const Term rhs){
	return lhs.exponent>rhs.exponent;
}
bool operator == (const Term lhs, const Term rhs){
	return lhs.exponent == rhs.exponent;
}
Term operator + (const Term lhs, const Term rhs){
	Term newterm(lhs.exponent, lhs.coefficient + rhs.coefficient);
	return newterm;
}

list<Term> addPolynomial(list<Term> a, list<Term> b){
	list<Term> result;
	list<Term>::iterator iter_a = a.begin();
	list<Term>::iterator iter_b = b.begin();
	while (iter_a != a.end() && iter_b != b.end()){
		if (iter_a == a.end()){
			result.push_back(*iter_b);
			iter_b++;
			continue;
		}
		if (iter_b == b.end()){
			result.push_back(*iter_a);
			iter_a++;
			continue;
		}
		if (*iter_a > *iter_b){
			result.push_back(*iter_a);
			iter_a++;
		}
		else if (*iter_a < *iter_b){
			result.push_back(*iter_b);
			iter_b++;
		}
		else{
			result.push_back(*iter_a + *iter_b);
			iter_a++;
			iter_b++;
		}
	}

	return result;
};

list<Term> enterPolynomial(){
	string str;
	cout << "      Enter a polynomial without like terms\n";
	cout << "(use the letter x. for ex.: -x+4.5x^3+2x^4-3.1)\n";
	cout << "\nEnter: ";
	cin >> str;
	int strSize = str.size();

	//	How many monomials has the polynomial?
	int monoms = 1;
	for (int i = 1; i < strSize; ++i)
		if (str[i] == '+' || str[i] == '-')
			monoms++;

	//	Signs "+" are necessary for the string parsing 
	if (isdigit(str[0])) str.insert(0, "+");
	if (str[0] == 'x') str.insert(0, "+");
	str.append("+");
	strSize = str.size();

	//	Extracting the monomials as monomStr
	int k = 0;
	int j = 0;
	string monomStr[DEG];
	for (int i = 1; i < strSize; ++i)
		if (str[i] == '+' || str[i] == '-')
		{
		monomStr[k++] = str.substr(j, i - j);
		j = i;
		}

	//  Monomials' formatting i.e. to have all the same form: coefficientX^exponent
	for (int i = 0; i < monoms; ++i)
	{
		if (monomStr[i][1] == 'x')	//x is after the +/- sign 
			monomStr[i].insert(1, "1");	//& gets 1 as coefficient
		bool flag = false;	// assuming that x is not present
		int len = monomStr[i].size();
		for (int j = 1; j < len; ++j)
			if (monomStr[i][j] == 'x')	//but we test this
			{
			flag = true;	//& if x is present
			if (j == len - 1)	//& is the last 
				monomStr[i].append("^1");	//it gets exponent 1
			break;	//& exit from j_loop
			}
		if (!flag)	//if x is not present: we have a constant term
			monomStr[i].append("x^0");	//who gets "formatting"
	}

	//	Extracting the coefficients and exponents as numbers
	list<Term> li;
	int expon[DEG] = { 0 };
	double coeff[DEG] = { 0. };
	for (int i = 0; i < monoms; ++i)
	{
		int monomSize = monomStr[i].size();
		for (int j = 0; j < monomSize; ++j)
		{
			if (monomStr[i][j] == '^')
			{
				expon[i] = stoi(monomStr[i].substr(j + 1, monomSize - j));
				coeff[i] = stod(monomStr[i].substr(0, j));
				break;
			}
		}
	}

	//	Looking for the max of exponents	
	int maxExponent = 0;
	for (int k : expon)
		if (k >= maxExponent) maxExponent = k;

	//	Generating the monomials of the null polynomial having degree = maxEponent
	string newMonom[DEG];
	for (int i = maxExponent; i >= 0; i--)
		newMonom[i] = "+0x^" + std::to_string(i);

	//	Mixing the two polynomials: given & null		
	for (int i = monoms; i >= 0; i--)
		newMonom[expon[i]] = monomStr[i];

	//	Creating the final(complete) form of the polynomial as finalStr	
	string finalStr;
	for (int i = maxExponent; i >= 0; i--)
		finalStr += newMonom[i];
	;

	//	Extracting( at last!..) the coefficients & exponents
	//	from the final form of the given polynomial		
	int finalSize = finalStr.size();
	int start[DEG] = { 0 };
	int stop[DEG] = { 0 };
	k = 0;
	for (int i = 0; i < finalSize; ++i)
	{
		if (finalStr.substr(i, 1) == "+" || finalStr.substr(i, 1) == "-")
			start[k] = i;
		if (finalStr.substr(i, 1) == "x")
			stop[k++] = i;
	}


	for (int i = 0; i < k; ++i)
	{
		coeff[i] = stod(finalStr.substr(start[i], stop[i] - start[i]));
		expon[i] = maxExponent - i;
		Term temp(expon[i], coeff[i]);
		li.push_back(temp);
	}
	display(li);
	return li;
};
void display(list<Term> result){
	for (list<Term>::iterator itr = result.begin(); itr != result.end(); itr++){
		cout << *itr;
	}
	cout << endl;
};
