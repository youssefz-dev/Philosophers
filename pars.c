/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:39:34 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/15 15:05:09 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

void	ft_signal(char c, long *signal, size_t *i)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			(*signal) = -1;
		(*i)++;
	}
}

long	ft_atoi(char *str)
{
	size_t		i;
	long long	res;
	long		signal;

	i = 0;
	res = 0;
	signal = 1;
	while ((str[i] && str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_signal(str[i], &signal, &i);
	while (str[i] && ft_isdigit(str[i]))
	{
		if (i >= 18)
			break ;
		res = (res * 10) + (str[i++] - 48);
	}
	return (res * signal);
}

int	ft_digitcheck(char *s)
{
	int	i;

	i = 0;
	if (s[i] && (s[i] == '-' || s[i] == '+') && ft_isdigit(s[i + 1]))
		i++;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	if (ft_atoi(s) > INT_MAX || ft_atoi(s) <= 0)
		return (0);
	return (1);
}

int	pars(int ac, char **av)
{
	int	i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (av[i])
			if (!ft_digitcheck(av[i++]))
				return (write(2, "Error\n", 6), 0);
		return (1);
	}
	return (write(2, "Error\n", 6), 0);
}
