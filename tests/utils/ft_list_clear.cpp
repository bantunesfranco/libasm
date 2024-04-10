#include "libasm.h"
#include <cstdlib>

void		ft_list_clear(t_list **begin_list, void (*free_fct)(void *))
{
	t_list *head;
	t_list *next;

	if (!begin_list)
		return;
	head = *begin_list;
	while (head)
	{
		next = head->next;
		(*free_fct)(head->data);
		free(head);
		head = next;
	}
}
