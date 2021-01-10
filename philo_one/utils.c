#include "philo_one.h"

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void	ft_putnbr(int n)
{
	char c;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n / 10)
		ft_putnbr_fd(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}

void    ft_print_status(int status)
{
    
}