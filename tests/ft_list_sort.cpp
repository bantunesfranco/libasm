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

void	print_list(t_list **list, std::vector<int>& arr)
{
	t_list	*node = *list;
	std::cout << "List: ";
	while (node)
	{
		std::cout << (char *)node->data << " ";
		node = node->next;
	}
	std::cout << std::endl;
	std::cout << "Arr: ";
	for (const auto i : arr)
		std::cout << i << " ";
	std::cout << "\n" << std::endl;

}

int	cmp(t_list **list, std::vector<int>& arr, int test)
{
	std::sort(arr.begin(), arr.end());
	ft_list_sort(list, strcmp);

	int res = 0;
	t_list	*node = *list;
	for (const auto i : arr)
	{
		int diff = strcmp((char *)node->data, std::to_string(i).c_str());
		
		res = diff == 0;
		if (!res)
		{
			if (!KO)
			{
				std::cerr << "------- " << FUNC << " -------" << std::endl;
				KO = true;
			}
			std::cerr << "Test " << test << ": expected '" << i << " got '" << (char *)node->data << "'" << std::endl;
			return (res);
		}
		node = node->next;
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

t_list **gen_list(const std::vector<int>& arr)
{
	t_list **list = (t_list**)calloc(1, sizeof(t_list*));

	for (auto i = arr.rbegin(); i != arr.rend(); i++)
	{
		std::string num = std::to_string(*i);
		char *str = strdup(num.c_str());
		ft_list_push_front(list, str);
	}
	return list;
}

int main(void)
{
	t_list				**list;
	std::vector<int>	arr;
	std::vector<int>	v;
	int					res;
	int					i = 1;

	// Test 1
	arr = {1, 2, 3, 4, 5};
	list = gen_list(arr);
	res = cmp(list, arr, i++);
	ft_list_clear(list, free);
	free(list);
	v.push_back(res);

	// Test 2
	arr = {4, 2, 1, 3, 5};
	list = gen_list(arr);
	res = cmp(list, arr, i++);
	ft_list_clear(list, free);
	free(list);
	v.push_back(res);

	// Test 3
	arr = {1, 1, 5, 2, 0, 6};
	list = gen_list(arr);
	res = cmp(list, arr, i++);
	ft_list_clear(list, free);
	free(list);
	v.push_back(res);

	// Test 4
	arr = {5, 4, 3, 2, 1, 4, 6};
	list = gen_list(arr);
	res = cmp(list, arr, i++);
	ft_list_clear(list, free);
	free(list);
	v.push_back(res);

	res = printRes(v);
	v.~vector();
	arr.~vector();
	std::exit(res);
}
