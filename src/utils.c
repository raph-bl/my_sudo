/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** DESCRIPTION
*/

#include "my_sudo.h"

void exit_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(FAILURE);
}

void print_usage(void)
{
    printf("usage: ./my_sudo -h\n"
        "usage: ./my_sudo [-ugEs] [command [args ...]]\n");
}

void *check_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        exit_error("Error: malloc failed.");
    return ptr;
}
