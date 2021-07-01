/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 06:49:33 by igor              #+#    #+#             */
/*   Updated: 2021/07/01 06:54:39 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	ft_usleep(unsigned long sleep_time)
{
	unsigned long	end;

	end = get_time() + sleep_time;
	while (get_time() < end)
		usleep(100);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dest;
	const char	*source;
	size_t		i;
	size_t		dlen;

	dest = dst;
	source = src;
	i = size;
	while (i-- != 0 && *dest)
		dest++;
	dlen = dest - dst;
	i = size - dlen;
	if (i == 0)
		return (dlen + ft_strlen(source));
	while (*source)
	{
		if (i != 1)
		{
			*dest++ = *source;
			i--;
		}
		source++;
	}
	*dest = '\0';
	return (dlen + (source - src));
}

int	ft_atoi(char const *str)
{
	int	i;
	int	is_neg;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		is_neg = -1;
	else
		is_neg = 1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * is_neg);
}
