#ifndef BRUTEFORCE_H_INCLUDED
#define BRUTEFORCE_H_INCLUDED

class BruteForce {
public:
	BruteForce();
	~BruteForce();
private:
	int NumberOfCities;
	int **mother;
	
	int *theShortest_order;
	int  theShortestRoad;
	void permutations(int[], int, int);
	void LoadFromFile();
	void DisplayTheMatrix();
	void DisplayResults();
	int FaceRoad(const int[]);
};



#endif // BRUTEFORCE_H_INCLUDED
