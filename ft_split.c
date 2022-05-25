/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaguiler <aaguiler@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:24:04 by aaguiler          #+#    #+#             */
/*   Updated: 2022/05/25 18:02:05 by aaguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtr;

	if (count + size < count || count + size < size)
		return (0);
	rtr = malloc(count * size);
	if (!rtr)
		return (0);
	ft_bzero(rtr, count * size);
	return (rtr);
}

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	c_words;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	c_words = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			c_words++;
		i++;
	}
	return (c_words);
}

char	*ft_malloc_str(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		n_words;
	char	**strs;
	int		i;

	if (!s)
		return (0);
	n_words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!strs)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			strs[i] = ft_malloc_str(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	strs[i] = 0;
	return (strs);
}
