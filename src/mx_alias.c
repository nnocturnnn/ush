#include "ush.h"

int mx_alias(char **arg, char **data, char **env) {
    int i = -1;
    int j = 0;

    while (data[j])
        j++;
    if (!arg[0]) {
        mx_print_env(data);
    } else {
        while(arg[++i]) {
            data[j] = strdup(arg[i]);
            j++;
        }
    }
    return 1;
}

int mx_unalias(char **arg, char **data, char **env) {
    int i = -1;
    int q = 0;

    if (!arg[0])
        mx_printerr("unalias: not enough arguments\n");
    while (arg[++i]) {
        if (mx_get_substr_index(arg[i],arg[q]) == 0)
            // mx_del
            return 1;
    }
    return 1;
}
