#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include "libasm.h"

#define FUNC "ft_list_push_front"

bool KO = false;

std::string get_lst_str(t_list **lst)
{
	std::string str = "";
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

int	cmp(t_list **list, char *data, const std::string& expected, int test)
{
	char *str = strdup(data);
	ft_list_push_front(list, str);
	std::string lst_str = get_lst_str(list);
	int res = expected == lst_str;

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
	char				*str;

	t_list	**list = (t_list **)malloc(sizeof(t_list *));
	str = strdup("1");
	*list = ft_create_elem(str);

	str = strdup("1");
	t_list	*list2 = ft_create_elem(str);

	t_list	*list3 = NULL;

	// Test 1
	res = cmp(list, (char *)"0", std::string("0 1"), i++);
	v.push_back(res);

	// Test 2
	res = cmp(list, (char *)"-1", std::string("-1 0 1"), i++);
	v.push_back(res);

	// Test 3
	res = cmp(&list2, (char *)"0", std::string("0 1"), i++);
	v.push_back(res);

	// Test 4
	res = cmp(&list2, (char *)"-1", std::string("-1 0 1"), i++);
	v.push_back(res);

	// Test 5
	res = cmp(&list3, (char *)"0", std::string("0"), i++);
	v.push_back(res);

	// Test 6
	res = cmp(&list3, (char *)"-1", std::string("-1 0"), i++);
	v.push_back(res);

	ft_list_clear(list, free);
	ft_list_clear(&list2, free);
	ft_list_clear(&list3, free);
	free(list);

	res = printRes(v);
	v.~vector();
	std::exit(res);
}
