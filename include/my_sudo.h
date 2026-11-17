/*
** EPITECH PROJECT, 2024
** my_sudo.h
** File description:
** DESCRIPTION
*/

#ifndef MY_SUDO_H
    #define MY_SUDO_H

    #include <stdio.h>
    #include <string.h>
    #include <crypt.h>
    #include <shadow.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <grp.h>

    #define FAILURE 84
    #define SUCCESS 0
    #define MAX_ATTEMPTS 3
    #define MAX_LINE_LEN 1024

typedef struct data_s {
    char *user;
    char *exec_user;
    char *exec_group;
    bool open_shell;
    bool custom_user;
    bool custom_group;
    bool keep_env;
    char *command;
    char **args;
} data_t;

int core(int ac, char **av);
int execution(data_t *my_sudo);
void authenticate_user(data_t *sudo);

void print_usage(void);
void exit_error(char *msg);
void *check_malloc(size_t size);

#endif /* !MY_SUDO_H */
