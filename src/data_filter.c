/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 08:29:13 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 14:43:30 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

void	data_filter(void)
{
	FILE				*jfile;
	char				buffer[100000];
	struct json_object	*parsed_json;

	jfile = fopen("./src/response.json", "r");
	fread(buffer, 100000, 1, jfile);
	fclose(jfile);
	parsed_json = json_tokener_parse(buffer);
	
	get_login(parsed_json);
	get_id(parsed_json);
	get_name(parsed_json);
	get_campus(parsed_json);
	get_staff(parsed_json);
	if (!ft_strnstr(profile.staff, "false", 5))
	{
		json_object_put(parsed_json);
		sprintf(t_strings.buffer, "{\"Login\":\"%s\",\"ID\":%d,\"Name\":\"%s\",\"Campus\":\"%s\",\"Staff?\":\"True\"}", profile.login, profile.id, profile.name, profile.campus);
		return ;
	}
	get_start(parsed_json);
	get_project(parsed_json);
	get_n_badges(parsed_json);
	get_wallet(parsed_json);
	get_ev_pts(parsed_json);
	json_object_put(parsed_json);
	write_profile();
}

void	get_login(json_object *parsed_json)
{
	struct json_object	*login;

	json_object_object_get_ex(parsed_json, "login", &login);
	memcpy(profile.login, (void *)json_object_get_string(login), 9);
	json_object_put(login);
}

void	get_id(json_object *parsed_json)
{
	struct json_object	*id;

	json_object_object_get_ex(parsed_json, "id", &id);
	profile.id = json_object_get_int(id);
	json_object_put(id);
}

void	get_name(json_object *parsed_json)
{
	struct json_object	*name;

	json_object_object_get_ex(parsed_json, "usual_full_name", &name);
	memcpy(profile.name, (void *)json_object_get_string(name), 49);
	json_object_put(name);
}

void	get_campus(json_object *parsed_json)
{
	struct json_object	*campus;
	struct json_object	*campus_name;
	struct json_object	*index;

	json_object_object_get_ex(parsed_json, "campus", &campus);
	index = json_object_array_get_idx(campus, 0);
	json_object_object_get_ex(index, "name", &campus_name);
	memcpy(profile.campus, (void *)json_object_get_string(campus_name), 24);
	json_object_put(campus_name);
	json_object_put(index);
	json_object_put(campus);
}

void	get_staff(json_object *parsed_json)
{
	struct json_object	*staff;

	json_object_object_get_ex(parsed_json, "staff?", &staff);
	memcpy(profile.staff, (void *)json_object_get_string(staff), 5);
	json_object_put(staff);
}

void	get_start(json_object *parsed_json)
{
	struct json_object	*cursus;
	struct json_object	*start;
	struct json_object	*index;
	struct json_object	*lvl;
	char				level[12];

	json_object_object_get_ex(parsed_json, "cursus_users", &cursus);
	index = json_object_array_get_idx(cursus, 0);
	json_object_object_get_ex(index, "begin_at", &start);
	json_object_object_get_ex(index, "level", &lvl);

	memcpy(profile.start, (void *)json_object_get_string(start), 10);
	sprintf(level, "%.2f%c", json_object_get_double(lvl), '%');
	memcpy(profile.lvl, level, 5);
	
	json_object_put(cursus);
	json_object_put(start);
	json_object_put(index);
	json_object_put(lvl);
}

void	get_project(json_object *parsed_json)
{
	struct json_object	*pj_user;
	struct json_object	*pj_data;
	struct json_object	*proj;
	struct json_object	*index;
	size_t				n_projects;
	int					i;
	

	i = 0;
	json_object_object_get_ex(parsed_json, "projects_users", &pj_user);
	n_projects = json_object_array_length(pj_user);
	while (i < (int)n_projects)
	{
		index = json_object_array_get_idx(pj_user, i);
		json_object_object_get_ex(index, "project", &pj_data);
		json_object_object_get_ex(pj_data, "name", &proj);
		if (i == 0)
			memcpy(profile.lst_proj, (void *)json_object_get_string(proj), 19);
		else if (ft_strnstr(json_object_get_string(proj), "Basecamp", 10))
		{
			profile.n_proj = (i - 1);
			break ;
		}
		i++;
	}
	json_object_put(pj_user);
	json_object_put(pj_data);
	json_object_put(proj);
	json_object_put(index);
}

void	get_n_badges(json_object *parsed_json)
{
	struct json_object *medals;
	size_t				n_medals;
	
	json_object_object_get_ex(parsed_json, "achievements", &medals);
	n_medals = json_object_array_length(medals);
	profile.n_badge = (int)n_medals;
	json_object_put(medals);
}

void	get_wallet(json_object *parsed_json)
{
	struct json_object	*wallet;

	json_object_object_get_ex(parsed_json, "wallet", &wallet);
	profile.wallet =json_object_get_int(wallet);
	json_object_put(wallet);
}

void	get_ev_pts(json_object *parsed_json)
{
	struct json_object	*ev_pts;

	json_object_object_get_ex(parsed_json, "correction_point", &ev_pts);
	profile.ev_pts = json_object_get_int(ev_pts);
	json_object_put(ev_pts);
}
