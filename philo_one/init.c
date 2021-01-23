/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:46:10 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 18:30:06 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_philos(void)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&g_mutex);
	while (i < g_nb_of_philos)
	{
		g_philos[i].id = i + 1;
		g_philos[i].stat = -1;
		g_philos[i].nb_of_eat = 0;
		g_philos[i].last_eat = g_start_time;
		if (pthread_create(&g_philos[i].thread, NULL, philosophers,
		&g_philos[i]))
			return (ft_error("pthread_create failed!"));
		usleep(100);
		i++;
	}
	pthread_mutex_unlock(&g_mutex);
	return (EXIT_SUCCESS);
}

int			init(void)
{
	int i;

	g_stat = true;
	if (pthread_mutex_init(&g_mutex, NULL) ||
	pthread_mutex_init(&g_die_mutex, NULL) ||
	pthread_mutex_init(&g_print_mutex, NULL))
		return (ft_error("mutex init failed!"));
	if (!(g_philos = malloc(sizeof(t_philo) * g_nb_of_philos)) ||
		!(g_forks_mutex = malloc(sizeof(pthread_mutex_t) * g_nb_of_philos)))
		return (ft_error("malloc failed!"));
	i = 0;
	while (i < g_nb_of_philos)
		if (pthread_mutex_init(&g_forks_mutex[i++], NULL))
			return (ft_error("mutex init failed!"));
	g_start_time = get_time_stamp();
	return (init_philos());
}
