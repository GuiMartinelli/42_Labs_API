/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:03:29 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/19 11:53:11 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	c;
	size_t	a;

	c = 0;
	if (!*little)
		return ((char *)big);
	while (*big && c < len)
	{
		a = 0;
		while (*(big + a) == *(little + a))
		{
			if ((c + 1) + a > len)
				return (NULL);
			else if (*(little + (a + 1)) == '\0')
				return ((char *)big);
			a++;
		}
		big++;
		c++;
	}
	return (NULL);
}
