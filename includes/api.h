/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 08:35:35 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 16:05:29 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_H
# define API_H
# include <string.h>
# include <json-c/json.h>
# include <stdio.h>
# include <stdlib.h>
# include <curl/curl.h>
# include <mysql/mysql.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

struct	s_data
{
	char		login[10];
	int			id;
	char		name[50];
	char		campus[25];
	char		start[11];
	char		lvl[6];
	char		lst_proj[20];
	int			n_proj;
	int			n_badge;
	int			ev_pts;
	int			wallet;
	char		staff[6];
}		profile;

struct	s_project
{
	char	name[25];
	char	start[11];
	int		retries;
	char	status[20];
	char	end[11];
	char	grade[5];
}				t_project;

struct	s_srings
{
	char	profile[320];
	char	*buffer;
}		t_strings;

char	*read_token(void);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	get_login(json_object *parsed_json);
void	get_id(json_object *parsed_json);
void	get_name(json_object *parsed_json);
void	get_campus(json_object *parsed_json);
void	get_start(json_object *parsed_json);
void	get_level(json_object *parsed_json);
void	get_project(json_object *parsed_json);
void	get_n_badges(json_object *parsed_json);
void	get_staff(json_object *parsed_json);
void	get_ev_pts(json_object *parsed_json);
void	get_wallet(json_object *parsed_json);
void	data_filter(void);
void	store_data(void);
int		test_input(void);
void	project_data(void);
void	get_pj_data(json_object *parsed_json);
void	proj_db(void);
void	populate_pdb(void);
void	write_profile(void);
void	write_projects(void);
char	*ft_strjoin(char *s1, char *s2);

#endif