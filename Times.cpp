#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <windows.h>
#include "Times.h"
using namespace std;


double PCFreq = 0.0;
__int64 CounterStart = 0;

void Times::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double Times::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}
