/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:46:10 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 19:22:07 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_philos(void)
{
	int	i;

	i = 0;
	while (i < g_nb_of_philos)
	{
		g_philos[i].id = i + 1;
		g_philos[i].stat = -1;
		g_philos[i].nb_of_eat = 0;
		g_philos[i].last_eat = g_start_time;
		if ((g_philos[i].pid = fork()) == 0)
			philosophers(&g_philos[i]);
		else if (g_philos[i].pid < 0)
			return (ft_error("fork failed!"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int		init(void)
{
	if (!(g_philos = malloc(sizeof(t_philo) * g_nb_of_philos)))
		return (ft_error("malloc failed!"));
	sem_unlink("g_forks_sem");
	sem_unlink("g_one_at_time");
	sem_unlink("g_print_sem");
	if ((g_forks_sem = sem_open("g_forks_sem", O_CREAT, S_IRWXG,
	g_nb_of_philos)) == SEM_FAILED || (g_one_at_time = sem_open("g_one_at_time",
	O_CREAT, S_IRWXG, 1)) == SEM_FAILED || (g_print_sem = sem_open("g_print_sem"
	, O_CREAT, S_IRWXG, 1)) == SEM_FAILED)
		return (ft_error("failed to open semaphore"));
	g_start_time = get_time_stamp();
	g_stat = true;
	return (init_philos());
}
