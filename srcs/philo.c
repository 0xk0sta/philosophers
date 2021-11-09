#include "../includes/philo.h"
#include <fcntl.h>

void 	eat_handler(int i, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer(*philo, 0, i);
	pthread_mutex_lock(&philo[i + 1].fork);
	printer(*philo, 0, i); /*STATUS 0 == GRAB FORK*/
	printer(*philo, 1, i); /*STATUS 1 == EAT*/
	philo->l_eat = get_time() - philo->table->time;
	usleep(philo->table->t_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo[i + 1].fork);
	printer(*philo, 2, i); /*STATUS 2 == SLEEP*/
	usleep(philo->table->t_to_sleep * 1000);
}

void	*thread_test(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (philo->table->dead != 1)
	{
		eat_handler(philo->index, philo);
	}
	return (NULL);
}

void	thread_handler(t_table *table)
{
	size_t	i;

	i = -1;
	table->time = get_time();
	while (++i < table->t_philo)
		pthread_create(&(table->philo[i].th), NULL, thread_test,
			&table->philo[i]);
	i = -1;
	while (1)
	{
		if (++i == table->t_philo)
			i = -1;
		pthread_mutex_lock(&table->death);
		if (table->philo[i].l_eat - table->time > table->t_to_die)
		{
			table->dead = 1;
			i = -1;
			printer(*table->philo, -1, table->philo[i].index);
			while (++i < table->t_philo)
				pthread_join(table->philo[i].th, NULL);
			while (++i < table->t_philo)
			{
				pthread_mutex_destroy(&table->philo[i].fork);
				pthread_detach(table->philo[i].th);
			}
			break ;
		}
		pthread_mutex_unlock(&table->death);
	}
}

long	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < (int)table->t_philo)
	{
		table->philo[i].l_eat = table->time;
		table->philo[i].index = i + 1;
		table->philo[i].dead = 0;
		table->philo[i].table = table;
		pthread_mutex_init(&table->philo[i].fork, NULL);
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death, NULL);
}

void	init_struct(t_table *table)
{
	table->t_philo = 0;
	table->t_to_die = 0;
	table->t_to_eat = 0;
	table->t_to_sleep = 0;
	table->t_food = -1;
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("%s\n", USAGE);
		printf("%s\n", OPT);
	}
	init_struct(&table);
	if (argc >= 5)
		table = fill_struct(argc, argv, &table);
	if (validate_args(&table, argc) == 0)
	{
		philo_init(&table);
		thread_handler(&table);
		free(table.philo);
	}
	else
	{
		printf("%s\n", "Invalid arguments.");
		return (1);
	}
}
