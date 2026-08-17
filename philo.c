/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:11:12 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/26 18:01:37 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->philos_num == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (get(philo, 3) == 1)
			break ;
		take_fork(philo);
		to_eat(philo);
		drop_fork(philo);
		to_sleep(philo);
	}
	return (0);
}

int	create_philo(t_list *philo)
{
	t_list	*head;

	head = philo;
	while (1)
	{
		if (pthread_mutex_init(&philo->fork, NULL))
			return (destroy_fork(philo, head, 0));
		philo = philo->next;
		if (philo == head)
			break ;
	}
	philo->data->start_time = get_time();
	while (1)
	{
		if (pthread_create(&philo->philo, NULL, &run, philo))
			return (destroy_fork(philo, head, 1));
		philo = philo->next;
		if (philo == head)
			break ;
	}
	return (1);
}

int	wait_philo(t_list *philo, t_list *head)
{
	philo = head;
	while (1)
	{
		if (pthread_join(philo->philo, NULL))
			pthread_detach(philo->philo);
		philo = philo->next;
		if (philo == head)
			break ;
	}
	while (1)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
		if (philo == head)
			break ;
	}
	return (1);
}

int	checker(int ac, char **av, t_data **data, t_list **philo)
{
	if (!pars(ac, av))
		return (0);
	*data = data_init(av);
	if (!data || !*data)
		return (write(2, "Error\n", 7), 0);
	if (!ft_pthread_mutex_init(data))
		return (0);
	*philo = ft_init(av, *data);
	if (!philo || !*philo)
	{
		write(2, "Error\n", 7);
		ft_destroy(data);
		free(*data);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_list	*philo;
	t_data	*data;
	t_list	*head;

	data = 0;
	philo = 0;
	if (!checker(ac, av, &data, &philo))
		return (1);
	head = philo;
	if (!create_philo(philo))
		return (ft_destroy(&data), ft_freelst(&philo), free(data), 1);
	while (1)
	{
		usleep(500);
		if (death(philo))
			break ;
		philo = philo->next;
	}
	wait_philo(philo, head);
	ft_destroy(&data);
	ft_freelst(&philo);
	free(data);
	return (0);
}
