/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:52 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/10 17:51:53 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
