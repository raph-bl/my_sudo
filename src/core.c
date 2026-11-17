/*
** EPITECH PROJECT, 2025
** core.c
** File description:
** DESCRIPTION
*/

#include "my_sudo.h"

static char *get_base_user(void)
{
    char *user = getenv("USER");

    if (user == NULL)
        exit_error("Error: Unable to get username.");
    return user;
}

data_t *init_data_struct(void)
{
    data_t *data = check_malloc(sizeof(data_t));

    data->user = get_base_user();
    data->command = NULL;
    data->args = NULL;
    data->open_shell = false;
    data->custom_user = false;
    data->custom_group = false;
    data->keep_env = false;
    data->exec_user = NULL;
    data->exec_group = NULL;
    return data;
}

static void handle_option_flags(data_t *data, char *arg)
{
    for (int j = 1; arg[j] != '\0'; j++) {
        if (arg[j] == 'u') {
            data->custom_user = true;
            continue;
        }
        if (arg[j] == 'g') {
            data->custom_group = true;
            continue;
        }
        if (arg[j] == 's') {
            data->open_shell = true;
            continue;
        }
        if (arg[j] == 'E') {
            data->keep_env = true;
            continue;
        }
        exit_error("Error: Invalid option.");
    }
}

static void check_help_option(int ac, char **av)
{
    if (ac < 2) {
        print_usage();
        exit(FAILURE);
    }
    if (ac == 2 && !strcmp(av[1], "-h")) {
        print_usage();
        exit(SUCCESS);
    }
}

static void handle_user_and_command(data_t *data, char *arg)
{
    if (data->custom_user && data->exec_user == NULL) {
        data->exec_user = arg;
        return;
    }
    if (data->custom_group && data->exec_group == NULL) {
        data->exec_group = arg;
        return;
    }
    if (data->command == NULL) {
        data->command = arg;
    }
}

static void check_args(data_t *data, int ac, char **av)
{
    int args_index = 0;

    check_help_option(ac, av);
    data->args = check_malloc(sizeof(char *) * ac);
    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-' && data->command == NULL) {
            handle_option_flags(data, av[i]);
            continue;
        }
        handle_user_and_command(data, av[i]);
        if (data->command != NULL && av[i] != data->command &&
            (!data->custom_user || av[i] != data->exec_user) &&
            (!data->custom_group || av[i] != data->exec_group)) {
            data->args[args_index] = av[i];
            args_index++;
        }
    }
}

int core(int ac, char **av)
{
    data_t *data = init_data_struct();

    check_args(data, ac, av);
    authenticate_user(data);
    execution(data);
    return SUCCESS;
}
