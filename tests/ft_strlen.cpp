#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "libasm.h"

#define FUNC "ft_strlen"

bool KO = false;

int	cmp(const char *s1, const char *s2, int test)
{
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = strlen(s2);

	int res = len1 == len2;

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << len2 << " got '" << len1 << "'" << std::endl;
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
	res = cmp("abcdefghijklmno", "abcdefghijklmno", i++);
	v.push_back(res);

	// Test 5
	res = cmp("this is a test", "this is a test", i++);
	v.push_back(res);

	return printRes(v);
}

