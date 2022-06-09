/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:24:37 by zwina             #+#    #+#             */
/*   Updated: 2021/11/08 11:39:59 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_pos;

	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	n_pos = n;
	if (n_pos > 9)
		ft_putnbr_fd(n_pos / 10, fd);
	ft_putchar_fd((n_pos % 10) + '0', fd);
}
