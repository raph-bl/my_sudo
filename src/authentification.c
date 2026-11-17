/*
** EPITECH PROJECT, 2025
** authentification.c
** File description:
** DESCRIPTION
*/

#include "my_sudo.h"

static void open_shadow_file(FILE **shadow_file)
{
    *shadow_file = fopen("/etc/shadow", "r");
    if (!*shadow_file)
        exit_error("Error: Cannot open shadow file");
}

static char *extract_hash(char *field, char *hash)
{
    char *end = strchr(field, ':');

    if (end) {
        strncpy(hash, field, end - field);
        hash[end - field] = '\0';
        return hash;
    }
    return NULL;
}

static char *process_line(char *buffer, const char *username, char *hash)
{
    char *field;

    if (strncmp(buffer, username, strlen(username)) == 0 &&
        buffer[strlen(username)] == ':') {
        field = strchr(buffer, ':');
        if (field) {
            field++;
            return extract_hash(field, hash);
        }
    }
    return NULL;
}

static char *get_shadow_entry(const char *username)
{
    FILE *shadow_file;
    char buffer[MAX_LINE_LEN];
    static char hash[MAX_LINE_LEN];
    char *result;

    open_shadow_file(&shadow_file);
    while (fgets(buffer, sizeof(buffer), shadow_file)) {
        result = process_line(buffer, username, hash);
        if (result != NULL) {
            fclose(shadow_file);
            return result;
        }
    }
    fclose(shadow_file);
    return NULL;
}

void authenticate_user(data_t *data)
{
    char *req_pass = check_malloc(sizeof(char) * (26 + strlen(data->user)));
    char *hash = NULL;
    int attempts = 0;

    if (!getuid())
        return;
    hash = get_shadow_entry(data->user);
    if (hash == NULL)
        exit_error("Error: Unable to get password entry.");
    while (attempts < MAX_ATTEMPTS) {
        sprintf(req_pass, "[my_sudo] password for %s: ", data->user);
        if (!strcmp(crypt(getpass(req_pass), hash), hash))
            return;
        attempts++;
        if (attempts < MAX_ATTEMPTS)
            printf("Sorry, try again.\n");
    }
    exit_error("my_sudo: 3 incorrect password attempts");
}
