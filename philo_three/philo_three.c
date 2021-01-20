/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:44 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 19:17:57 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	g_turn = 0;

void	*ft_check_die(void *ptr)
{
	t_philo				*philo;
	t_micro_second_t	mc;

	philo = ptr;
	while (philo->stat != DONE)
	{
		mc = get_time_stamp();
		if ((mc - philo->last_eat > g_time_to_die) && philo->stat != EATING)
		{
			g_stat = false;
			philo->stat = DIED;
			ft_print_status(philo);
			exit(2);
		}
	}
	return (NULL);
}

void	philosophers(void *ptr)
{
	t_philo *philo;

	philo = ptr;
	if (pthread_create(&philo->thread, NULL, ft_check_die, philo))
		exit(ft_error("pthread_create failed!"));
	while (g_stat && (g_nb_of_eat == -1 || philo->nb_of_eat < g_nb_of_eat))
	{
		ft_think(philo);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
	}
	ft_set_stat(philo, DONE);
	exit(EXIT_SUCCESS);
}

int		run(void)
{
	int	i;
	int j;
	int	status;

	i = 0;
	while (i < g_nb_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			j = 0;
			while (j < g_nb_of_philos)
				kill(g_philos[j++].pid, 9);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		finalize(void)
{
	sem_unlink("g_forks_sem");
	sem_unlink("g_one_at_time");
	sem_unlink("g_print_sem");
	free(g_philos);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("usage: ./philo_one number_of_philosophers"
		"g_time_to_die g_time_to_eat g_time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]"));
	g_nb_of_philos = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]) * 1000;
	g_time_to_eat = ft_atoi(argv[3]) * 1000;
	g_time_to_sleep = ft_atoi(argv[4]) * 1000;
	g_nb_of_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	if (g_nb_of_philos < 0 || g_time_to_die < 0 || g_time_to_eat < 0 ||
	g_time_to_sleep < 0 || g_nb_of_eat < -1)
		return (EXIT_FAILURE);
	if (init() || run() || finalize())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
