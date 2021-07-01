/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:49:18 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 06:49:56 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mut_forks[philo->lfork]);
	print(philo, FORK);
	pthread_mutex_lock(&philo->data->mut_forks[philo->rfork]);
	print(philo, FORK);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_meal = get_time();
	philo->time_limit = philo->last_meal + philo->data->time_to_die;
	print(philo, EATING);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->mut_forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->mut_forks[philo->rfork]);
	print(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

int	philo_create_odd(t_data *data)
{
	int			i;
	pthread_t	tid;
	t_philo		*philo;

	i = 1;
	while (i < data->nbrs)
	{
		philo = (void *)(&data->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(20);
		i += 2;
	}
	return (0);
}

int	philo_create_even(t_data *data)
{
	int			i;
	pthread_t	tid;
	t_philo		*philo;

	i = 0;
	while (i < data->nbrs)
	{
		philo = (void *)(&data->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(20);
		i += 2;
	}
	return (0);
}
