#include "philo.h"

void	*monitor(void *arg)
{
	t_table			*table;
	t_philosopher	*philo;
	int				i;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		i = 0;
		while (i < table->num_philosophers)
		{
			philo = &table->philosophers[i];
			if (get_timestamp() - philo->last_meal_time > table->time_to_die)
			{
				print_state(table, philo->id, "died");
				table->simulation_running = 0;
				return (NULL);
			}
			i++;
		}
		usleep(1000); // Check every millisecond
	}
	return (NULL);
}
