#include "../includes/philo.h"
#include <fcntl.h>

void	custom_sleep(size_t w_time, t_philo *philo)
{
	size_t	time;

	time = get_time();
	while (philo->table->dead != 1)
	{
		if (get_time() - time >= w_time)
			break ;
		usleep(10);
	}
}

void 	eat_handler(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer(*philo, 0, philo->index);
	if (philo->table->t_philo == 1)
		return ;
	pthread_mutex_lock(&philo->philo_r->fork);
	printer(*philo, 0, philo->index);
	philo->l_eat = get_time();
	printer(*philo, 1, philo->index);
	custom_sleep(philo->table->t_to_eat, philo);
	philo->table->total_e++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->philo_r->fork);
	printer(*philo, 2, philo->index);
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
		if (philo->table->total_e
			>= philo->table->t_food * philo->table->t_philo)
			return (NULL);
		eat_handler(philo);
		if (philo->table->t_philo == 1)
			return (NULL);
		if (philo->table->t_philo > 1)
			think(philo->index, philo);
	}
	return (NULL);
}

void	thread_init(const t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->t_philo)
		pthread_create(&(table->philo[i].th), NULL, philo,
			&table->philo[i]);
}

void	thread_handler(t_table *table)
{
	size_t	i;

	thread_init(table);
	i = -1;
	while (table->dead != 1)
	{
		if (i == table->t_philo - 1)
			i = -1;
		pthread_mutex_lock(&table->death);
		if ((table->total_e
			>= table->t_food * table->t_philo) || get_time()
			- table->philo[++i].l_eat >= table->t_to_die)
		{
			table->dead = 1;
			if (table->total_e < table->t_food * table->t_philo)
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
		usleep(100);
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
	size_t	i;

	i = -1;
	while (++i < table->t_philo)
	{
		table->philo[i].l_eat = table->time;
		table->philo[i].index = i + 1;
		table->philo[i].dead = 0;
		table->philo[i].table = table;
		pthread_mutex_init(&table->philo[i].fork, NULL);
	}
	i = -1;
	while (++i < table->t_philo - 1)
	{
		table->philo[i].philo_l = &table->philo[table->t_philo - i - 1];
		table->philo[i].philo_r = &table->philo[i + 1];
	}
	table->philo[table->t_philo - 1].philo_l = &table->philo[table->t_philo - 2];
	table->philo[table->t_philo - 1].philo_r = &table->philo[0];
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
	table->t_food = -100;
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
