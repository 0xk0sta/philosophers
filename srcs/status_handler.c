#include "../includes/philo.h"

void	printer(t_philo philo, int status, size_t in)
{
	pthread_mutex_lock(&philo.table->print);
	if (philo.table->dead == 0)
	{
		if (status == 0)
			printf("%s[%lu ms]|[ %s %zu %s %s]\n", GREEN,
				   get_time() - philo.table->time, "Philo", in, "took a fork",
				   EF);
		if (status == 1)
			printf("%s[%lu ms]|[ %s %zu %s %s]\n", BLUE,
				   get_time() - philo.table->time, "Philo", in, "is eating",
				   EF);
		if (status == 2)
			printf("%s[%lu ms]|[ %s %zu %s %s]\n", MAG,
				   get_time() - philo.table->time, "Philo", in, "is sleeping",
				   ES);
		if (status == 3)
			printf("%s[%lu ms]|[ %s %zu %s %s]\n", CYAN,
				   get_time() - philo.table->time, "Philo", in, "is thinking",
				   ET);
	}
	if (status == -1)
		printf("%s[%lu ms]|[ %s %zu %s %s]\n", RED,
			   get_time() - philo.table->time, "Philo", in, "is dead", DD);
	pthread_mutex_unlock(&philo.table->print);
}
