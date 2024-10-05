/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:24:56 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:24:56 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	print_state(table, philo->id, "is thinking");
}

void	philo_eat(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	print_state(table, philo->id, "has taken a fork");
	if (table->num_philosophers == 1)
	{
		precise_sleep(table->time_to_die, table); // Użycie precise_sleep
		print_state(table, philo->id, "died");
		table->simulation_running = 0;
		pthread_mutex_unlock(&table->forks[philo->id - 1]);
		return ;
	}
	pthread_mutex_lock(&table->forks[philo->id % table->num_philosophers]);
	print_state(table, philo->id, "has taken a fork");
	print_state(table, philo->id, "is eating");
	philo->last_meal_time = get_timestamp(); // Ustawienie czasu ostatniego posiłku
	precise_sleep(table->time_to_eat, table); // Użycie precise_sleep zamiast usleep()
	philo->meals++;
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[philo->id % table->num_philosophers]);
}

void	philo_sleep(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	print_state(table, philo->id, "is sleeping");
	precise_sleep(table->time_to_sleep, table); // Precyzyjnie czekamy
}

void	*philo_lifecycle(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = (t_philosopher *)arg;
	table = philo->table;

	if (philo->id % 2 == 0)
		usleep(500);
	while (table->simulation_running)
	{
		philo_think(philo);
		// if (!table->simulation_running)
		// 	break ;
		philo_eat(philo);
		// if (!table->simulation_running)
		// 	break ;
		if (table->meals_required > 0 && philo->meals >= table->meals_required)
		{
			pthread_mutex_lock(&table->print_lock);
			table->philosophers_finished++;
			if (table->philosophers_finished == table->num_philosophers)
				table->simulation_running = 0;
			pthread_mutex_unlock(&table->print_lock);
			break ;
		}
		philo_sleep(philo);
	}
	return (NULL);
}
