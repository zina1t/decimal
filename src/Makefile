CFLAGS = -Wall -Wextra -Werror -std=c11

all: main

main: 
	gcc $(CFLAGS) main.c s21_add.c s21_sub.c aux_funcs.c -lm -o main

clean:
	rm -f *.o main

rebuild: clean all