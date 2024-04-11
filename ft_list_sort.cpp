#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include "libasm.h"
#include <random>

#define FUNC "ft_list_sort"

bool KO = false;

int	cmp(t_list **list, const std::vector<std::string>& arr, int test)
{
	std::sort(arr.begin(), arr.end());
	ft_list_sort(list, strcmp);

	t_list	*node = *list;
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
			return (1);
		}
		node = node->next;
	}

	return (0);
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
	t_list				**list;
	std::vector<std::string> 	arr = {"1", "2", "3", "4", "5"};
	std::vector<int>	v;
	int					res;
	int					i = 1;

	// Test 1
	// std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
	list = gen_list(arr);
	res = cmp(list, arr, i++);
	// ft_list_clear(list, free);
	v.push_back(res);

	// // Test 2
	// std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
	// list = gen_list(arr);
	// res = cmp(list, arr, i++);
	// // ft_list_clear(list, free);
	// v.push_back(res);

	// // Test 3
	// arr.push_back(6);
	// std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
	// list = gen_list(arr);
	// res = cmp(list, arr, i++);
	// // ft_list_clear(list, free);
	// v.push_back(res);

	// // Test 4
	// arr.push_back(6);
	// arr.push_back(4);
	// std::shuffle(arr.begin(), arr.end(), std::mt19937{std::random_device{}()});
	// list = gen_list(arr);
	// res = cmp(list, arr, i++);
	// // ft_list_clear(list, free);
	// v.push_back(res);

	res = printRes(v);
	v.~vector();
	std::exit(res);
}
