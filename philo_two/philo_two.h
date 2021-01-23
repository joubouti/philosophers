/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:51 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 19:01:07 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <sys/fcntl.h>
# define DIED		0
# define THINKING	1
# define TAKE_FORKS	2
# define EATING		3
# define SLEEPING	4
# define PUTS_FORKS	5
# define DONE		6
# define BUFF_SIZE	64

typedef long	t_micro_second_t;
typedef enum {
	false,
	true
}	t_bool;

typedef struct		s_philo
{
	pthread_t			thread;
	int					id;
	int					stat;
	int					nb_of_eat;
	t_micro_second_t	last_eat;
}					t_philo;

sem_t				*g_forks_sem;
sem_t				*g_one_at_time;
sem_t				*g_print_sem;
t_philo				*g_philos;
int					g_nb_of_philos;
t_micro_second_t	g_time_to_die;
t_micro_second_t	g_time_to_eat;
t_micro_second_t	g_time_to_sleep;
int					g_nb_of_eat;
t_micro_second_t	g_start_time;
t_bool				g_stat;

size_t				ft_strlen(const char *s);
t_micro_second_t	get_time_stamp();
void				ft_print_status(t_philo *philo);
int					ft_atoi(const char *str);
void				*philosophers(void *ptr);
void				ft_set_stat(t_philo *philo, int stat);
void				ft_think(t_philo *philo);
void				ft_take_forks(t_philo *philo);
void				ft_eat(t_philo *philo);
void				ft_put_forks(t_philo *philo);
void				ft_sleep(t_philo *philo);
int					init(void);
int					ft_error(char *err);

#endif
