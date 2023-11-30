/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:51:29 by slippert          #+#    #+#             */
/*   Updated: 2023/11/30 11:22:16 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_args(t_ruler *ruler, char **argv)
{
	if (ft_atoi(argv[0]) <= 0 || !ft_isnumbers(argv[0]))
		return (write(2, "Error: Too few philos!\n", 23), 1);
	ruler->num_of_philos = ft_atoi(argv[0]);
	if (ft_atoi(argv[1]) <= 0 || !ft_isnumbers(argv[1]))
		return (write(2, "Error: Time to die lower or equal 0!\n", 37), 1);
	ruler->time_to_die = ft_atoi(argv[1]);
	if (ft_atoi(argv[2]) <= 0 || !ft_isnumbers(argv[2]))
		return (write(2, "Error: Time to eat lower or equal 0!\n", 37), 1);
	ruler->time_to_eat = ft_atoi(argv[2]);
	if (ft_atoi(argv[3]) <= 0 || !ft_isnumbers(argv[3]))
		return (write(2, "Error: Time to sleep lower or equal 0!\n", 39), 1);
	ruler->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4] && (ft_atoi(argv[4]) < 0 || !ft_isnumbers(argv[4])))
		return (write(2, "Error: Times to eat lower than 0!\n", 34), 1);
	else if (argv[4] && (ft_atoi(argv[4]) >= 0
			&& ft_atoi(argv[4]) <= INT_MAX && ft_isnumbers(argv[4])))
		ruler->eat_times = ft_atoi(argv[4]);
	else
		ruler->eat_times = -1;
	ruler->created_at = get_time_ms();
	ruler->philo_finished = 0;
	ruler->is_done = 0;
	return (0);
}

int	init_mutex(t_ruler *ruler)
{
	int		index;

	index = -1;
	if (pthread_mutex_init(&ruler->lock, NULL))
		return (write(2, "Error: Mutex can't be initialized!\n", 35), 1);
	ruler->forks = malloc(sizeof(pthread_mutex_t) * ruler->num_of_philos);
	if (!ruler->forks)
		return (write(2, "Error: Memory can't be allocated!\n", 34), 1);
	while (++index < ruler->num_of_philos)
		if (pthread_mutex_init(&ruler->forks[index], NULL))
			return (write(2, "Error: Mutex can't be initialized!\n", 35), 1);
	return (0);
}

int	init_philo(t_philo **philo, t_ruler *ruler)
{
	int		index;

	index = 0;
	*philo = malloc(sizeof(t_philo) * ruler->num_of_philos);
	if (!philo)
		return (write(2, "Error: Memory can't be allocated!\n", 34), 1);
	while (index < ruler->num_of_philos)
	{
		(*philo)[index].id = index;
		(*philo)[index].ruler = ruler;
		(*philo)[index].left = index;
		(*philo)[index].right = ((index + 1) % ruler->num_of_philos);
		(*philo)[index].eat_count = 0;
		(*philo)[index].last_meal = get_time_ms();
		index++;
	}
	return (0);
}
