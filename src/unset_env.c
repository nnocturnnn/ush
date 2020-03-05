#include "ush.h"

char **mx_remove_env_var(char *name_var, char **env) {
    int var_pos = mx_find_env_var(name_var, env);
    int i = var_pos;
    int var_count;

    mx_strdel(&env[var_pos]);
	var_count = var_pos + 1;
	while (env[i + 1]) {
		env[i] = strdup(env[i + 1]);
		mx_strdel(&env[i + 1]);
		i++;
		var_count++;
	}
	env = realloc_envv(var_count - 1, env);
    return env;
}

int mx_unsetenv_builtin(char **arg, char ***env) {
    int	i;
	int	var_pos;

	if (!arg[0]) {
		mx_errors(UNSET_ERR, "uns");
		return 1;
	}
	i = -1;
	while (arg[++i]) {
		var_pos = mx_find_env_var(arg[i], *(env));
		if (*(*env + var_pos))
			*(env) = mx_remove_env_var(arg[i], *(env));
	}
	return 1;
}