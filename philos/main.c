/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaglami <mbaglami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:34:31 by mbaglami          #+#    #+#             */
/*   Updated: 2024/01/04 14:28:14 by mbaglami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philo)
	{
		if (table->number_of_philo == 1)
			pthread_detach(table->philos[i].thread);
		pthread_join(table->philos[i].thread, NULL);
	}
	pthread_mutex_destroy(&table->stop_count);
	pthread_mutex_destroy(&table->count_eat);
	pthread_mutex_destroy(&table->eat_last);
	pthread_mutex_destroy(&table->is_die);
	pthread_mutex_destroy(&table->is_print);
	i = 0;
	while (i < table->number_of_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	free (table->forks);
	free (table->philos);
	free (table);
}

t_table	*parse(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->number_of_must_eat = -1;
	if (ac == 6)
		table->number_of_must_eat = ft_atoi(av[5]);
	table->philos = malloc(sizeof(t_philo) * table->number_of_philo);
	if (table->philos == NULL)
		return (NULL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (table->philos == NULL)
		return (NULL);
	table->time = current_time();
	table->stop = 0;
	return (table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ft_control(ac, av) == 0)
		return (1);
	table = parse(ac, av);
	if (table != NULL)
	{
		if (table->number_of_philo > 0)
		{
			start_threads(table);
			end_threads(table);
		}
	}
	return (0);
}
