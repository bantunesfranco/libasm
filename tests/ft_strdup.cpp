#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include "libasm.h"

#define FUNC "ft_strdup"

bool KO = false;

int	cmp(const char *src, int test)
{
	char	*s1 = ft_strdup(src);
	char	*err1 = s1 == NULL ? strerror(errno): NULL;
	char	*s2 = strdup(src);
	char	*err2 = s2 == NULL ? strerror(errno): NULL;
	int		res;

	if (err1 || err2)
	{
		free(s1);
		free(s2);
		if (err1 && err2)
			res = strcmp(err1, err2);
		else
			return 0;
	
		if (!res)
		{
			if (!KO)
			{
				std::cerr << "------- " << FUNC << " -------" << std::endl;
				KO = true;
			}
			std::cerr << "Test " << test << ": expected '" << err2 << "' got '" << err1 << "'" << std::endl;
			return 0;
		}
	}

	res = strcmp(s1, s2) == 0;

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << s2 << "' got '" << s1 << "'" << std::endl;
	}

	free(s1);
	free(s2);
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
	v.~vector();
	std::exit(res);
}

