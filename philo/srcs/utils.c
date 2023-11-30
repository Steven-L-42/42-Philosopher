/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:31:29 by slippert          #+#    #+#             */
/*   Updated: 2023/11/30 11:40:14 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = sign * (-2 * (*str == '-') + 1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
}

long long	get_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print_msg(t_ruler *ruler, int id, char *msg)
{
	long long	now;

	now = get_time_ms();
	pthread_mutex_lock(&ruler->lock);
	if (!ruler->is_done)
		printf("%lld %d %s\n", (now - ruler->created_at), id + 1, msg);
	pthread_mutex_unlock(&ruler->lock);
}

int	ft_isnumbers(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

void	pause_time(t_ruler *ruler, long long wait_time)
{
	long long	now;
	long long	start;

	start = get_time_ms();
	while (!(ruler->is_done))
	{
		now = get_time_ms();
		if ((now - start) >= wait_time)
			break ;
		usleep(1);
	}
}
