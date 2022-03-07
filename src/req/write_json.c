/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_json.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 21:06:06 by guferrei          #+#    #+#             */
/*   Updated: 2022/03/07 08:12:24 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/api.h"

void	write_profile(void)
{
	sprintf(t_strings.profile, "{\"Login\":\"%s\",\"ID\":%d,\"Name\":\"%s\",\"Campus\":\"%s\",\"Start_at\":\"%s\",\"Level\":\"%s\",\"Current_proj\":\"%s\",\"Proj_done\":%d,\"Badges\":%d,\"Ev_points\":%d,\"Wallet\":%d,\"Staff?\":\"False\"", profile.login, profile.id, profile.name, profile.campus, profile.start, profile.lvl, profile.lst_proj, profile.n_proj, profile.n_badge, profile.ev_pts, profile.wallet);
}

void	write_projects(void)
{
	sprintf(t_strings.profile, "{\"Project\":\"%s\",\"Registered_at\":\"%s\",\"Validated_at\":\"%s\",\"Status\":\"%s\",\"Retries\":%d,\"Grade\":\"%s\"}", t_project.name, t_project.start, t_project.end, t_project.status, t_project.retries, t_project.grade);
	t_strings.buffer = ft_strjoin(t_strings.buffer, t_strings.profile);
}

