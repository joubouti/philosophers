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


int    init()
{
    if (pthread_mutex_init(&mutex, NULL) ||
    pthread_mutex_init(&die_mutex, NULL) ||
    pthread_mutex_init(&print_mutex, NULL))
    {
        write(2, "mutex init failed!", 19);
        return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}

int    run()
{
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