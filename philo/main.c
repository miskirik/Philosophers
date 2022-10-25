/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miskirik <miskirik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:29:47 by miskirik          #+#    #+#             */
/*   Updated: 2022/10/25 00:29:50 by miskirik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if ((ft_check_args(argc, argv)))
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	ft_table_init(table, argc, argv);
	ft_table_loop(table);
	ft_table_free(table);
	return (0);
}
