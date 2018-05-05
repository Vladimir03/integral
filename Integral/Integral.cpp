#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <thread>
//#include <mutex>
#include <vector>
#include <sstream>

using namespace std;

vector<int> threads;

double f(double x)
{
	return(10 - x);
}

void rectangle_integral(double left_limit, double right_limit, double step, double &res1)
{
	double x;
	double sum = 0.0;
	double fx;
	double h = (right_limit - left_limit) / step;
	for (int i = 0; i < step - 1; i++)
	{
		x = left_limit + i * h;
		fx = f(x);
		sum += fx;
	}
	res1 = sum*h;
}

//typedef chrono::duration<float> fsec;
int main(int argc, char *argv[]) 
{
	if (argc != 4)
	{
		cerr << "wrong input data";
	}
	else
	{
		double result = 0.0;
		int n;
		double lower_limit;
		double upper_limit;
		const unsigned long long int const_step = 1000000000l;
		stringstream new_stream;
		new_stream << argv[1] << ' ' << argv[2] << ' ' << argv[3];
		new_stream >> n >> lower_limit >> upper_limit;
		const int step1 = const_step / n;
		const int step2 = const_step - step1 * (n - 1);
		double *res_lim = new double[n + 1];
		auto start = chrono::high_resolution_clock::now();
		double h = (upper_limit - lower_limit) / n;
		for (int i = 0; i <= n; i++)
		{
			res_lim[i] = lower_limit + i * h;
		}
		double *i = new double[n];
		vector<thread> threads;
		for (int j = 0; j < n; j++)
		{
			if (j != n - 1)
			{
				threads.push_back(thread(rectangle_integral, res_lim[j], res_lim[j + 1], step1, ref(i[j])));
			}
			else
			{
				threads.push_back(thread(rectangle_integral, res_lim[j], res_lim[j + 1], step1, ref(i[j])));
			}
		}
		for (auto & thread1 : threads)
			thread1.join();
		for (int j = 0; j < n; j++)
		{
			result += i[j];
		}
		auto end = chrono::high_resolution_clock::now();
		cout << result << endl;
		//fsec fs = end - start;
		//cout << fs.count() << endl;
		cerr << chrono::duration<unsigned long int, nano>(end - start).count() << endl;
	}
	return 0;
}