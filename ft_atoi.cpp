#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "libasm.h"

#define FUNC "atoi"

bool KO = false;

int	cmp(const char *s, int test)
{
	int	n1 = ft_atoi(s);
	int	n2 = atoi(s);

	int res = n1 == n2;

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << n2 << " got '" << n1 << "'" << std::endl;
	}

	return (res);
}

int printRes(std::vector<int> v)
{
	int res = 0;

	std::cout << std::left << std::setw(20) << FUNC << " : ";
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << i + 1 << ".";
		if (v[i])
			std::cout << "\033[1;32mOK\033[0m ";
		else
		{
			std::cout << "\033[1;31mKO\033[0m ";
			res = 1;
		}
	}
	std::cout << std::endl;

	return res;
}

int main(void)
{
	std::vector<int>	v;
	int					res;
	int					i = 1;

	// Test 1
	res = cmp("1", i++);
	v.push_back(res);

	// Test 2
	res = cmp("1234", i++);
	v.push_back(res);

	// Test 3
	res = cmp("-1", i++);
	v.push_back(res);

	// Test 4
	res = cmp("-1", i++);
	v.push_back(res);

	// Test 5
	res = cmp("+1", i++);
	v.push_back(res);

	// Test 6
	res = cmp("++1", i++);
	v.push_back(res);

	// Test 7
	res = cmp("--1", i++);
	v.push_back(res);

	// Test 8
	res = cmp("+-1", i++);
	v.push_back(res);

	// Test 9
	res = cmp("-+1", i++);
	v.push_back(res);

	// Test 10
	res = cmp("--+-1", i++);

	// Test 11
	res = cmp("1a", i++);
	v.push_back(res);

	// Test 12
	res = cmp("a1", i++);
	v.push_back(res);

	// Test 13
	res = cmp("1 1", i++);
	v.push_back(res);

	return printRes(v);
}
