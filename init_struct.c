/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:48:58 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 06:48:59 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mut_write, NULL);
	pthread_mutex_init(&data->mut_exit_thread, NULL);
	pthread_mutex_init(&data->mut_philo_dead, NULL);
	pthread_mutex_lock(&data->mut_philo_dead);
	data->mut_forks = (pthread_mutex_t *)malloc(sizeof(*(data->mut_forks))
			* data->nbrs);
	if (!data->mut_forks)
		return (1);
	while (i < data->nbrs)
		pthread_mutex_init(&data->mut_forks[i++], NULL);
	return (0);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbrs)
	{
		data->philo[i].eating = 0;
		data->philo[i].id = i;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->nbrs;
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].mutex, NULL);
		pthread_mutex_init(&data->philo[i].mut_eaten_enough, NULL);
		pthread_mutex_lock(&data->philo[i].mut_eaten_enough);
		i++;
	}
}

int	init(t_data *data, int argc, char **argv)
{
	data->nbrs = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->meal_nbrs = ft_atoi(argv[5]);
		if (!data->meal_nbrs)
			return (1);
	}
	else
		data->meal_nbrs = -1;
	if (data->nbrs < 2 || data->nbrs > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (1);
	data->mut_forks = NULL;
	data->philo = NULL;
	data->exit_thread = 0;
	data->philo = (t_philo *)malloc(sizeof(*(data->philo))
			* data->nbrs);
	if (!data->philo)
		return (1);
	init_philo(data);
	return (init_mutexes(data));
}
