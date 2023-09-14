/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:02 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:03:27 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char		*get_home_dir(char *dir);

static char	*get_home_dir(char *dir)
{
	char	*home;

	if ((ft_strnstr(dir, "/home/", 6) != NULL && ft_strlen(dir) > 6)
		|| (ft_strnstr(dir, "/Users/", 7) != NULL && ft_strlen(dir) > 7))
	{
		home = ft_strchr((char *)&dir[7], '/');
		if (home == NULL && ft_strlen(dir) > 6)
		{
			home = ft_strdup("~");
			return (free(dir), home);
		}
		if (home != NULL)
		{
			home = ft_strjoin("~", home, 0);
			return (free(dir), home);
		}
	}
	return (dir);
}

char	*readline_prompt(void)
{
	char	*prompt;
	char	*input;
	char	*dir;

	rl_on_new_line();
	prompt = ft_strdup("\001\033[0;31m\002minishell:");
	dir = NULL;
	dir = getcwd(dir, 0);
	if (dir == NULL)
	{
		free_mem((void **)&prompt);
		ft_putstr_fd("\001\x1b[0m\002minishell: pwd error\n", 2);
		return (NULL);
	}
	dir = get_home_dir(dir);
	prompt = ft_strjoin(prompt, "\001\033[0;36m\002", 1);
	prompt = ft_strjoin(prompt, dir, 3);
	prompt = ft_strjoin(prompt, "\001\x1b[0m\002$ ", 1);
	input = readline(prompt);
	free_mem((void **)&prompt);
	return (input);
}
