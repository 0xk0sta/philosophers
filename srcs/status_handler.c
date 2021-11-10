#include "../includes/philo.h"

void	printer(t_philo philo, int status, size_t in)
{
	pthread_mutex_lock(&philo.table->print);
	if (philo.table->dead == 0
		&& (philo.table->total_e <= philo.table->t_food * philo.table->t_philo))
	{
		if (status == 0)
			printf("%s[%lu ms]|[ %s %zu %s ]\n", GREEN,
				   get_time() - philo.table->time, "Philo", in, "took a fork");
		if (status == 1)
			printf("%s[%lu ms]|[ %s %zu %s ]\n", BLUE,
				   get_time() - philo.table->time, "Philo", in, "is eating");
		if (status == 2)
			printf("%s[%lu ms]|[ %s %zu %s ]\n", MAG,
				   get_time() - philo.table->time, "Philo", in, "is sleeping");
		if (status == 3)
			printf("%s[%lu ms]|[ %s %zu %s ]\n", CYAN,
				   get_time() - philo.table->time, "Philo", in, "is thinking");
	}
	if (status == -1)
		printf("%s[%lu ms]|[ %s %zu %s ]\n", RED,
			   get_time() - philo.table->time, "Philo", in, "is dead");
	pthread_mutex_unlock(&philo.table->print);
}
