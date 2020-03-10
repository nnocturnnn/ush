#ifndef USH_H 
#define USH_H

#include <stdio.h>
#include <signal.h>
#include <wchar.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <time.h>
#include <termios.h>
#include "../libmx/inc/libmx.h"

enum e_eror{
    UNSET_ERR,
    USH_NF,
    USH_PERMISION,
    FORK_FAIL,
    USH_BAD_ASSIGN,
    CD_NSFORD,
    CD_PERMISION,
    CD_NON_DIR,
    CD_TO_MANY,
    CD_STR_NOT_PWD,
    ENV_ILL,
    ENV_OPTION_REQ,
    WHC_NF,
    ERR_NAR,
};

typedef struct s_ush {
    char **commands;
    char **alias;
    char **var;
} t_ush;

#define MX_OK 00

char *mx_replace_dolars(char *nah_tild, char ***env);
char **replace_on_koskav(char **shit);
char **mx_interpretate(char *command);
int mx_unalias(char **arg, char **data);
int check_builtins(char **command, t_ush data, char ***env);
int mx_exit_builtin(char **arg);
void mx_set_var(char *key, char *value, char **var);
int bye_builtin(char **command);
int false_builtin(char **var);
int true_builtin(char **var);
int return_builtin(char **var, char **arg);
void key_handler(t_ush data);
int envv_len(char **envv);
void mx_errors(enum e_eror errors, char *a);
void print_path(char *path, char **env);
char **mx_init_envr(int argc, char **argv, char **envr);
void mx_display(char **env);
char *mx_parse_home_path(char *path, int reverse, char **env);
int mx_isemptystr(char *str, int consider_space);
void mx_exit_shell(char **env);
char *mx_get_env_var(char *var, char **env);
char *mx_pathjoin(char *p1, char *p2);
char **mx_get_input(char **input, t_ush data, char ***env);
void signal_handler(int signo);
void proc_signal_handler(int signo); 
int mx_run_command(char **commands, t_ush data, char ***env, int run_mode);
void mx_print_env(char **env);
int mx_export_builtin(char **arg, t_ush data, char **env);
int mx_echo_builtin(char **arg, t_ush data);
int mx_cd_builtin(char **arg, char **env);
int mx_change_dir(char *path, int printh_path, char **env);
int mx_find_env_var(char *var,char **env);
void mx_set_env_var(char *key, char *value, char ***env);
char **realloc_envv(int new_size, char **env);
int mx_pwd_builtin(char **arg, char **env);
int mx_which_builtin(char **arg, char **env);
int mx_env_builtin(char **arg, t_ush data, char **env);
char **mx_init_export(char **env);
int mx_alias(char **arg, char **data);
int mx_unsetenv_builtin(char **arg, char **data);
int	mx_isinenv(char **env, char *var);
int mx_exit_builtin(char **arg);
int mx_echo_builtin(char **str, t_ush data);

#endif 
