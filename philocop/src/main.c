/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:25:26 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:25:26 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atol(argv[5]);
	else
		table->meals_required = -1;
	table->simulation_running = 1;
	table->start_time = get_timestamp();
	table->philosophers_finished = 0;
}

int	initialize_philosophers(t_table *table)
{
	int	i;

	i = 0;
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->num_philosophers);
	if (!table->philosophers)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
	if (!table->forks)
	{
		free(table->philosophers);
		return (1);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	while (i < table->num_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal_time = get_timestamp();
		table->philosophers[i].meals = 0;
		table->philosophers[i].table = table;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (0);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->philosophers);
	free(table->forks);
}

int	main(int argc, char **argv)
{
	pthread_t	monitor_thread;
	t_table		table;

	if (validate_arguments(argc, argv))
		return (0);
	initialize_table(&table, argc, argv);
	if (initialize_philosophers(&table))
		return (0);
	create_threads(&table, &monitor_thread);
	join_threads(&table, &monitor_thread);
	cleanup(&table);
	return (0);
}
