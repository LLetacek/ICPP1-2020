#include <iostream>
#include "Matrix.h"
using namespace std;

void test() {
	Matrix<int> m{ 3, 3 };
	m.Print();

	int jednodpole[] = { 0,1,2,3,4,5,6,7,8 };
	m.Setter(jednodpole);
	m.Print();

	Matrix<int> mt = m.Transposition();
	mt.Print();

	Matrix<int> mmt = m.Multiply(mt);
	mmt.Print();

	Matrix<double> mmt_d = mmt.Cast<double>();
	mmt_d.Print();

	Matrix<double> n_d{ 3,3 };
	double jednodpole_d[] = { 4.5,5,0,2,-0.5,7,1.5,9,6 };
	n_d.Setter(jednodpole_d);
	n_d.Print();

	Matrix<double> mmtn_d = mmt_d.Multiply(n_d);
	mmtn_d.Print();

	Matrix<int> r = mmtn_d.Cast<int>();
	r.Print();

	Matrix<int> t{ 3,3 };
	int tpole[] = { 85,225,236,292,819,866,499,1413,1496 };
	t.Setter(tpole);
	t.Print();

	std::cout << "r==t ? " << (r.IsMatch(t) ? "true" : "false") << std::endl;
}

int main(int agrc, char** agrv) {

	test();

	return 0;

}