/*
** EPITECH PROJECT, 2024
** test_my_sudo.c
** File description:
** DESCRIPTION
*/

#include "my_sudo.h"

#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(core, main_test_01, .init = redirect_all_stdout)
{
    char *av[] = {"./my_sudo", "-h", NULL};
    int ac = 2;

    core(ac, av);
}

Test(core, main_test_02, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-u", "root", "ls", "-l", NULL};
    int ac = 5;

    core(ac, av);
}

Test(core, main_test_03, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-u", "root", "-g", "root", "ls", "-l", NULL};
    int ac = 7;

    core(ac, av);
}

Test(core, main_test_04, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-s", "ls", "-l", NULL};
    int ac = 4;

    core(ac, av);
}

Test(core, main_test_05, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", NULL};
    int ac = 1;

    core(ac, av);
}

Test(core, main_test_06, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-u", "root", "-s", "ls", "-l", NULL};
    int ac = 6;

    core(ac, av);
}

Test(core, main_test_07, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-u", "aaaaaa", NULL};
    int ac = 3;

    core(ac, av);
}

Test(core, main_test_08, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-E", "whoami", NULL};
    int ac = 3;

    core(ac, av);
}

Test(core, main_test_09, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-g", "root", "ls", "-l", NULL};
    int ac = 5;

    core(ac, av);
}

Test(core, main_test_10, .init = redirect_all_stdout, .exit_code = 84)
{
    char *av[] = {"./my_sudo", "-z", "root", "-g", "root", "-E", "ls", NULL};
    int ac = 7;

    core(ac, av);
}
