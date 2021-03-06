// Helloworld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>

double shared = 0;
std::mutex mtx;

void compute(int begin, int end)
{
	for (int i = begin; i != end; ++i)
	{
		double current = i;

		std::lock_guard<std::mutex> lck(mtx);
		shared += current;
	}
}

int main()
{
	std::thread t1 (compute, 0, 100);
	std::thread t2 (compute, 100, 102);
	t1.join();
	t2.join();
    std::cout << shared << std::endl;
    return 0;
}

