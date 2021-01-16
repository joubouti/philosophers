/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:51 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/16 12:57:00 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# define DIED		0
# define THINKING	1
# define TAKE_FORKS	2
# define EATING		3
# define SLEEPING	4
# define PUTS_FORKS	5
# define DONE		6
# define BUFF_SIZE	64


typedef enum { false, true } bool;

typedef long   micro_second_t;

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				stat;
	int				nb_of_eat;
	micro_second_t	last_eat;
}				t_philo;

pthread_mutex_t	*forks_mutex;
pthread_mutex_t	mutex;
pthread_mutex_t	die_mutex;
pthread_mutex_t	print_mutex;
t_philo			*g_philos;
bool			*forks;
int				nb_of_philos;
micro_second_t	time_to_die;
micro_second_t	time_to_eat;
micro_second_t	time_to_sleep;
int				g_nb_of_eat;
micro_second_t	g_start_time;

size_t			ft_strlen(const char *s);
micro_second_t	get_time_stamp();
void			ft_print_status(t_philo *philo);
void			*ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);

#endif