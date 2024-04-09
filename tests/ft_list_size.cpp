#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include "libasm.h"

#define FUNC "ft_list_size"

bool KO = false;

int	cmp(t_list **list, int size, int test)
{
	int len = ft_list_size(*list);
	int res = len == size;

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << size << " got '" << len << "'" << std::endl;
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

t_list **gen_list(int start, int end)
{
	t_list **list = (t_list**)calloc(1, sizeof(t_list*));

	for (int i = end; i >= start; i--)
	{
		t_list	*node = ft_list_new((void *)strdup(std::to_string(i).c_str()));
		ft_list_push_front(list, node);
	}
	return list;
}

int main(void)
{
	std::vector<int>	v;
	int					res;
	int					i = 1;

	t_list	**list = gen_list(1, 5);
	t_list	*list2 = NULL;

	// Test 1
	res = cmp(list, 5, i++);
	v.push_back(res);

	// Test 2
	t_list *node = ft_list_new((void *)strdup("0"));
	ft_list_push_front(list, node);
	res = cmp(list, 6, i++);
	v.push_back(res);

	// Test 3
	res = cmp(&list2, 0, i++);
	v.push_back(res);

	// Test 4
	node = ft_list_new((void *)strdup("1"));
	ft_list_push_front(&list2, node);
	res = cmp(&list2, 1, i++);
	v.push_back(res);

	ft_list_clear(list, free);
	ft_list_clear(&list2, free);
	free(list);

	std::exit(printRes(v));
}
