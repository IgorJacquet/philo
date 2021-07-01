/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:49:39 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 06:49:45 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

unsigned long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000));
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*i;

	if (b == 0)
		return (NULL);
	if (len == 0)
		return (b);
	i = b;
	while (len--)
	{
		*i = (unsigned char)c;
		if (len)
			i++;
	}
	return (b);
}

int	ft_clear_data(t_data *data)
{
	int	i;

	if (data->mut_forks)
	{
		i = 0;
		while (i < data->nbrs)
			pthread_mutex_destroy(&data->mut_forks[i++]);
		free(data->mut_forks);
	}
	if (data->philo)
	{
		i = 0;
		while (i < data->nbrs)
			pthread_mutex_unlock(&data->philo[i++].mut_eaten_enough);
		i = 0;
		while (i < data->nbrs)
		{
			pthread_mutex_destroy(&data->philo[i].mutex);
			pthread_mutex_destroy(&data->philo[i++].mut_eaten_enough);
		}
		free(data->philo);
	}
	pthread_mutex_destroy(&data->mut_write);
	pthread_mutex_destroy(&data->mut_philo_dead);
	return (1);
}

int	exit_error(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}
