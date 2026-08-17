/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:11:16 by yzoullik          #+#    #+#             */
/*   Updated: 2025/04/26 17:37:36 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data
{
	long			philos_num;
	long			eat_time;
	long			die_time;
	long			sleep_time;
	long			must_eat;
	long			eat_count;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	counter;
	pthread_mutex_t	start;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	id;
	long			isdead;
}				t_data;

typedef struct s_list
{
	pthread_t		philo;
	long			id;
	pthread_mutex_t	fork;
	long			last_eat;
	long			eat;
	long			philos_num;
	long			eat_time;
	long			die_time;
	long			sleep_time;
	long			must_eat;
	long			eat_count;
	t_data			*data;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

int		pars(int ac, char **av);
long	ft_atoi(char *str);
t_list	*ft_init(char **av, t_data *data);
void	ft_freelst(t_list **lst);
long	get_time(void);
t_data	*data_init(char **av);
void	print(t_list *philo, char *str);
void	to_sleep(	t_list	*philo);
void	ft_sleep(t_list *philo, size_t i);
int		death(t_list *philo);
void	take_fork(t_list *philo);
void	drop_fork(t_list *philo);
void	to_eat(t_list *philo);
void	*one_philo(t_list *philo);
long	get(t_list	*philo, int mutex);
void	set(t_list	*philo, int mutex, long val);
int		ft_pthread_mutex_init(t_data **data);
int		destroy_fork(t_list *philo, t_list *head, int i);
void	ft_destroy(t_data **data);

#endif