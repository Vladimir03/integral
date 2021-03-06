//#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <thread>
//#include <mutex>
#include <vector>

using namespace std;
vector<int> threads;
typedef double(*pointFunc)(double);
double f(double x)
{
	return(10 - x);
}

double rectangle_integral(pointFunc f, double a, double b, double n)
{
	double x, h;
	double sum = 0.0;
	double fx;
	h = (b - a) / n;
	for (int i = 0; i < n; i++)
	{
		x = a + i * h;
		fx = f(x);
		sum += fx;
	}
	return (sum * h);
}

int main() {
	double a, b;
	double I;
	int n = 1000000, n_th;
	cin >> a;
	cin >> b;
	cin >> n_th;
	I = rectangle_integral(f, a, b, n);
	for (int i = 0; i < n_th; i++) {
		threads.push_back(i);
	}
	cout << I << endl;
	return 0;
}