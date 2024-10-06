/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:24:56 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:24:56 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(long long duration_in_ms, t_table *table)
{
	long long	start_time;
	long long	current_time;

	start_time = get_timestamp();
	current_time = start_time;
	usleep((duration_in_ms - 1) * 1000);
	while (table->simulation_running)
	{
		current_time = get_timestamp();
		if (current_time - start_time >= duration_in_ms)
			break ;
	}
}
// ^^^
// Pobieramy aktualny czas
// Usypiamy prawie cały czas (o 1 milisekundę mniej)
// Czekamy, aż minie dokładnie duration milisekund
