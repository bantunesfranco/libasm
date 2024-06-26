#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "libasm.h"

#define FUNC "ft_strcpy"

bool KO = false;

int	cmp(const char *src, int test)
{
	char	dst1[100];
	char	dst2[100];

	bzero(dst1, 100);
	bzero(dst2, 100);

	char	*s1 = ft_strcpy(dst1, src);
	char	*s2 = strcpy(dst2, src);

	int res = strcmp(s1, s2) == 0;
	if (!res)
	{
		std::cerr << s1 << " , " << s2 << std::endl;
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << s2 << "' got '" << s1 << "'" << std::endl;
	}

	return (res);
}

int printRes(const std::vector<int>& v)
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
	res = cmp("", i++);
	v.push_back(res);

	// Test 2
	res = cmp("a", i++);
	v.push_back(res);

	// Test 3
	res = cmp("ab", i++);
	v.push_back(res);

	// Test 4
	res = cmp("lol", i++);
	v.push_back(res);

	// Test 5
	res = cmp("this is a test!", i++);
	v.push_back(res);


	res = printRes(v);

	std::exit(res);
}

