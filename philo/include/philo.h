/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:47:03 by slippert          #+#    #+#             */
/*   Updated: 2023/11/30 10:11:11 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	struct s_ruler	*ruler;
	pthread_t		thread;
	long long		last_meal;
	int				eat_count;
}					t_philo;

typedef struct s_ruler
{
	int				is_done;
	int				philo_finished;
	long long		created_at;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}					t_ruler;

// init
int			init_args(t_ruler *ruler, char **argv);
int			init_mutex(t_ruler *ruler);
int			init_philo(t_philo **philo, t_ruler *ruler);

// threads
void		start_threads(t_philo *philo, t_ruler *ruler);
void		*thread_selector(void *data);

// utils
long long	get_time_ms(void);
int			ft_atoi(const char *str);
int			ft_isnumbers(char *str);
void		print_msg(t_ruler *ruler, int id, char *msg);
void		pause_time(t_ruler *info, long long wait_time);

#endif