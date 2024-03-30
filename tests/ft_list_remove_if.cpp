#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "libasm.h"


// void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(const char *, const char *), void (*free_fct)(void *))
// {
// 	t_list	*node = *begin_list;
// 	t_list	*prev = NULL;

// 	while (node)
// 	{
// 		if (cmp((const char*)node->data, (const char*)data_ref) == 0)
// 		{
// 			if (prev)
// 				prev->next = node->next;
// 			else
// 				*begin_list = node->next;
// 			free_fct(node->data);
// 			free(node);
// 			node = prev ? prev->next : *begin_list;
// 		}
// 		else
// 		{
// 			prev = node;
// 			node = node->next;
// 		}
// 	}
// }

t_list **gen_list(int start, int end)
{
	t_list **list = (t_list**)calloc(1, sizeof(t_list*));
	*list = ft_list_new((void *)strdup("a"));
	t_list *head = *list;
	char	arr[2] = "a";

	for (int i = start; i <= end; i++)
	{
		arr[0] = (char)('a' + i);
		t_list	*node = ft_list_new((void *)strdup(arr));
		head->next = node;
		head = node;
	}

	head->next = ft_list_new((void *)strdup("c"));
	head->next->next = ft_list_new((void *)strdup("d"));
	head->next->next->next = ft_list_new((void *)strdup("c"));
	return list;
}

int main(void)
{
	t_list	**list = gen_list(1, 5);
	t_list	*lol = ft_list_new((void *)strdup("z"));
	// lol->next = ft_list_new((void *)strdup("a"));
	// ft_list_remove_if(list, (void*)"z", strcmp, free);
	ft_list_remove_if(&lol, (void*)"z", strcmp, free);

	*list = lol;
	t_list	*node = *list;
	while (node)
	{
		printf("%s ", (char *)node->data);
		node = node->next;
	}
	printf("\n");
}
