/***********************************************************************************************
*						Algorithms Fall 2016 Group Project Question 5                          *
*						Ted Johansmeyer, Andrew Holmes, Todd Weisse                            *
************************************************************************************************
*	5) This problem concerns the longest increasing subsequence problem. For example, for      *
*	the sequence {9,5,2,8,7,3,1,6,4} the longest increasing subsequence is {2,3,4} (note that  *
*	these elements do not need to be in consecutive positions in the sequence).                *
*	(a) Write an algorithm to solve the longest increasing subsequence problem.                *
*	(b) What is the running time of your algorithm?                                            *
*		The Runtime of our algorithm is O(nlogn)											   *
*	(c) Implement your algorithm and test it on a random sequence with 1000 entries.           *
************************************************************************************************/

#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void randomNumbers(vector<int> &a, int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 1000 + 1;
	}
}

void longestIncreasingSubsequence(vector<int> &a, vector<int> &b)
{
	// a = initial vector
	// b = vector of indexes
	vector<int> p(a.size());
	int low, hi;

	// If the initial vector is empty return
	if (a.empty()) {
		return;
	}

	b.push_back(0);

	for (int i = 1; i < a.size(); i++) {
		// Check upper bound
		if (a[b.back()] < a[i]) {
			p[i] = b.back();
			b.push_back(i);
			continue;
		}

		
		low = 0;
		hi = b.size();
		// Binary Search 
		while(low < hi) {
			int mid = (low + hi) / 2;
			if (a[b[mid]] < a[i])
				low = mid + 1; 
			else 
				hi = mid;
		}

		if (a[i] < a[b[low]]) {
			if (low > 0) 
				p[i] = b[low - 1];
			b[low] = i;
		}
	}
	// Reconstruct result
	int it = b.size();
	int index = b.back();
	while (it > 0) {
		it--;
		b[it] = index;
		index = p[index];
	}
}

int main()
{
	int n = 1000;
	vector<int> initialSeq(n);
	vector<int> indexVec;
	randomNumbers(initialSeq, n);
	longestIncreasingSubsequence(initialSeq, indexVec);

	// Print Starting Vector
	cout << "Starting vector: ";
	for (auto i = 0; i < initialSeq.size(); i++) {
		if (i == 0)
			cout << endl << "{";
		if (i % 20 == 0 && i != 0) 
			cout << endl;
		if (i == initialSeq.size() - 1)
			cout << initialSeq[i];
		else
			cout << initialSeq[i] << ", ";

	}
	cout << "}" << endl << endl;
	// Print Longest Increasing Subsequence
	cout << "The Longest increasing subsequence is: ";
	for (auto i = 0; i < indexVec.size(); i++) {
		if (i == 0)
			cout << endl << "{";
		if (i % 20 == 0 && i != 0)
			cout << endl;
		if(i == indexVec.size() - 1)
			cout << initialSeq[indexVec[i]];
		else
			cout << initialSeq[indexVec[i]] << ", ";
	}
	cout << "}" << endl;

	system("PAUSE");
	return 0;
}