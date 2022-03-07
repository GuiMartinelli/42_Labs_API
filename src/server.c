#include <stdio.h>
#include <ulfius.h>
#include "../includes/main.h"

#define PORT 8080

int callback_json (const struct _u_request * request, struct _u_response * response, void * user_data)
{
	user_data = calloc(5000, sizeof(char));
	user_data = ft_request(request->http_url);
	if (ft_strnstr(user_data, "{}", 2))
		ulfius_set_string_body_response(response, 404, user_data);
	else if (ft_strnstr(user_data, "Error", 5))
		ulfius_set_string_body_response(response, 403, user_data);
	else if (ft_strnstr(user_data, "Connection", 30))
		ulfius_set_string_body_response(response, 500, user_data);
	else
		ulfius_set_string_body_response(response, 200, user_data);
	return U_CALLBACK_CONTINUE;
}

int main(void)
{
	struct _u_instance	instance;

	if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK)
	{
		fprintf(stderr, "Error ulfius_init_instance, abort\n");
		return(1);
	}

	ulfius_add_endpoint_by_val(&instance, "GET", "/:user", NULL, 0, &callback_json, NULL);
	
	if (ulfius_start_framework(&instance) == U_OK)
	{
		printf("Start framework on port %d\n", instance.port);
		getchar();
	}
	else
		fprintf(stderr, "Error starting framework\n");
	printf("End framework\n");

	ulfius_stop_framework(&instance);
	ulfius_clean_instance(&instance);
	return 0;
}
