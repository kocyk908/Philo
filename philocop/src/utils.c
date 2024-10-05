/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:24:51 by lkoc              #+#    #+#             */
/*   Updated: 2024/10/03 17:24:51 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

long long get_timestamp(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((long long)(time.tv_sec * 1000) + (time.tv_usec / 1000)); // Zwracamy czas w milisekundach jako long long
}

// Zwraca czas w milisekundach

void precise_sleep(long long duration_in_ms, t_table *table)
{
    long long start_time;
    long long current_time;

    start_time = get_timestamp(); // Pobieramy aktualny czas
    current_time = start_time;

    // Używamy bardziej precyzyjnego sprawdzania czasu
    while ((current_time - start_time < duration_in_ms) && table->simulation_running)
    {
        usleep(100); // Krótkie przerwy, aby nie przeciążać CPU
        current_time = get_timestamp(); // Aktualizujemy bieżący czas
    }
}


// Pobieramy aktualny czas
// Usypiamy prawie cały czas (o 1 milisekundę mniej)
// Czekamy, aż minie dokładnie duration milisekund

void	print_state(t_table *table, int id, const char *state)
{
	long	elapsed_time;

	pthread_mutex_lock(&table->print_lock);
	if (table->simulation_running)
	{
		elapsed_time = get_timestamp() - table->start_time;
		// Sprawdzamy, czy nie ustawiliśmy z góry czasu śmierci
		if (strcmp(state, "died") == 0)
		{
			elapsed_time = table->time_to_die; // Dodaj 10 ms
		}
		printf("%ld %d %s\n", elapsed_time, id, state);
	}
	pthread_mutex_unlock(&table->print_lock);
}

int	is_positive_integer(const char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s num_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep [meals_required]\n");
		return (1);
	}
	while (i < argc)
	{
		if (!is_positive_integer(argv[i]))
		{
			printf("Error: All args must be positive integers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
