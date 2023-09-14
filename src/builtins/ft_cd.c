/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:00:34 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:00:34 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	special_cases(t_global *g, int n, int wall)
{
	char	*expand;

	if (!g->tokens[n].arg[0] || \
			ft_strncmp(g->tokens[n].arg[0], "~", 2) == 0)
	{
		expand = search_env_expand("HOME", g->env);
		g->exit_status = chdir(expand);
		wall = 1;
		free_mem((void **)&expand);
	}
	else if (ft_strncmp(g->tokens[n].arg[0], "-", 2) == 0)
	{
		wall = 1;
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
	return (wall);
}

static void	cd_work_with_addresses(t_global *g, int n)
{
	if (g->tokens[n].arg[0][0] == '~' && g->tokens[n].arg[0][1] != '\0')
	{
		g->tokens[n].arg[0] = ft_substr(g->tokens[n].arg[0], 1, \
		ft_strlen(g->tokens[n].arg[0]), 1);
		g->tokens[n].arg[0] = ft_strjoin(search_env_expand("HOME", g->env), \
		g->tokens[n].arg[0], 3);
		if (chdir(g->tokens[n].arg[0]) < 0)
		{
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
			g->exit_status = chdir(g->tokens[n].arg[0]) * -1;
		}
	}
	else if (chdir(g->tokens[n].arg[0]) < 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		g->exit_status = chdir(g->tokens[n].arg[0]) * -1;
	}
}

void	ft_cd(t_global *g, int n)
{
	char	buffer[PATH_MAX];
	char	*path_pwd;
	char	*path_old_pwd;
	int		wall;

	wall = 0;
	path_old_pwd = search_env_expand("PWD", g->env);
	if (g->tokens[n].arg[0] != NULL && g->tokens[n].arg[1] != NULL)
	{
		wall = 1;
		g->exit_status = 0;
	}	
	wall = special_cases(g, n, wall);
	if (wall == 0)
		cd_work_with_addresses(g, n);
	path_pwd = getcwd(buffer, PATH_MAX);
	update_path(g, path_pwd, path_old_pwd);
	free_mem((void **)&path_old_pwd);
}
