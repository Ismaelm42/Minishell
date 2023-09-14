/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jroldan- <jroldan-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:47:56 by Jroldan-          #+#    #+#             */
/*   Updated: 2023/09/14 17:02:48 by Jroldan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void		no_quotes(int j, char **d, char **nv);
static void		quotes(int j, char **d, char **nv);
static void		build_var_local(char **nv, char **d);
static int		get_var_local(t_global *g);

static void	no_quotes(int j, char **d, char **nv)
{
	while ((*d)[j] != '<' && (*d)[j] != '>'
			&& (*d)[j] != '|' && (*d)[j] != '\'' && (*d)[j] != '\"'
			&& (*d)[j] != ' ' && (*d)[j] != '!' && (*d)[j] != '\0')
				j++;
	if ((*d)[j] == '\0')
		*nv = ft_strjoin(*nv, ft_substr(*d, 0, ft_strlen(*d), 0), 3);
	else
		*nv = NULL;
}

static void	quotes(int j, char **d, char **nv)
{
	char	quote;		

	quote = (*d)[j];
	j++;
	while ((*d)[j] != quote)
		j++;
	if ((*d)[j] == quote)
		*nv = ft_strjoin(*nv, ft_substr(*d, 1, ft_strlen(*d) - 2, 0), 3);
	else
		*nv = NULL;
}

static void	build_var_local(char **nv, char **d)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (d[++i])
	{
		j = 0;
		if ((d)[i][j] != '\'' && (d)[i][j] != '\"' && (d)[i][j] != ' '
			&& (d)[i][j] != '\0')
			no_quotes(j, &d[i], nv);
		else if (((d)[i][j] == '\'' || (d)[i][j] == '\"') && nv)
			quotes(j, &d[i], nv);
	}
}

static int	get_var_local(t_global *g)
{
	char	**d;
	char	*nv;
	char	*val;
	char	*key;

	key = extract_clue(g->input);
	nv = ft_strdup("");
	val = extract_value(g->input);
	d = var_lexer_maker(val);
	free(val);
	if (*d == NULL)
		free_mem((void **)&nv);
	build_var_local(&nv, d);
	free_matrix((void ***)&d, 0);
	if (nv != NULL)
	{	
		if (search_env_replace(ft_strdup(key), ft_strdup(nv), g->env, 1) == 1)
			return (free_mem((void **)&key), put_dictionary_local(nv, g), 0);
		else
			return (search_key_and_replace(g->lst_env, key, nv, 2), \
			free_mem((void **)&key), 0);
	}
	else
		return (free_mem((void **)&key), 1);
}

int	local_var(t_global *g, char *input)
{
	unsigned int	i;

	i = 0;
	while (input[i] != '\0')
		i++;
	if (ft_strrchr(input, '=') != NULL)
	{
		if (check_key(extract_clue(g->input), 1) == 0)
		{
			if (get_var_local(g) == 0)
			{
				free_mem((void **)&input);
				return (0);
			}
		}
	}
	return (1);
}
