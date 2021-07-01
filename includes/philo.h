/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:48:47 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 07:32:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	FORK,
	THINKING,
	DYING,
	FINISHED
}				t_status;

struct	s_data;

typedef struct s_philo
{
	int					id;
	int					eating;
	unsigned long		time_limit;
	unsigned long		last_meal;
	int					lfork;
	int					rfork;
	int					eat_count;
	struct s_data		*data;
	pthread_mutex_t		mutex;
	pthread_mutex_t		mut_eaten_enough;
}						t_philo;

typedef struct s_data
{
	int					exit_thread;
	int					nbrs;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					meal_nbrs;
	unsigned long		start;
	t_philo				*philo;
	pthread_mutex_t		*mut_forks;
	pthread_mutex_t		mut_write;
	pthread_mutex_t		mut_philo_dead;
	pthread_mutex_t		mut_exit_thread;
}						t_data;

void					drop_fork(t_philo *philo);
void					eating(t_philo *philo);
int						exit_error(const char *str);
int						ft_atoi(const char *str);
int						ft_clear_data(t_data *data);
void					*ft_memset(void *b, int c, size_t len);
void					ft_putstr_fd(char *str, int fd);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
int						ft_strlen(const char *str);
void					ft_usleep(unsigned long sleep_time);
unsigned long			get_time(void);
int						init(t_data *data, int argc, char **argv);
int						philo_create_even(t_data *data);
int						philo_create_odd(t_data *data);
void					print(t_philo *philo, t_status status);
void					*routine(void *philo_void);
void					take_fork(t_philo *philo);

#endif
