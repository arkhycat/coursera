// crypto5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>
#include <cmath>
#include <iostream>
#include "mpir-2.7.0\mpirxx.h"


using namespace std;

unordered_map<float, unsigned int> BuildHash(unsigned int g, unsigned int h, unsigned int p, unsigned int max)
{
	unordered_map<float, unsigned int> multProducts;
	for (unsigned int i = 1; i <= max; i++)
	{
		unsigned int product = static_cast<unsigned int>(pow(g, i)) % p;
		multProducts.insert(pair<float, unsigned int>(h/product, i));
	}

	return multProducts;
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int g = 10;
	unsigned int p = 3;
	unsigned int h = 2;
	unsigned int B = pow(2, 20);

	unordered_map<float, unsigned int> hash = BuildHash(g, h, p, B);

	cin.get();
	return 0;
}

