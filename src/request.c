/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:14:41 by guferrei          #+#    #+#             */
/*   Updated: 2021/08/22 14:32:30 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "api.h"

char	*ft_request(const char *login)
{
	CURL	*curl;
	CURLcode	response;
	struct curl_slist *header = NULL;
	const char			*token;
	char				url[50];

	token = (const char *)read_token();
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	sprintf(url, "https://api.intra.42.fr/v2/users%s", login);
	freopen("./src/response.json", "w", stdout);
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		header = curl_slist_append(header, token);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		response = curl_easy_perform(curl);
		if (response != CURLE_OK)
			return ("Error!! Connection with 42API Failed!!\n");
		freopen("/dev/tty", "w", stdout);
		curl_easy_cleanup(curl);
	}
	if (test_input() == 1)
		return ("{}");
	else if (test_input() == 2)
		return ("Error!! Not Authorized");
	printf("Data found\n");
	data_filter();
	if (ft_strnstr(profile.staff, "false", 5))
		project_data();
	store_data();
	curl_global_cleanup();
	curl_slist_free_all(header);
	return (t_strings.buffer);
}
