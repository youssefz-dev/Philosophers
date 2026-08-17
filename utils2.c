/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:02:18 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/26 17:41:27 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get(t_list	*philo, int mutex)
{
	long	i;

	i = 0;
	if (mutex == 0)
	{
		(pthread_mutex_lock(&philo->data->start), i = philo->data->start_time);
		pthread_mutex_unlock(&philo->data->start);
	}
	if (mutex == 1)
	{
		(pthread_mutex_lock(&philo->data->eat), i = philo->last_eat);
		pthread_mutex_unlock(&philo->data->eat);
	}
	if (mutex == 2)
	{
		(pthread_mutex_lock(&philo->data->counter), i = philo->data->eat_count);
		pthread_mutex_unlock(&philo->data->counter);
	}
	if (mutex == 3)
		(pthread_mutex_lock(&philo->data->dead), i = philo->data->isdead, \
		pthread_mutex_unlock(&philo->data->dead));
	if (mutex == 4)
		(pthread_mutex_lock(&philo->data->id), i = philo->id), \
		pthread_mutex_unlock(&philo->data->id);
	return (i);
}

void	set(t_list	*philo, int mutex, long val)
{
	if (mutex == 0)
	{
		(pthread_mutex_lock(&philo->data->start), \
		philo->data->start_time = val);
		pthread_mutex_unlock(&philo->data->start);
	}
	if (mutex == 1)
	{
		(pthread_mutex_lock(&philo->data->eat), philo->last_eat = val);
		pthread_mutex_unlock(&philo->data->eat);
	}
	if (mutex == 2)
	{
		pthread_mutex_lock(&philo->data->counter);
		philo->data->eat_count = val;
		pthread_mutex_unlock(&philo->data->counter);
	}
	if (mutex == 3)
	{
		(pthread_mutex_lock(&philo->data->dead), philo->data->isdead = val);
		pthread_mutex_unlock(&philo->data->dead);
	}
}

int	ft_pthread_mutex_init(t_data **data)
{
	if (pthread_mutex_init(&(*data)->print, NULL))
		return (0);
	if (pthread_mutex_init(&(*data)->counter, NULL))
		return (pthread_mutex_destroy(&(*data)->print), 0);
	if (pthread_mutex_init(&(*data)->start, NULL))
		return (pthread_mutex_destroy(&(*data)->print), \
		pthread_mutex_destroy(&(*data)->counter), 0);
	if (pthread_mutex_init(&(*data)->eat, NULL))
		return (pthread_mutex_destroy(&(*data)->print), \
		pthread_mutex_destroy(&(*data)->counter), \
		pthread_mutex_destroy(&(*data)->start), 0);
	if (pthread_mutex_init(&(*data)->dead, NULL))
		return (pthread_mutex_destroy(&(*data)->print), \
		pthread_mutex_destroy(&(*data)->counter), \
		pthread_mutex_destroy(&(*data)->start), \
		pthread_mutex_destroy(&(*data)->eat), 0);
	if (pthread_mutex_init(&(*data)->id, NULL))
		return (pthread_mutex_destroy(&(*data)->print), \
		pthread_mutex_destroy(&(*data)->counter), \
		pthread_mutex_destroy(&(*data)->start), \
		pthread_mutex_destroy(&(*data)->eat), \
		pthread_mutex_destroy(&(*data)->dead), 0);
	return (1);
}

int	destroy_fork(t_list *philo, t_list *head, int i)
{
	if (i == 1)
	{
		while (1)
		{
			philo = philo->prev;
			pthread_detach(philo->philo);
			if (philo->prev == head)
				break ;
		}
		while (1)
		{
			pthread_mutex_destroy(&philo->fork);
			philo = philo->next;
			if (philo->next == head)
				return (0);
		}
	}
	while (1)
	{
		philo = philo->prev;
		pthread_mutex_destroy(&philo->fork);
		if (philo->prev == head)
			return (0);
	}
}

void	ft_destroy(t_data **data)
{
	pthread_mutex_destroy(&(*data)->print);
	pthread_mutex_destroy(&(*data)->counter);
	pthread_mutex_destroy(&(*data)->start);
	pthread_mutex_destroy(&(*data)->eat);
	pthread_mutex_destroy(&(*data)->dead);
	pthread_mutex_destroy(&(*data)->id);
}
