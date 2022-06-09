/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:44:04 by zwina             #+#    #+#             */
/*   Updated: 2021/11/13 13:00:24 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	len = ft_strlen(s);
	while (len--)
		if (s[len] == (char)c)
			return ((char *)(s + len));
	return (0);
}
