/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <zwina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:44:19 by zwina             #+#    #+#             */
/*   Updated: 2021/11/13 09:39:07 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_size;
	char	*sub;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	else if (s_len > len + start)
		sub_size = len + 1;
	else
		sub_size = s_len - start + 1;
	sub = (char *)malloc(sizeof (char) * sub_size);
	if (!sub)
		return (0);
	ft_strlcpy(sub, s + start, sub_size);
	return (sub);
}
