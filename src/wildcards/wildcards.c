#include "../../include/minishell.h"

static void		search_wildstrings(char ***new_lexer, char *dir, char *lex, int *i);
static void		get_wildcards_strings(char ***new_lexer, char **dir, char *lex, int *i);
static void		get_lexer_with_wildcards(char ***new_lexer, char **dir, char **lexer);

static void	search_wildstrings(char ***new_lexer, char *dir, char *lex, int *i)
{
	char	*dir_ptr;
	int		flag;

	flag = 0;
	dir_ptr = dir;
	while (*lex != '\0')
	{
		if (extract_wildcards(&lex, &dir, flag) == 1)
			return ;
		flag = 1;
		while (*lex == '*')
			lex++;
	}
	if (ft_strlen(dir) == 0 || lex[-1] == '*')
	{
		(*new_lexer)[*i] = ft_strdup(dir_ptr);
		*i += 1;
	}
}

static void	get_wildcards_strings(char ***new_lexer, char **dir, char *lex, int *i)
{
	int	n;

	n = 0;
	while (dir[n] != NULL)
		search_wildstrings(new_lexer, dir[n++], lex, i);
}

static void	get_lexer_with_wildcards(char ***new_lexer, char **dir, char **lexer)
{
	char	*lex;
	int		checker;
	int		i;

	i = 0;
	while (*lexer != NULL)
	{
		if (ft_strchr(*lexer, '*') != NULL
			&& check_wildcard_conditions(*lexer) == 0)
		{
			checker = i;
			lex = handle_quoted_substr(ft_strdup(*lexer));
			get_wildcards_strings(new_lexer, dir, lex, &i);
			free_mem((void **)&lex);
			if (checker == i)
				(*new_lexer)[i++] = ft_strdup(*lexer);
		}
		else
			(*new_lexer)[i++] = ft_strdup(*lexer);
		lexer++;
	}
}

char	**get_wildcards(char **lexer)
{
	char	**new_lexer;
	char	**dir;
	int		size;

	if (check_wildcards(lexer) == 1)
	{
		dir = get_dir_content();
		if (dir == NULL)
			return (NULL);
		size = get_wildcards_and_lexer_size(dir, lexer);
		new_lexer = (char **)ft_calloc(sizeof(char *), size + 1);
		get_lexer_with_wildcards(&new_lexer, dir, lexer);
		free_matrix((void ***)&dir, 0);
		free_matrix((void ***)&lexer, 0);
		return (new_lexer);
	}
	else
		return (lexer);
}
