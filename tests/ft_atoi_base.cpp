#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "libasm.h"

#define FUNC "ft_atoi_base"

bool KO = false;

int	cmp(const char *s, const char *base, int mode, int test)
{
	int	n1 = ft_atoi_base(s, base);
	int	n2 = mode == 1 ? 0 : strtol(s, NULL, strlen(base));

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
	res = cmp("1", "0123456789", 0, i++);
	v.push_back(res);

	// Test 2
	res = cmp("1234", "	0123456789", 1, i++);
	v.push_back(res);

	// Test 3
	res = cmp("-1", "0123456789", 0, i++);
	v.push_back(res);

	// Test 4
	res = cmp("+1", "0123456789", 0, i++);
	v.push_back(res);
	// Test 5
	res = cmp("12", "\b \r01234567", 1, i++);
	v.push_back(res);

	// Test 6
	res = cmp("-12", "01234567", 0, i++);
	v.push_back(res);

	// Test 7
	res = cmp("+12", "01234567", 0, i++);
	v.push_back(res);

	// Test 8
	res = cmp("FF", "0123456789ABCDEF", 0, i++);
	v.push_back(res);

	// Test 9
	res = cmp("-FF", "0123456789ABCDEF", 0, i++);
	v.push_back(res);

	// Test 10
	res = cmp("+FF", "0123456789ABCDEF", 0, i++);
	v.push_back(res);

	// Test 11
	res = cmp("ABC", "0123456789ABCDEF", 0, i++);
	v.push_back(res);

	// Test 12
	res = cmp("ABC", "01223456789ABCDEF", 1, i++);
	v.push_back(res);

	// Test 13
	res = cmp("123", "01223456789", 1, i++);
	v.push_back(res);

	// Test 14
	res = cmp("123", "012234567", 1, i++);
	v.push_back(res);

	// Test 15
	res = cmp("2", "01", 1, i++);
	v.push_back(res);

	// Test 16
	res = cmp("01001111", "01", 0, i++);
	v.push_back(res);

	res = printRes(v);

	std::exit(res);
}
