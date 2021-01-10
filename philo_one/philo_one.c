/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:44 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/01 18:20:46 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int ft_error(char *err)
{
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
    return (EXIT_FAILURE);
}

void    ft_think(t_philo *philo)
{
    philo->stat = THINK;
    pthread_mutex_lock(&mutex);
}

void    ft_take_forks(t_philo *philo)
{
    pthread_mutex_lock(&forks_mutex[philo->id - 1]);
    forks[philo->id - -1] = true;
    pthread_mutex_lock(&forks_mutex[philo->id % nb_of_philos]);
    forks[philo->id % nb_of_philos] = true;

}

void    ft_eat(t_philo *philo)
{
    philo->stat = EAT;

}

void    ft_put_forks(t_philo *philo)
{
    pthread_mutex_unlock(&forks_mutex[philo->id - 1]);
    forks[philo->id - 1] = false;

    pthread_mutex_unlock(&forks_mutex[philo->id % nb_of_philos]);
    forks[philo->id % nb_of_philos] = false;

}

void    ft_sleep(t_philo *philo)
{
    philo->stat = SLEEP;

}

void    *philosophers(void *ptr)
{
    t_philo *philo;

    philo = ptr;
    while (philo->stat != DEAD)
    {
        ft_think(philo);
        ft_take_forks(philo);
        ft_eat(philo);
        ft_put_forks(philo);
        ft_sleep(philo);
    }
    return (NULL);
}

int    init()
{
    int i;

    nb_of_philos = 3;
    time_to_die = 7000 * 1000;
    time_to_eat = 2000 * 1000;
    time_to_sleep = 4000 * 1000;
    nb_of_eat = 0;
    if (pthread_mutex_init(&mutex, NULL) ||
    pthread_mutex_init(&die_mutex, NULL) ||
    pthread_mutex_init(&print_mutex, NULL))
        return (ft_error("mutex init failed!"));
    printf("size of bool: %lu\n", sizeof(bool));
    if (!(g_philos = malloc(sizeof(t_philo) * nb_of_philos)) ||
        !(forks = malloc(sizeof(bool) * nb_of_philos)) ||
        !(forks_mutex = malloc(sizeof(pthread_mutex_t) * nb_of_philos)))
        return (ft_error("malloc failed!"));
    i = 0; 
    while (i < nb_of_philos)
    {
        g_philos[i].id = i + 1;
        g_philos[i].stat = -1;
        if (pthread_create(&g_philos[i].thread, NULL, philosophers, &g_philos[i]))
            return (ft_error("pthread_create failed!"));
        if (pthread_mutex_init(&forks_mutex[i], NULL))
            return (ft_error("mutex init failed!"));

        i++;
    }    
    return (EXIT_SUCCESS);
}

int    run()
{
    pthread_mutex_lock(&die_mutex);
    pthread_mutex_lock(&die_mutex);
    return (EXIT_SUCCESS);
}

int    finalize()
{
    return (EXIT_SUCCESS);
}

int main()
{
    if (init() || run() || finalize())
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}