/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:43:57 by zwina             #+#    #+#             */
/*   Updated: 2021/11/10 18:35:28 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = i;
		k = 0;
		while (haystack[j] == needle[k] && haystack[j] && j < len)
		{
			j++;
			k++;
		}
		if (!needle[k])
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
