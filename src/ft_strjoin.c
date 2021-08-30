/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:57:17 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/20 23:28:17 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "api.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*ptr;
	int		c;

	c = 0;
	l1 = strlen((char *)s1);
	l2 = strlen((char *)s2);
	ptr = malloc(((l1 + l2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (*s1)
	{
		*(ptr + c) = *s1;
		c++;
		s1++;
	}
	while (*s2)
	{
		*(ptr + c) = *s2;
		c++;
		s2++;
	}
	*(ptr + c) = *s2;
	return (ptr);
}
