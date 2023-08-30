#include "../../include/minishell.h"

/*
solo funcionara con el primer argumento si recibe mas de un argumento
error bash: cd: too many arguments
 POSIBLES ARGUMENTOS:
	. -> cd . no hace nada pq indica que se quede en el directorio actual lo mismo sin argumentos
	.. -> retrocede un directotio atras, direcciones relativas.
	- -> cd - , printea por pantalla el directorio de trabajo anterior y se ubica en el.
	~ -> se ubica en el directorio HOME del usuario actual
	~/USER -> se ubica en el directorio Home del usuario indicado
*/

static void	update_path(t_global *g, char *pwd, char *oldpwd)
{
	char	*path_pwd_export;
	char	*path_old_pwd_export;

	path_pwd_export = ft_strdup(pwd);
	path_old_pwd_export = ft_strdup(oldpwd);
	search_key_and_replace(g->lst_env, ft_strdup("PWD"), path_pwd_export);
	search_key_and_replace(g->lst_env, ft_strdup("OLDPWD"), \
	path_old_pwd_export);
	search_env_replace(ft_strdup("PWD"), pwd, g->env);
	search_env_replace(ft_strdup("OLDPWD"), oldpwd, g->env);
}


int	ft_cd(t_global *g, int n)
{
	char	buffer[PATH_MAX];
	char	*path_pwd;
	char	*path_old_pwd;

	path_old_pwd = ft_strdup(getcwd(buffer, PATH_MAX));
	if (g->tokens[n].arg[1])
	{
		perror("error bash: cd: too many arguments \n");
		return (1);
	}	
	if (!g->tokens[n].arg[0] || \
			ft_strncmp(g->tokens[n].arg[0], "~", 2) == 0)
		chdir(search_env_expand("HOME", g->env));
	else if (ft_strncmp(g->tokens[n].arg[0], "-", 2) == 0)
	{
		ft_putstr_fd(search_env_expand("OLDPWD", g->env), STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		chdir(search_env_expand("OLDPWD", g->env));
	}
	else if (chdir(g->tokens[n].arg[0]) < 0)
		return (perror(0), 1);
	path_pwd = ft_strdup(getcwd(buffer, PATH_MAX));
	update_path(g, path_pwd, path_old_pwd);
	return (0);
}
