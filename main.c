/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:49:05 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 07:31:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*monitor_count(void *data_void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)data_void;
	while (i < data->nbrs)
		pthread_mutex_lock(&data->philo[i++].mut_eaten_enough);
	print(&data->philo[0], FINISHED);
	pthread_mutex_lock(&data->mut_exit_thread);
	data->exit_thread = 1;
	pthread_mutex_unlock(&data->mut_exit_thread);
	pthread_mutex_unlock(&data->mut_philo_dead);
	return ((void *)0);
}

void	*monitor(void *data_void)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_void;
	while (1)
	{
		i = -1;
		while (++i < data->nbrs)
		{
			if (data->exit_thread)
				return ((void *)0);
			if (!data->philo[i].eating && get_time() > \
			data->philo[i].time_limit)
			{
				print(&data->philo[i], DYING);
				pthread_mutex_lock(&data->mut_exit_thread);
				data->exit_thread = 1;
				pthread_mutex_unlock(&data->mut_exit_thread);
				pthread_mutex_unlock(&data->mut_philo_dead);
				return ((void *)0);
			}
		}
	}
}

void	*routine(void *philo_void)
{
	t_philo		*philo;

	philo = (t_philo *)philo_void;
	philo->last_meal = philo->data->start;
	philo->time_limit = philo->last_meal + philo->data->time_to_die;
	while (1)
	{
		if (philo->eat_count == philo->data->meal_nbrs)
			pthread_mutex_unlock(&philo->mut_eaten_enough);
		if (philo->data->exit_thread)
			break ;
		print(philo, THINKING);
		eating(philo);
	}
	return ((void *)0);
}

static int	start_thread(t_data *data)
{
	pthread_t	tid;

	data->start = get_time();
	if (philo_create_even(data) || philo_create_odd(data))
		return (1);
	if (data->meal_nbrs > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void *)data) != 0)
			return (1);
		pthread_detach(tid);
	}
	if (pthread_create(&tid, NULL, &monitor, (void *)data) != 0)
		return (1);
	pthread_detach(tid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (exit_error("Wrong nbrs of args\n"));
	if (init(&data, argc, argv))
		return (exit_error("fatal error\n"));
	if (start_thread(&data))
		return (ft_clear_data(&data) && exit_error("fatal error\n"));
	pthread_mutex_lock(&data.mut_philo_dead);
	pthread_mutex_unlock(&data.mut_philo_dead);
	ft_usleep(1000);
	ft_clear_data(&data);
}
