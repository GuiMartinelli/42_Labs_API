/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 08:29:13 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 14:45:35 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

void	project_data(void)
{
	FILE				*jfile;
	char				buffer[100000];
	struct json_object	*parsed_json;
	
	proj_db();
	jfile = fopen("./src/response.json", "r");
	fread(buffer, 100000, 1, jfile);
	fclose(jfile);
	parsed_json = json_tokener_parse(buffer);
	get_pj_data(parsed_json);
	json_object_put(parsed_json);
}

void	get_pj_data(json_object *parsed_json)
{
	struct json_object	*pj_user;
	struct json_object	*pj_data;
	struct json_object	*index;
	struct json_object	*name;
	struct json_object	*retries;
	struct json_object	*grade;
	struct json_object	*status;
	struct json_object	*start;
	struct json_object	*end;
	size_t				n_projects;
	int					i;
	

	i = 0;
	json_object_object_get_ex(parsed_json, "projects_users", &pj_user);
	n_projects = json_object_array_length(pj_user);
	t_strings.buffer = ft_strjoin(t_strings.profile, ",\"Project_data\"[");
	while (i < (int)n_projects)
	{
		index = json_object_array_get_idx(pj_user, i);

		//GET DATA
		json_object_object_get_ex(index, "occurrence", &retries);
		json_object_object_get_ex(index, "final_mark", &grade);
		json_object_object_get_ex(index, "status", &status);
		json_object_object_get_ex(index, "created_at", &start);
		json_object_object_get_ex(index, "marked_at", &end);
		json_object_object_get_ex(index, "project", &pj_data);
		json_object_object_get_ex(pj_data, "name", &name);

		//WRITE DATA ON STRUCT T_PROJECT
		sprintf(t_project.grade, "%3i%c", (int)json_object_get_int(grade), '%');
		t_project.retries = (int)json_object_get_int(retries);
		memcpy(t_project.name, json_object_get_string(name), 24);
		memcpy(t_project.status, json_object_get_string(status), 10);
		memcpy(t_project.start, json_object_get_string(start), 10);
		if (json_object_get_string(end))
			memcpy(t_project.end, json_object_get_string(end), 10);
		else
			memcpy(t_project.end, "-", 10);
		populate_pdb();
		write_projects();
		i++;
		if (i < (int)n_projects)
			t_strings.buffer = ft_strjoin(t_strings.buffer, ",");
		else
			t_strings.buffer = ft_strjoin(t_strings.buffer, "]}");
	}
	json_object_put(pj_user);
	json_object_put(pj_data);
	json_object_put(name);
	json_object_put(index);
	json_object_put(retries);
	json_object_put(start);
	json_object_put(end);
	json_object_put(status);
	json_object_put(grade);
}
