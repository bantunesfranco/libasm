#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include "libasm.h"

#define FUNC "list_push_front"

bool KO = false;

std::string get_lst_str(t_list **lst)
{
	std::string str;
	t_list *head = *lst;

	while (head)
	{
		str += std::string((char *)head->data);
		if (head->next)
			str += " ";
		head = head->next;
	}

	return str;
}

int	cmp(t_list **list, void *data, char *expected, int test)
{
	ft_list_push_front(list, data);

	std::string lst_str = get_lst_str(list);
	int res = std::string(expected) == lst_str;

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << expected << " got '" << lst_str << "'" << std::endl;
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

t_list	**gen_list(int start, int end)
{
	t_list	*head = ft_list_new((void *)start++);
	t_list	*node = head;

	for (int i = start; i <= end; i++)
	{
		const char *data = std::to_string(i).c_str();
		node->next = ft_list_new((void *)strdup(data));
		node = node->next;
	}

	return &head;
}

int main(void)
{
	std::vector<int>	v;
	int					res;
	int					i = 1;

	t_list	**list = gen_list(1, 5);
	t_list	*list2 = ft_list_new((void *)strdup("1"));
	t_list	**list3 = NULL;

	// Test 1
	res = cmp(list, strdup("0"), "0 1 2 3 4 5", i++);
	v.push_back(res);

	// Test 2
	res = cmp(list, strdup("-1"), "-1 0 1 2 3 4 5", i++);
	v.push_back(res);

	// Test 3
	res = cmp(&list2, strdup("0"), "0, 1", i++);
	v.push_back(res);

	// Test 4
	res = cmp(&list2, strdup("-1"), "-1, 0, 1", i++);
	v.push_back(res);

	// Test 5
	res = cmp(list3, strdup("0"), "0", i++);
	v.push_back(res);

	// Test 6
	res = cmp(list3, strdup("-1"), "-1, 0", i++);
	v.push_back(res);

	ft_list_clear(list, free);
	ft_list_clear(&list2, free);
	ft_list_clear(list3, free);

	return printRes(v);
}
