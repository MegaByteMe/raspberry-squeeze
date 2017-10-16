/*
 * main.cxx
 * 
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <ctime>

#include <sys/types.h>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

void selection_sort(int * b, int size) {
	for(int j = 0; j < size; j++) {
		int imin = j;
		
		for(int i = j + 1; i < size; i++) {
			if(b[i] < b[imin]) imin = i;
		}
		
		if(imin != j) {
			int temp = b[j];
			b[j] = b[imin];
			b[imin] = temp;
		}
	}
}

void dsp_array(int * b, int size) {
	cout << endl;
	for(int i = 0; i < size; i++) {
		cout << b[i] << " ";
	}
	cout << endl;
}

int main(int argc, char **argv)
{
	string id;
	
	// Generate Two Additional Processes For A Total Of Three
	pid_t first, second;
	first = fork();

	if(first > 0) {
		second = fork();
		
		if(second > 0) {
			id = "Parent Process";
			}
		else if(second < 0) {
			cout << "FAILED" << endl;
			exit(1);
		}
		else {
			id = "Second Child Process";
		}
	}
	else if(first < 0) {
		cout << "FAILED" << endl;
		exit(1);
	}
	else {
		id = "First Child Process";
	}

	// Random Seed value
	srand((unsigned int)time(NULL));
	const int n = 9000;
	const int runs = 100;
	int a[n];
	long total = 0;
	
	for(int h = 0; h < runs; h++) {
		// Populate Array With Random Numbers
		for(int i = 0; i < n; i++) {
			a[i] = (rand() % 100000) + 1;
		}
		
		auto t1 = high_resolution_clock::now();
		selection_sort(a, n);
		auto t2 = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds> (t2 - t1).count();
		total += duration;
	}

	cout << endl << "Execution for " << id << endl;
	cout << "Total Time " << total << " mS\n";
	cout << "Average Time " << total/runs << " mS, over " << runs << " runs\n\n";
	
	return 0;
}

