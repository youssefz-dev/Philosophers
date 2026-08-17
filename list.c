/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:41:52 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/26 17:37:48 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_lstnew(int id, t_data *data)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (0);
	list->id = id;
	list->last_eat = 0;
	list->eat = 0;
	list->philos_num = data->philos_num;
	list->die_time = data->die_time;
	list->eat_time = data->eat_time;
	list->sleep_time = data->sleep_time;
	list->must_eat = data->must_eat;
	list->data = data;
	return (list->next = 0, list->prev = 0, list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		new->next = new;
		new->prev = new;
		*lst = new;
	}
	else
	{
		last = (*lst)->prev;
		new->next = (*lst);
		new->prev = last;
		last->next = new;
		(*lst)->prev = new;
	}
}

t_list	*ft_init(char **av, t_data *data)
{
	t_list	*list;
	int		i;

	i = 1;
	list = 0;
	while (i <= ft_atoi(av[1]))
		ft_lstadd_back(&list, ft_lstnew(i++, data));
	return (list);
}

void	ft_freelst(t_list **lst)
{
	t_list	*head;
	t_list	*node;

	if (!lst || !*lst)
		return ;
	head = *lst;
	node = (*lst)->next;
	free(*lst);
	*lst = node;
	while (*lst != head)
	{
		node = (*lst)->next;
		free(*lst);
		*lst = node;
	}
}

t_data	*data_init(char **av)
{
	t_data	*list;

	list = malloc(sizeof(t_data));
	if (!list)
		return (0);
	list->philos_num = ft_atoi(av[1]);
	list->die_time = ft_atoi(av[2]);
	list->eat_time = ft_atoi(av[3]);
	list->sleep_time = ft_atoi(av[4]);
	list->must_eat = -1;
	if (av[5])
		list->must_eat = ft_atoi(av[5]);
	list->isdead = 0;
	list->eat_count = 0;
	list->start_time = 0;
	return (list);
}
