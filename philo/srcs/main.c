/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:24:51 by slippert          #+#    #+#             */
/*   Updated: 2023/11/30 11:21:44 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_ruler		ruler;
	t_philo		*philo;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: Too much or too few arguments!\n", 38), 1);
	memset(&ruler, 0, sizeof(t_ruler));
	if (init_args(&ruler, argv + 1))
		return (1);
	if (init_mutex(&ruler))
		return (1);
	if (init_philo(&philo, &ruler))
		return (1);
	start_threads(philo, &ruler);
	return (0);
}
//system("leaks philo");
// die 					./philo 1 800 200 200
// no die				./philo 5 800 200 200
// only eat 7 times 	./philo 5 800 200 200 7
// no die 				./philo 4 410 200 200
// one die 				./philo 4 310 200 100
