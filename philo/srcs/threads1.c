/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:58:08 by slippert          #+#    #+#             */
/*   Updated: 2023/11/30 11:22:00 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_if_done(t_philo *philo, t_ruler *ruler)
{
	int			index;
	long long	now;

	while (!ruler->is_done)
	{
		if (ruler->eat_times > 0
			&& ruler->philo_finished == ruler->num_of_philos)
		{
			ruler->is_done = 1;
			break ;
		}
		index = 0;
		while (index < ruler->num_of_philos)
		{
			now = get_time_ms();
			if (now - philo[index].last_meal >= ruler->time_to_die)
			{
				print_msg(ruler, index, "died");
				ruler->is_done = 1;
				break ;
			}
			index++;
		}
	}
}

void	free_all_thread(t_philo *philo, t_ruler *ruler)
{
	int	index;

	index = -1;
	while (++index < ruler->num_of_philos)
		pthread_mutex_destroy(&(ruler->forks[index]));
	free(philo);
	free(ruler->forks);
	pthread_mutex_destroy(&(ruler->lock));
}

void	start_threads(t_philo *philo, t_ruler *ruler)
{
	int		index;

	index = -1;
	while (++index < ruler->num_of_philos)
	{
		philo[index].last_meal = get_time_ms();
		if (pthread_create(&philo[index].thread,
				NULL, thread_selector, &philo[index]))
		{
			write(2, "Error: Thread can't be created!\n", 32);
			return ;
		}
	}
	check_if_done(philo, ruler);
	index = -1;
	while (++index < ruler->num_of_philos)
	{
		if (pthread_join(philo[index].thread, NULL))
		{
			write(2, "Error: Thread can't be joined!\n", 32);
			return ;
		}
	}
	free_all_thread(philo, ruler);
}
