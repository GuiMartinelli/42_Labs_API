/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:17:35 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 14:32:08 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

int	test_input(void)
{
	FILE				*fd;
	char				buffer[100000];

	fd = fopen("./src/response.json", "r");
	fread(buffer, 100000, 1, fd);
	fclose(fd);
	if (ft_strnstr(buffer, "{}", 3))
		return (1);
	else if (ft_strnstr(buffer, "authorized", 50))
		return (2);
	else
		return (0);
}
