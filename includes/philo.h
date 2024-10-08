/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:25:30 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:25:30 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int			id;
	long		last_meal_time;
	int			meals;
	pthread_t	thread;
	t_table		*table;
}				t_philosopher;

typedef struct s_table
{
	int				num_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_required;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				simulation_running;
	long long		start_time;
	int				philosophers_finished;
}					t_table;

// main

void		initialize_table(t_table *table, int argc, char **argv);
int			initialize_philosophers(t_table *table);
void		cleanup(t_table *table);

// monitor

void		*monitor(void *arg);

// routine

void		*philo_lifecycle(void *arg);

// threads

void		create_threads(t_table *table, pthread_t *monitor_thread);
void		join_threads(t_table *table, pthread_t *monitor_thread);

// utils

void		print_state(t_table *table, int id, const char *state);
void		precise_sleep(long long time, t_table *table);
int			is_positive_integer(const char *str);
int			validate_arguments(int argc, char **argv);
long		ft_atol(const char *str);
long long	get_timestamp(void);

#endif
