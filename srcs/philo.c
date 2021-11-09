#include "../includes/philo.h"
#include <fcntl.h>

void	custom_sleep(size_t s_time, t_philo *philo)
{
	size_t	time;

	time = get_time();
	while (philo->table->dead != 1)
	{
		if (get_time() - time >= s_time)
			break ;
		usleep(100);
	}
}

void 	eat_handler(size_t i, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer(*philo, 0, i);
	if (philo->table->t_philo == 1)
		return ;
	if (i + 1 >= philo->table->t_philo && philo->table->t_philo != 2)
		i++;
	pthread_mutex_lock(&philo[i + 1].fork);
	printer(*philo, 0, i);
	philo->l_eat = get_time();
	printer(*philo, 1, i);
	philo->table->total_e++;
	custom_sleep(philo->table->t_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo[i + 1].fork);
	printer(*philo, 2, i);
	custom_sleep(philo->table->t_to_sleep, philo);
}

void	think(int i, t_philo *philo)
{
	printer(*philo, 3, i);
}

void	*philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index % 2 == 0)
		usleep(100);
	while (philo->table->dead != 1)
	{
		eat_handler(philo->index, philo);
		if (philo->table->t_philo == 1)
			return (NULL);
		if (philo->table->total_e
			>= philo->table->t_food * philo->table->t_philo)
			return (NULL);
		if (philo->table->t_philo > 1)
			think(philo->index, philo);
	}
	return (NULL);
}

void	thread_handler(t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->t_philo)
		pthread_create(&(table->philo[i].th), NULL, philo,
			&table->philo[i]);
	i = -1;
	while (table->dead != 1)
	{
		if (i == table->t_philo - 1)
			i = -1;
		pthread_mutex_lock(&table->death);
		if (table->total_e == table->t_food * table->t_philo
			|| get_time() - table->philo[++i].l_eat >= table->t_to_die)
		{
			table->dead = 1;
			if (table->total_e != table->t_food * table->t_philo)
				printer(table->philo[i], -1, table->philo[i].index);
			i = -1;
			while (++i < table->t_philo)
				pthread_join(table->philo[i].th, NULL);
			while (++i < table->t_philo)
			{
				pthread_mutex_destroy(&table->philo[i].fork);
				pthread_detach(table->philo[i].th);
			}
			return ;
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
	table->dead = 0;
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
	table->total_e = 0;
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
	{
		if (fill_struct(argc, argv, &table))
			return (EXIT_FAILURE);
	}
	if (validate_args(&table, argc) == 0)
	{
		philo_init(&table);
		thread_handler(&table);
		free(table.philo);
	}
	else
	{
		printf("%s\n", "Invalid arguments.");
		return (EXIT_FAILURE);
	}
}
