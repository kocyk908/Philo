#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philosopher {
    int id;
    long last_meal_time;
    int meals;
    pthread_t thread;
    t_table *table; // Add reference to the Table structure
} t_philosopher;

typedef struct s_table {
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long meals_required;
    t_philosopher *philosophers;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    int simulation_running;
    long start_time; // Add start_time to the Table structure
    int philosophers_finished; // Add philosophers_finished to the Table structure
} t_table;

long    get_timestamp(void);
void    print_state(t_table *table, int id, const char *state);
void    *philo_lifecycle(void *arg);
void    *monitor(void *arg);
long    ft_atol(const char *str);
int     is_positive_integer(const char *str);
int	validate_arguments(int argc, char **argv);
void	initialize_table(t_table *table, int argc, char **argv);
int	initialize_philosophers(t_table *table);
void	create_threads(t_table *table, pthread_t *monitor_thread);
void	join_threads(t_table *table, pthread_t *monitor_thread);
void	cleanup(t_table *table);

#endif