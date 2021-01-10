/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:51 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/01 18:20:52 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# define DEAD 0
# define EAT 1
# define THINK 2
# define SLEEP 3


typedef enum { false, true } bool;

typedef struct  s_philo
{
    pthread_t   thread;
    int         id;
    int         stat;
}               t_philo;

pthread_mutex_t *forks_mutex;
pthread_mutex_t *mutex;
pthread_mutex_t die_mutex;
pthread_mutex_t print_mutex;
t_philo         *g_philos;
bool             *forks;
int             nb_of_philos;
int             time_to_die;
int             time_to_eat;
int             time_to_sleep;
int             nb_of_eat;

size_t  ft_strlen(const char *s);

#endif