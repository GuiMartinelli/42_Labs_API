FLAGS = -Wall -Wextra -Werror -lcurl -lmysqlclient -ljson-c -lulfius

FILES = src/*.c

all:
	gcc $(FILES) $(FLAGS)

token:
	sh src/token.sh

clean:
	rm a.out