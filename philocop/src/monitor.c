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
	long			elapsed_time;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = -1;
		while (++i < table->num_philosophers)
		{
			philo = &table->philosophers[i];
			elapsed_time = get_timestamp() - philo->last_meal_time;
			if (elapsed_time > table->time_to_die)
			{
				// Jeśli filozof umarł, dodaj 10 ms do poprzedniego czasu
				long death_time = philo->last_meal_time + table->time_to_die + 10;
				print_state(table, philo->id, "died");
				table->simulation_running = 0;
				return (NULL);
			}
		}
		usleep(100); // Regularne sprawdzanie co 100 µs
	}
	return (NULL);
}
