/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 09:15:32 by guferrei          #+#    #+#             */
/*   Updated: 2022/03/08 09:18:20 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/api.h"

char	*read_token(void)
{
	int		fd;
	void	*token;

	token = malloc(87 * (sizeof(char)));
	fd = open("./src/token.txt", O_RDONLY);
	read(fd, token, 86);
	*(char *)(token + 87) = '\0';
	return ((char *)token);
}
