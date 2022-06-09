/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalidvar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:50:45 by zwina             #+#    #+#             */
/*   Updated: 2022/06/05 16:32:43 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isvalidvar(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || c == '?' || c == '0')
		return (1);
	return (0);
}