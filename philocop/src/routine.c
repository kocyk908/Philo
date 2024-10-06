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
	int		left_fork;
	int		right_fork;

	table = philo->table;
	left_fork = philo->id - 1;
	right_fork = philo->id % table->num_philosophers;
	if (table->num_philosophers == 1)
	{
		print_state(table, philo->id, "has taken a fork");
		precise_sleep(table->time_to_die, table);
		print_state(table, philo->id, "died");
		table->simulation_running = 0;
		return ;
	}
	// Zabezpieczenie na wypadek jednego filozofa
	pthread_mutex_lock(&table->forks[left_fork]);
	print_state(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[right_fork]);
	print_state(table, philo->id, "has taken a fork");
	print_state(table, philo->id, "is eating");
	philo->last_meal_time = get_timestamp(); // Aktualizacja czasu ostatniego posiłku
	precise_sleep(table->time_to_eat, table);
	philo->meals++;

	pthread_mutex_unlock(&table->forks[left_fork]);
	pthread_mutex_unlock(&table->forks[right_fork]);
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

	//if (philo->id % 2 == 0)
	//	usleep(500);
	usleep(philo->id * 100);
	while (table->simulation_running)
	{
		philo_eat(philo);
		philo_think(philo);
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
