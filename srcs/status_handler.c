#include "../includes/philo.h"

void	printer(t_philo philo, int status, int index)
{
	if (status == 0)
	{
		printf("[ %lu ms ]  [ %s %d %s ]%s\n", get_time() - philo.table->time,
			   "Philo", index, "took a fork", EF);
	}
	if (status == 1)
		printf("[ %lu ms ]  [ %s %d %s ]%s\n", get_time() - philo.table->time,
			   "Philo", index, "is eating", EF);
	if (status == 2)
		printf("[ %lu ms ]  [ %s %d %s ]%s\n", get_time() - philo.table->time,
			   "Philo", index, "is sleeping", ES);
}
