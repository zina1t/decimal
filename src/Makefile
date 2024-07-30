CFLAGS = -Wall -Wextra -Werror -std=c11

all: clean main

main: 
	gcc $(CFLAGS) main.c s21_add.c s21_sub.c s21_mul.c aux_funcs.c int_to_decimal.c float_to_decimal.c -lm -o main

clean:
	rm -f *.o main

rebuild: clean all