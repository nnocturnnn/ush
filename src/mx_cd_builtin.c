#include "ush.h"

static void	print_path(char *path, char **env) {
	char *parsed_home = mx_parse_home_path(path, 0, env);

	mx_printstr(parsed_home);
	free(parsed_home);
}

static int has_two_args(char **args, char **env) {
	char *cwd;
	char buff[4096 + 1];
	char *tmp;

	if (args[1]) {
		if (args[2]) {
		    mx_errors(CD_TO_MANY, "");
			return (1);
		}
		cwd = getcwd(buff, 4096);
		if (!(tmp = mx_replace_substr(cwd, args[0], args[1]))) {
            mx_errors(CD_STR_NOT_PWD, args[0]);
			// free(tmp);
			return (1);
		}
		mx_change_dir(tmp, 1, env);
		// free(tmp);
		return (1);
	}
	return (0);
}

void mx_change_dir(char *path, int printh_path, char **env) {
    char *cwd;
	char buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path)) {
		if (printh_path) {
			print_path(path, env);
		    mx_printchar('\n');
		}
		mx_set_env_var("OLDPWD", cwd, env);
	} else {
        if (access(path, F_OK) == -1)
			mx_errors(CD_NSFORD, path);
		else if (access(path, R_OK) == -1)
			mx_errors(CD_PERMISION, path);
		else
			mx_errors(CD_NON_DIR, path);
    }
}


// static int cd_with_flag(char **arg, char **env, char *home_path) {
   
// }

int mx_cd_builtin(char **arg, char **env) {
    char *home_path  = mx_get_env_var("HOME", env);
    struct stat buffy;

    if(!arg[0]) {
        mx_change_dir(home_path, 0, env);
        return 1;
    }
    if (has_two_args(arg, env))
        return 1;
    else {
         if (mx_strequ(arg[0], "-")) {
			mx_change_dir(mx_get_env_var("OLDPWD", env), 1, env);
			return 1;
		 } else if (mx_strequ(arg[0], "--")) {
			mx_change_dir(home_path, 0, env);
			return 1;
        } else if (mx_strequ(arg[0], "-P")) {
            return 1;
        } else if (mx_strequ(arg[0], "-s")) {
            mx_printstr(mx_pathjoin(mx_get_env_var("PWD", env), arg[1]));
            lstat(mx_pathjoin(mx_get_env_var("PWD", env), arg[1]),&buffy);
            if ((buffy.st_mode & S_IFMT) == S_IFLNK)
                mx_errors(CD_NON_DIR, arg[0]);
            else
                mx_change_dir(arg[1], 0, env);
            return 1;
        }
		mx_change_dir(arg[0], 0, env);
    }
    return 1;
}
