/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:14:22 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 14:30:16 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

void	store_data(void)
{
	char	string[500];
	MYSQL	*con;

	con = mysql_init(NULL);
	mysql_real_connect(con, "localhost", "guferrei", "user42", "apidb", 3306, NULL, 0);
	if (con == NULL)
	{
		printf("Error : Connection with Database Failed!\n");
		return ;
	}
	sprintf(string, "DELETE FROM users WHERE id = %d;", profile.id);
	mysql_query(con, string);
	sprintf(string, "INSERT INTO users VALUES(\"%s\",%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%i,%i,%i,%i,%s)", profile.login, profile.id, profile.name, profile.campus, profile.start, profile.lvl, profile.lst_proj, profile.n_proj ,profile.n_badge, profile.ev_pts, profile.wallet, profile.staff);
	mysql_query(con, string);
	printf("Data Stored\n");
	mysql_close(con);
}
