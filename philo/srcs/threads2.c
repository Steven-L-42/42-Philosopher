/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:58:08 by slippert          #+#    #+#             */
/*   Updated: 2023/11/29 19:22:40 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo, t_ruler *ruler)
{
	pthread_mutex_lock(&ruler->forks[philo->left]);
	print_msg(ruler, philo->id, "has taken a fork");
	if (ruler->num_of_philos != 1)
	{
		pthread_mutex_lock(&ruler->forks[philo->right]);
		print_msg(ruler, philo->id, "has taken a fork");
		print_msg(ruler, philo->id, "is eating");
		philo->last_meal = get_time_ms();
		philo->eat_count = philo->eat_count + 1;
		pause_time(ruler, (long long)ruler->time_to_eat);
		pthread_mutex_unlock(&ruler->forks[philo->right]);
	}
	pthread_mutex_unlock(&ruler->forks[philo->left]);
}

void	sleep_and_think(t_philo *philo, t_ruler *ruler)
{
	print_msg(ruler, philo->id, "is sleeping");
	pause_time(ruler, (long long)ruler->time_to_sleep);
	print_msg(ruler, philo->id, "is thinking");
}

void	*thread_selector(void *data)
{
	t_ruler		*ruler;
	t_philo		*philo;

	philo = data;
	ruler = philo->ruler;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
	while (!ruler->is_done)
	{
		eat(philo, ruler);
		if (philo->eat_count == ruler->eat_times)
		{
			ruler->philo_finished++;
			break ;
		}
		sleep_and_think(philo, ruler);
	}
	return ((void *)0);
}
