/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:15:49 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 16:16:19 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_status_flag(t_global *global)
{
	if (g_flag_exit_status == 1)
		global->exit_status = 1;
	else if (g_flag_exit_status == 2)
		global->exit_status = 131;
	g_flag_exit_status = 0;
}
