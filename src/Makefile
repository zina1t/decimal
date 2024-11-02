# Компилятор
CC = gcc

# Опции компилятора
CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags --libs check)

# Опции линковки
LDFLAGS = -lcheck -lsubunit -lm

# Заголовки
HEADERS = s21_decimal.h 

# Исходные файлы
SOURCES_ALL := $(wildcard *.c) $(wildcard tests/*.c)

# Объектные файлы для библиотеки
OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES_ALL))

# Правило для создания объектных файлов
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Основное правило
all: s21_decimal.a test gcov_report

# Создание статической библиотеки
s21_decimal.a: $(OBJ_LIBRARY)
	ar rcs $@ $^
	ranlib $@

# Правило для тестирования
test: s21_decimal.a tests/main_for_tests.c
	$(CC) $(CFLAGS) tests/main_for_tests.c -o test.out s21_decimal.a $(LDFLAGS)
	./test.out

# Генерация отчета о покрытии
gcov_report: s21_decimal.a tests/main_for_tests.c
	$(CC) $(CFLAGS) tests/main_for_tests.c $(SOURCES_ALL) -o report.out $(LDFLAGS)
	./report.out
	gcov -f $(SOURCES_ALL)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

# Личное тестирование с отдельным файлом
personal: s21_decimal.a tests/personal.c
	$(CC) $(CFLAGS) tests/personal.c -o test.out s21_decimal.a $(LDFLAGS)
	./test.out

# Проверка стиля кода с clang-format
check:
	clang-format -style=Google -n ./*/*.c

# Полная пересборка проекта
rebuild: clean all

# Очистка временных файлов и отчетов о покрытии
clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report

.PHONY: all clean test gcov_report personal check rebuild