##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME = my_sudo

CPPFLAGS = -I./include -lcrypt
CFLAGS = -W -Wall -Wextra
TFLAGS = -lcriterion --coverage

MAKEFLAGS += -B -s -j$(nproc)

SRC = $(shell find src -name '*.c')
SRC_O = $(SRC:.c=.o)

TESTS = $(shell find tests -name '*.c')
TESTS_O = $(TESTS:.c=.o)

all: $(NAME)

$(NAME): $(SRC_O)
	$(CC) $^ $(CPPFLAGS) -o $@

tests_run: CPPFLAGS += $(TFLAGS)
tests_run: $(filter-out src/main.o, $(SRC_O)) $(TESTS_O)
	-$(CC) $^ $(CPPFLAGS) $(TFLAGS) -o $(NAME) && ./$(NAME)

clean:
	find . -name "*.o" -delete
	find . -name "*.gc*" -delete
	find . -name "*.log" -delete
	find . -name "*.a" -delete

fclean: clean
	$(RM) $(NAME)

re: fclean all





# DEVARGS = -u maty whoami
DEVARGS = whoami
# DEVARGS = -s
# DEVARGS = -h
# DEVARGS = ls -la

dev: $(SRC_O)
	-$(CC) $^ $(CPPFLAGS) -o $(NAME)
	-sudo chown root:root $(NAME)
	-sudo chmod u+s $(NAME)
	-./$(NAME) $(DEVARGS); echo $$?
	$(MAKE) fclean

cov: tests_run
	clear
	-gcovr --exclude tests && gcovr --exclude tests --txt-metric branch
	-./$(NAME)
	$(MAKE) fclean
