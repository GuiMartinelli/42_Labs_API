/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 09:15:32 by guferrei          #+#    #+#             */
/*   Updated: 2022/03/07 08:45:22 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/api.h"

void	token_format(char *token)
{
	while (*token != '"')
		token++;
	*token = '\0';
}

char	*read_token(void)
{
	int		fd;
	void	*token;

	token = malloc(87 * (sizeof(char)));
	fd = open("./src/token/token.txt", O_RDONLY);
	read(fd, token, 86);
	*(char *)(token + 87) = '\0';
	token_format((char *)token);
	printf("%s\n", (char *)token);
	return ((char *)token);
}
