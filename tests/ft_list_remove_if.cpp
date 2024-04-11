#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include "libasm.h"
#include <random>

#define FUNC "ft_list_remove_if"

bool KO = false;

int	cmp(t_list **list, const char *str, const std::vector<std::string>& arr, int test)
{
	ft_list_remove_if(list, (void *)str, strcmp, free);

	t_list	*node = *list;
	if (!arr.size())
	{
		if (!node)
			return (1);
		else
		{
			if (!KO)
			{
				std::cerr << "------- " << FUNC << " -------" << std::endl;
				KO = true;
			}
			std::cerr << "Test " << test << ": expected NULL got '" << (char *)node->data << "'" << std::endl;
			return (0);
		}
	}
	for (const auto &i : arr)
	{
		int res = strcmp((char *)node->data, i.c_str());
		if (res)
		{
			if (!KO)
			{
				std::cerr << "------- " << FUNC << " -------" << std::endl;
				KO = true;
			}
			std::cerr << "Test " << test << ": expected '" << i << " got '" << (char *)node->data << "'" << std::endl;
			return (0);
		}
		node = node->next;
	}

	return (1);
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

t_list **gen_list(const std::vector<std::string>& arr)
{
	t_list **list = (t_list**)calloc(1, sizeof(t_list*));

	for (auto i = arr.rbegin(); i != arr.rend(); i++)
	{
		char *str = strdup((*i).c_str());
		ft_list_push_front(list, str);
	}
	return list;
}

int main(void)
{
	int							res;
	int							i = 1;
	std::vector<std::string>	arr = {"a", "b", "c", "c", "d", "a", "f", "l"};
	std::vector<int>			v;
	t_list						**list = gen_list(arr);

	// Test 1
	arr = {"a", "b", "c", "c", "d", "a", "f"};
	res = cmp(list, "l",  arr, i++);
	v.push_back(res);

	// Test 2
	arr = {"a", "c", "c", "d", "a", "f"};
	res = cmp(list, "b",  arr, i++);
	v.push_back(res);

	// Test 3
	arr = {"c", "c", "d", "f"};
	res = cmp(list, "a",  arr, i++);
	v.push_back(res);
		
	// Test 4
	arr = {"c", "c", "f"};
	res = cmp(list, "d",  arr, i++);
	v.push_back(res);

	// Test 5
	arr = {"f"};
	res = cmp(list, "c",  arr, i++);
	v.push_back(res);

	// Test 6
	arr = {"f"};
	res = cmp(list, "z",  arr, i++);
	v.push_back(res);

	// Test 7
	arr = {};
	res = cmp(list, "f",  arr, i++);
	v.push_back(res);

	ft_list_clear(list, free);
	free(list);

	res = printRes(v);
	v.~vector();
	arr.~vector();
	std::exit(res);
}
