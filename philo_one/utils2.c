/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 12:29:17 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/16 12:50:20 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_return(long num, int add, int sign)
{
	if (sign == 1 && (num > 922337203685477580 ||
	(num == 922337203685477580 && add > 7)))
		return (-1);
	else if (sign == -1 && (num > 922337203685477580 && add > 8))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	num;
	int			i;
	int			neg;

	num = 0;
	i = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		neg = -*str + 44;
		i++;
	}
	else if (*str == ' ' || (*str > 8 && *str < 14))
		return (ft_atoi((str + 1)));
	while (*(str + i))
	{
		if (ft_return(num, *(str + i) - 48, neg) != 1)
			return (ft_return(num, *(str + i) - 48, neg));
		if (*(str + i) < 58 && *(str + i) > 47)
			num = num * 10 + (*(str + i) - 48);
		else
			break ;
		i++;
	}
	return ((num * neg));
}