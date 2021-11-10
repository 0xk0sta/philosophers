/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:59 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/10 17:52:00 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_handler(t_philo *philo)
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

void	*philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (philo->table->dead != 1)
	{
		if (philo->table->total_e
			>= philo->table->t_food * philo->table->t_philo)
			return (NULL);
		eat_handler(philo);
		if (philo->table->t_philo == 1)
			return (NULL);
		if (philo->table->t_philo > 1)
			printer(*philo, 3, philo->index);
	}
	return (NULL);
}

void	thread_init(const t_table *table)
{
	size_t	i;

	i = -1;
	while (++i < table->t_philo)
		pthread_create(&(table->philo[i].th), NULL, philo, &table->philo[i]);
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
		if ((table->total_e >= table->t_food * table->t_philo) || get_time()
			- table->philo[++i].l_eat >= table->t_to_die)
		{
			table->dead = 1;
			if (table->total_e < table->t_food * table->t_philo)
				printer(table->philo[i], -1, table->philo[i].index);
			i = -1;
			while (++i < table->t_philo)
				pthread_join(table->philo[i].th, NULL);
			while (++i < table->t_philo)
				pthread_mutex_destroy(&table->philo[i].fork);
			return ;
		}
		pthread_mutex_unlock(&table->death);
		usleep(100);
	}
}
