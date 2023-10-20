/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:00:34 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/21 12:53:04 by Jroldan-         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		update_path(t_global *g, char *pwd, char *oldpwd);
static int		special_cases(t_global *g, int n, int flag);
static void		cd_work_with_addresses(t_global *g, int n);
static void		previous_working_directory(t_global *g, char *expand);

static void	update_path(t_global *g, char *pwd, char *oldpwd)
{
	char	*path_pwd_export;
	char	*path_old_pwd_export;

	if (ft_strncmp(pwd, oldpwd, ft_strlen(pwd) + 1) != 0)
	{	
		path_pwd_export = ft_strdup(pwd);
		path_old_pwd_export = ft_strdup(oldpwd);
		search_key_and_replace(g->lst_env, ft_strdup("PWD"), \
		path_pwd_export, 1);
		if (search_env("OLDPWD", g->env) == 1)
			add_env(&g->env, "OLDPWD=");
		search_key_and_replace(g->lst_env, ft_strdup("OLDPWD"), \
		path_old_pwd_export, 1);
		search_env_replace(ft_strdup("PWD"), pwd, g->env, 0);
		search_env_replace(ft_strdup("OLDPWD"), oldpwd, g->env, 0);
	}
}

static void	previous_working_directory(t_global *g, char *expand)
{
	if (search_env("OLDPWD", g->env) == 1)
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
	else
	{
		expand = search_env_expand("OLDPWD", g->env);
		ft_putstr_fd(expand, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		g->exit_status = chdir(expand);
		free_mem((void **)&expand);
	}
}

static int	special_cases(t_global *g, int n, int flag)
{
	char	*expand;

	expand = NULL;
	if (!g->tokens[n].arg[0] || \
			ft_strncmp(g->tokens[n].arg[0], "~", 2) == 0)
	{
		if (search_env("HOME", g->env) == 1 && g->tokens[n].arg[0] == NULL)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return (flag = 1);
		}
		if (search_env("HOME", g->env) == 1 && g->tokens[n].arg[0][0] == '~')
			expand = ft_strdup(getenv("HOME"));
		else
			expand = (search_env_expand("HOME", g->env));
		g->exit_status = chdir(expand);
		flag = 1;
		free_mem((void **)&expand);
	}
	else if (ft_strncmp(g->tokens[n].arg[0], "-", 2) == 0)
	{
		previous_working_directory(g, expand);
		flag = 1;
	}
	return (flag);
}

static void	cd_work_with_addresses(t_global *g, int n)
{
	char	*env_home;

	if (g->tokens[n].arg[0][0] == '~' && g->tokens[n].arg[0][1] != '\0')
	{
		g->tokens[n].arg[0] = ft_substr(g->tokens[n].arg[0], 1, \
		ft_strlen(g->tokens[n].arg[0]), 1);
		if (search_env("HOME", g->env) == 1)
			env_home = ft_strdup(getenv("HOME"));
		else
			env_home = (search_env_expand("HOME", g->env));
		g->tokens[n].arg[0] = ft_strjoin(env_home, \
		g->tokens[n].arg[0], 3);
	}
	if (chdir(g->tokens[n].arg[0]) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(g->tokens[n].arg[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g->exit_status = chdir(g->tokens[n].arg[0]) * -1;
	}
}

void	ft_cd(t_global *g, int n)
{
	char	buffer[PATH_MAX];
	char	*path_pwd;
	char	*path_old_pwd;
	int		flag;

	flag = 0;
	path_old_pwd = check_pwd_oldpwd(g);
	flag = special_cases(g, n, flag);
	if (flag == 0)
		cd_work_with_addresses(g, n);
	path_pwd = getcwd(buffer, PATH_MAX);
	update_path(g, path_pwd, path_old_pwd);
	free_mem((void **)&path_old_pwd);
}
