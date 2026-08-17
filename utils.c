/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:43:06 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/27 10:10:39 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(t_list *philo, size_t i)
{
	if (get(philo, 3) == 1)
		return ;
	if (i > (size_t) philo->die_time * 1000)
	{
		usleep((philo->die_time + 1) * 1000);
		return ;
	}
	usleep(i);
}

void	print(t_list *philo, char *str)
{
	if (get(philo, 3) == 1)
		return ;
	pthread_mutex_lock(&philo->data->print);
	if (get(philo, 3) != 1)
		printf("%ld %ld %s\n", get_time() - get(philo, 0), get(philo, 4), str);
	pthread_mutex_unlock(&philo->data->print);
}

void	to_sleep(t_list	*philo)
{	
	print(philo, "is sleeping");
	ft_sleep(philo, philo->sleep_time * 1000);
	print(philo, "is thinking");
	usleep(600);
}
