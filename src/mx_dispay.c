#include "ush.h"

void mx_display(char **env) {
    char *cwd;
    char buff[4096 + 1];
    char *parsed_cwd;

    cwd = getcwd(buff, 4096);
    parsed_cwd = mx_parse_home_path(cwd, 0, env);
    if (!parsed_cwd)
        mx_printstr("\033[0;32mu$h> \033[0m ");
    else {
        mx_printstr("\033[0;32m");
        mx_printstr(parsed_cwd);
        mx_strdel(&parsed_cwd);
        mx_printstr(" u$h> \033[0m ");
    }
}
