#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "libasm.h"

#define FUNC "ft_strcmp"

bool KO = false;

int normalize(int c)
{
	if (c < 0)
		return -1;
	else if (c > 0)
		return 1;
	return c;
}

int	cmp(const char *s1, const char *s2, int test)
{
	int	cmp1 = ft_strcmp(s1, s2);
	int	cmp2 = strcmp(s1, s2);

	int res = normalize(cmp1) == normalize(cmp2);

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << cmp2 << " got '" << cmp1 << "'" << std::endl;
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
	res = cmp("", "", i++);
	v.push_back(res);

	// Test 2
	res = cmp("a", "a", i++);
	v.push_back(res);

	// Test 3
	res = cmp("ab", "ab", i++);
	v.push_back(res);

	// Test 4
	res = cmp("lol", "loo", i++);
	v.push_back(res);

	// Test 5
	res = cmp("this is a test!", "this is a test", i++);
	v.push_back(res);

	// Test 6
	res = cmp("1234", "12", i++);
	v.push_back(res);

	// Test 7
	res = cmp("12", "1234", i++);
	v.push_back(res);

	std::exit(printRes(v));
}

