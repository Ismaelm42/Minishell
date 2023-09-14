/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:15 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 15:46:16 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_global	*init_struct(char **env)
{
	t_global	*global;

	global = (t_global *)ft_calloc(sizeof(t_global), 1);
	global->env = copy_environment(env);
	global->lst_env = init_list();
	global->exit_status = 0;
	global->pid = NULL;
	global->fd = NULL;
	tcgetattr(STDIN_FILENO, &global->prompt);
	copy_environment_list(&global->lst_env, env);
	ft_envlst_short(&global->lst_env);
	return (global);
}

void	get_struct_data(t_global *global, char *input)
{
	int	token_return;

	signal(SIGINT, ft_sigint_open_pipe);
	global->input = ft_strdup(input);
	token_return = -1;
	while (token_return == -1)
	{
		token_return = get_tokens(input, global);
		if (token_return != -1)
			break ;
		input = readline("> ");
		if (!input || g_flag_exit_status == 1)
		{
			if (!input)
				global->exit_status = 258;
			else if (g_flag_exit_status == 1)
				global->exit_status = 1;
			break ;
		}
		input = ft_strjoin(global->input, input, 3);
		global->input = ft_strdup(input);
	}
	if (token_return != 0)
		free_global(global, 0);
}
