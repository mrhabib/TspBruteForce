#include "stdafx.h"
#include "BruteForce.h"
#include <iostream>
#include <fstream>
#include <limits>
#include "Times.h"

using namespace std;


BruteForce::BruteForce()
{
	LoadFromFile();
	DisplayTheMatrix();
	Times times;
	double measurement;
	times.StartCounter();
	int * order = new int[NumberOfCities - 1];
	theShortest_order = new int[NumberOfCities - 1];
	for (int i = 0; i < NumberOfCities - 1; i++) //setting the first permutation to 0->1->2->...
		order[i] = i + 1;
	theShortestRoad = numeric_limits<int>::max();
	
	permutations(order, NumberOfCities - 1, (NumberOfCities / sizeof(int))); //going through all permutations, Heape's algorithm
	measurement = times.GetCounter();
	DisplayResults();
	cout<< "Time: " << measurement << " milliseconds" << endl<<endl;
}

void BruteForce::permutations(int a[], int size, int n) //Heape's algorithm
{
	if (size == 1)
	{
		if (FaceRoad(a) < theShortestRoad)
		{
			theShortestRoad = FaceRoad(a);
			memcpy(theShortest_order, a, sizeof(int)*(NumberOfCities - 1));
		}
		return;
	}
	for (int i = 0; i < size; i++)
	{
		permutations(a, size - 1, n);
		if (size % 2 == 1)
			swap(a[0], a[size - 1]);
		else
			swap(a[i], a[size - 1]);
	}
}

int BruteForce::FaceRoad(const int order[])
{
	int sum = 0;
	sum += mother[0][order[0]];		//Road to and town to visit
	for (int i = 0; i < NumberOfCities - 2; i++)
	{
		sum += mother[order[i]][order[i + 1]]; //we are adding roads to other cities
	}
	sum += mother[order[NumberOfCities - 2]][0];	//we are adding a way to go back to the first city
	return sum;
}


void BruteForce::LoadFromFile()
{
	ifstream files;
	files.open("dane.txt");
	files >> NumberOfCities;
	mother = new int*[NumberOfCities];
	for (int i = 0; i < NumberOfCities; ++i) {
		mother[i] = new int[NumberOfCities];
	}
	for (int i = 0; i<NumberOfCities; i++)
	{
		for (int j = 0; j<NumberOfCities; j++)
		{
			files >> mother[i][j];
		}
	}
}

void BruteForce::DisplayTheMatrix()
{
	for (int i = 0; i<NumberOfCities; i++)
	{
		for (int j = 0; j<NumberOfCities; j++)
		{
			cout << mother[i][j]<<"  ";
		}
		cout << endl;
	}
	cout << endl;
}

void BruteForce::DisplayResults()
{
	cout << "the Shortest Road:\n0";
	for (int i = 0; i < NumberOfCities - 1; i++)
		cout << " -> " << theShortest_order[i];
	cout << " -> 0 \n\n Distance: " << theShortestRoad << " Units\n\n";
}

BruteForce::~BruteForce()
{
	for (int i = 0; i < NumberOfCities; ++i) {
		delete[] mother[i];
	}
	delete[] mother;
	delete[] theShortest_order;
}
