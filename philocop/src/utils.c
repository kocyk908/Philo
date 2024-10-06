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

void	print_state(t_table *table, int id, const char *state)
{
	long	elapsed_time;

	pthread_mutex_lock(&table->print_lock);
	if (table->simulation_running)
	{
		elapsed_time = get_timestamp() - table->start_time;
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
