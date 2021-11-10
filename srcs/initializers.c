/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:48 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/10 17:51:49 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_init(t_table *table)
{
	size_t	i;
	size_t	index;

	i = -1;
	index = table->t_philo - 1;
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
	table->philo[index].philo_l = &table->philo[table->t_philo - 2];
	table->philo[index].philo_r = &table->philo[0];
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
