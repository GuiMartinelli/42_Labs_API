NAME = labs_api

FLAGS = -Wall -Wextra -Werror -lcurl -lmysqlclient -ljson-c -lulfius

FILES = src/db/database.c src/db/proj_db.c src/parse/data_filter.c src/parse/project_data.c src/req/request.c \
		src/req/write_json.c src/token/read_token.c src/utils/ft_strjoin.c src/utils/ft_strnstr.c src/utils/test_input.c

MAIN = src/server.c

all:
	gcc $(FILES) $(MAIN) $(FLAGS) -o $(NAME)

token:
	sh src/token/token.sh

clean:
	rm $(NAME)

re: clean all