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
# include <sys/time.h>

typedef struct  s_philo
{
    pthread_t   thread;
    int         id;
    int         stat;
}               t_philo;

pthread_mutex_t mutex;
pthread_mutex_t die_mutex;
pthread_mutex_t print_mutex;
t_philo         *g_philos;
int             nb_of_philos;
int             time_to_die;
int             time_to_eat;
int             time_to_sleep;
int             nb_of_eat;


#endif