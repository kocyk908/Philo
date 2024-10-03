/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:24:54 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:24:54 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table, pthread_t *monitor_thread)
{
	int	i;

	pthread_create(monitor_thread, NULL, monitor, table);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_create(&table->philosophers[i].thread, NULL,
			philo_lifecycle, &table->philosophers[i]);
		i++;
	}
}

void	join_threads(t_table *table, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(*monitor_thread, NULL);
}
