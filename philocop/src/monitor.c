/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:25:23 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:25:23 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_table			*table;
	t_philosopher	*philo;
	int				i;
	long long		current_time;
	long long		time_since_last_meal;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = -1;
		current_time = get_timestamp(); // Pobieramy aktualny czas jako long long
		while (++i < table->num_philosophers)
		{
			philo = &table->philosophers[i];
			time_since_last_meal = current_time - philo->last_meal_time;
			if (time_since_last_meal >= table->time_to_die)
			{
				print_state(table, philo->id, "died");
				table->simulation_running = 0;
				return (NULL);
			}
		}
		usleep(500); // Regularne sprawdzanie co 500 µs
	}
	return (NULL);
}

