// algo1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

unsigned long inversions = 0;

void merge(vector<int>& merged, vector<int>& left, vector<int>& right)
{
	vector<int>::iterator it_l = left.begin();
	vector<int>::iterator it_r = right.begin();

	while (it_l != left.end() && it_r != right.end())
	{
		if (*it_l <= *it_r)
		{
			merged.push_back(*it_l);
			it_l++;
		}
		else
		{
			merged.push_back(*it_r);
			it_r++;
			inversions += left.end() - it_l;
		}
	}

	if (it_l != left.end())
	{
		copy(it_l, left.end(), back_inserter(merged));
	}else if(it_r != right.end())
	{
		copy(it_r, right.end(), back_inserter(merged));
	}
}


void sort(vector<int> &v)
{
	if (v.size() > 1)
	{
		vector<int>::iterator middle = v.begin() + (int)v.size()/2;
		vector<int> left(v.begin(), middle);
		vector<int> right(middle, v.end());
		sort(left);
		sort(right);
		vector<int> merged;
		merged.reserve(left.size()+right.size());
		merge(merged, left, right);
		if (merged.size() > 50000)
			cout << inversions << endl;
		v.assign(merged.begin(), merged.end());
	}
}


int main()
{
    ifstream ifs("IntegerArray.txt");
	//int a[] = { 4, 80, 70, 23, 9, 60, 68, 27, 66, 78, 12, 40, 52, 53, 44, 8, 49, 28, 18, 46, 21, 39, 51, 7, 87, 99, 69, 62, 84, 6, 79, 67, 14, 98, 83, 0, 96, 5, 82, 10, 26, 48, 3, 2, 15, 92, 11, 55, 63, 97, 43, 45, 81, 42, 95, 20, 25, 74, 24, 72, 91, 35, 86, 19, 75, 58, 71, 47, 76, 59, 64, 93, 17, 50, 56, 94, 90, 89, 32, 37, 34, 65, 1, 73, 41, 36, 57, 77, 30, 22, 13, 29, 38, 16, 88, 61, 31, 85, 33, 54 };
	//vector<int> v(&a[0], &a[0]+sizeof(a)/sizeof(int));
	vector<int> v;

	v.assign(istream_iterator<int>(ifs), istream_iterator<int>());

	//copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    sort(v);
	cin.get();

    return 0;
}

