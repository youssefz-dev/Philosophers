/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:55:09 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/26 17:43:04 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_list *philo)
{
	long	time;

	time = get_time() - get(philo, 0) - get(philo, 1);
	if (time > philo->data->die_time)
	{
		set(philo, 3, 1);
		usleep(1000);
		printf("%ld %ld %s\n", get_time() - \
		get(philo, 0), get(philo, 4), "died");
		return (1);
	}
	if (get(philo, 2) == philo->data->philos_num)
	{
		set(philo, 3, 1);
		return (1);
	}
	return (0);
}

void	take_fork(t_list *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*sec;

	first = &philo->fork;
	sec = &philo->next->fork;
	if (get(philo, 4) > get(philo->next, 4))
	{
		first = &philo->next->fork;
		sec = &philo->fork;
	}
	pthread_mutex_lock(first);
	print(philo, "has taken a fork");
	pthread_mutex_lock(sec);
	print(philo, "has taken a fork");
	set(philo, 1, get_time() - get(philo, 0));
}

void	drop_fork(t_list *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	to_eat(t_list *philo)
{
	print(philo, "is eating");
	philo->eat++;
	ft_sleep(philo, philo->eat_time * 1000);
	if (philo->eat == philo->must_eat)
	{
		pthread_mutex_lock(&philo->data->counter);
		philo->data->eat_count++;
		pthread_mutex_unlock(&philo->data->counter);
	}
}

void	*one_philo(t_list *philo)
{
	pthread_mutex_lock(&philo->fork);
	print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->fork);
	set(philo, 1, get_time() - get(philo, 0));
	ft_sleep(philo, philo->die_time * 1000);
	return (0);
}
