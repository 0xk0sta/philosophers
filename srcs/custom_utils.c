/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:38 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/10 17:51:40 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	custom_sleep(size_t w_time, t_philo *philo)
{
	size_t	time;

	time = get_time();
	while (philo->table->dead != 1)
	{
		if (get_time() - time >= w_time)
			break ;
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
