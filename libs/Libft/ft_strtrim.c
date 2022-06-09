/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:44:12 by zwina             #+#    #+#             */
/*   Updated: 2021/11/10 20:11:42 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first_index;
	size_t	last_index;
	size_t	len;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
	{
		str = ft_strdup(s1);
		return (str);
	}
	first_index = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[first_index]) && first_index < len)
		first_index++;
	last_index = len - 1;
	if (first_index > last_index)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[last_index]))
		last_index--;
	str = ft_substr(s1, first_index, last_index - first_index + 1);
	return (str);
}
