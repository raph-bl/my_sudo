/*
** EPITECH PROJECT, 2025
** cmd_exec.c
** File description:
** DESCRIPTION
*/

#include "my_sudo.h"

static int parse_passwd_line(const char *line, const char *username)
{
    char *token;
    char line_copy[MAX_LINE_LEN];

    strcpy(line_copy, line);
    token = strtok(line_copy, ":");
    if (token && !strcmp(token, username)) {
        strtok(NULL, ":");
        token = strtok(NULL, ":");
        if (token)
            return atoi(token);
    }
    return -1;
}

static int get_user_uid(const char *username)
{
    FILE *passwd;
    char line[MAX_LINE_LEN];
    int uid;

    if (username == NULL)
        return 0;
    passwd = fopen("/etc/passwd", "r");
    if (!passwd)
        exit_error("Error: Cannot open /etc/passwd");
    while (fgets(line, sizeof(line), passwd)) {
        uid = parse_passwd_line(line, username);
        if (uid != -1) {
            fclose(passwd);
            return uid;
        }
    }
    fclose(passwd);
    exit_error("Error: User not found.");
    return -1;
}

int execution(data_t *data)
{
    char *shell = getenv("SHELL");

    if (setuid(get_user_uid(data->exec_user)) == -1)
        exit_error("Error: Unable to setuid.");
    if (data->open_shell) {
        if (!shell)
            shell = "/bin/sh";
        execvp(shell, data->args);
        return SUCCESS;
    }
    execvp(data->command, data->args);
    return SUCCESS;
}
