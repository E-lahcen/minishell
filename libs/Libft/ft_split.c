/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:38:44 by zwina             #+#    #+#             */
/*   Updated: 2021/11/10 18:32:08 by zwina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_strs(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			i++;
		if (i > 0 && s[i - 1] != c)
			count++;
	}
	return (count);
}

static size_t	ft_len_of_strs(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	ft_free_strs(char **strs, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(strs[i++]);
	free(strs);
	strs = 0;
}

static void	ft_str_to_strs(char **strs, char const *s, char c, size_t n_of_strs)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (i < n_of_strs)
	{
		while (s[j] == c)
			j++;
		if (s[j])
		{
			len = ft_len_of_strs(s + j, c);
			strs[i] = (char *)malloc(sizeof (char) * (len + 1));
			if (!strs[i])
			{
				ft_free_strs(strs, i);
				break ;
			}
			ft_strlcpy(strs[i], s + j, len + 1);
			j += len;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	n_of_strs;
	char	**strs;

	n_of_strs = ft_count_strs(s, c);
	strs = (char **)malloc(sizeof (char *) * (n_of_strs + 1));
	if (!strs)
		return (0);
	ft_str_to_strs(strs, s, c, n_of_strs);
	if (strs)
		strs[n_of_strs] = 0;
	return (strs);
}
