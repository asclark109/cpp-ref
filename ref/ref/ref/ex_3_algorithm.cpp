#include<iostream>
#include<numeric>
#include<algorithm>
#include<vector>
#include<iterator>
#include<cmath>
using namespace std;

double square(double d) {
	return d*d;
}

vector<double> ex2_1_faster(vector<double> v) {
	vector<double> result(v.size());
	transform(v.begin(), v.end(), result.begin(), square);
	cout << "result = (";
	ostream_iterator<double> os(cout, ", ");
	copy(result.begin(), result.end(), os);
	cout << ")" << endl;
	return result;
}

vector<double> ex2_1_safer(vector<double> v) {
	vector<double> result;
	transform(v.begin(), v.end(), back_inserter(result), square);
	cout << "result = (";
	ostream_iterator<double> os(cout, ", ");
	copy(result.begin(), result.end(), os);
	cout << ")" << endl;
	return result;
}

void ex2_1_lambda(vector<double> v) {
	vector<double> result;
	result.resize(v.size());
	transform(v.begin(), v.end(), result.begin(),
		[](double d) { return d*d; });
	cout << "result = (";
	ostream_iterator<double> os(cout, ", ");
	copy(result.begin(), result.end(), os);
	cout << ")" << endl;
}

void ex2_1_shorter(vector<double> v)
{
	ostream_iterator<double> os(cout, ", ");
	cout << "result = (";
	transform(v.begin(), v.end(), os,
		[](double d) { return d * d; });
	cout << ")" << endl;
} 

void ex2_1_2(vector<double> v) {
	vector squared = ex2_1_faster(v);
	cout << "Length = "
		 << sqrt(accumulate(squared.begin(), squared.end(), 0.0))
		 << endl;
}


void ex2_1_3(vector<double> v) {
	cout << "Length = "
		<< sqrt(inner_product(v.begin(), v.end(),
			v.begin(), 0.0));
}

double square_and_add_to_accumulator(double old_accumulator, double next) {
	return old_accumulator + next*next;
}

void ex2_1_4_v1(vector<double> v) {
	cout << "Length = "
		 << sqrt(accumulate(v.begin(), v.end(), 0.0, square_and_add_to_accumulator))
		 << endl;
}

void ex2_1_4_v2(vector<double> v) {
	cout << "Length = "
		<< sqrt(accumulate(v.begin(), v.end(), 0.0, 
		        [](double d, double n) { return d + n*n;}))
		<< endl;
}

int main()
{
	vector<double> v{ 1, 2, 3 };
	ex2_1_faster(v);
	ex2_1_safer(v);
	ex2_1_lambda(v);
	ex2_1_shorter(v);
	ex2_1_2(v);
	ex2_1_3(v);
	ex2_1_4_v1(v);
	ex2_1_4_v2(v);
	return 0;
}
