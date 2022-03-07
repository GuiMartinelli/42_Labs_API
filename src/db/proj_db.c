/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_db.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:09:52 by guferrei          #+#    #+#             */
/*   Updated: 2022/03/07 08:12:03 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/api.h"


void	proj_db(void)
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
	printf("Connection with Database Established\n");
	sprintf(string, "DROP TABLE %d_projects;", profile.id);
	mysql_query(con, string);
	sprintf(string, "CREATE TABLE %d_projects (project VARCHAR(24), registered_at VARCHAR(10), validated_at VARCHAR(10), finished VARCHAR(15), retries TINYINT, grade VARCHAR(4));", profile.id);
	mysql_query(con, string);
}

void	populate_pdb(void)
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
	sprintf(string, "INSERT INTO %d_projects VALUES(\"%s\", \"%s\", \"%s\", \"%s\", %i, \"%s\");", profile.id, t_project.name, t_project.start, t_project.end, t_project.status, t_project.retries, t_project.grade);
	mysql_query(con, string);
}
