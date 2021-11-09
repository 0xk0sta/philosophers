#include "../includes/philo.h"
#include <fcntl.h>

void 	eat_handler(int i, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer(*philo, 0, i);
	pthread_mutex_lock(&philo[i - 1].fork);
	printer(*philo, 0, i);
	printer(*philo, 1, i);
	usleep(philo->table->t_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo[i - 1].fork);
	/* sleep */
	printer(*philo, 2, i);
	usleep(philo->table->t_to_sleep);
}

void	*thread_test(void *p)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p;
	i = -1;
	if (philo->index % 2)
		usleep(1000);
	while (philo->dead != 1)
		eat_handler(philo->index, philo);
	return (NULL);
}

void	thread_handler(t_table *table)
{
	unsigned long		i;

	i = -1;
	while (++i < table->t_philo)
		pthread_create(&(table->philo[i].th), NULL, thread_test,
			 &table->philo[i]);
	i = -1;
	while (++i < table->t_philo)
		pthread_join(table->philo[i].th, NULL);
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
		table->philo[i].index = i + 1;
		table->philo[i].dead = 0;
		pthread_mutex_init(&table->philo[i].fork, NULL);
	}
}

static void	init_struct(t_table *table)
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
	}
	else
	{
		printf("%s\n", "Invalid arguments.");
		return (1);
	}
}
