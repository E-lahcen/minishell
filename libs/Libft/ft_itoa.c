/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:37:52 by zwina             #+#    #+#             */
/*   Updated: 2021/11/10 18:21:32 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_topositive(int n)
{
	unsigned int	n_pos;

	if (n > 0)
		n_pos = (unsigned int)n;
	else
		n_pos = (unsigned int)(n * -1);
	return (n_pos);
}

static void	ft_n_str(char *str, int n, unsigned int n_pos, unsigned long ten)
{
	if (n == 0)
		*(str++) = '0';
	else
	{
		if (n < 0)
			*(str++) = '-';
		while (ten / 10)
		{
			*(str++) = (n_pos % ten) / (ten / 10) + '0';
			ten /= 10;
		}
	}
	*str = 0;
}

char	*ft_itoa(int n)
{
	unsigned long	ten;
	unsigned int	n_pos;
	size_t			size;
	char			*str;

	size = 1;
	n_pos = ft_topositive(n);
	if (n <= 0)
		size++;
	ten = 1;
	while (n_pos / ten)
	{
		ten *= 10;
		size++;
	}
	str = (char *)malloc(sizeof (char) * size);
	if (!str)
		return (0);
	ft_n_str(str, n, n_pos, ten);
	return (str);
}
