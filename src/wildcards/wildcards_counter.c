#include "../../include/minishell.h"

static void		search_wildcard(char *new_lexer, char *dir, int *size);
static void		get_wildcards_size(char *new_lexer, char **dir, int *size);

static void	search_wildcard(char *new_lexer, char *dir, int *size)
{
	int	flag;

	flag = 0;
	while (*new_lexer != '\0')
	{
		if (extract_wildcards(&new_lexer, &dir, flag) == 1)
			return ;
		flag = 1;
		while (*new_lexer == '*')
			new_lexer++;
	}
	if (ft_strlen(dir) == 0 || new_lexer[-1] == '*')
		(*size) += 1;
}

static void	get_wildcards_size(char *new_lexer, char **dir, int *size)
{
	int	n;
	int	saved_size;

	n = 0;
	saved_size = *size;
	while (dir[n] != NULL)
		search_wildcard(new_lexer, dir[n++], size);
	if (saved_size == *size)
		*size += 1;
}

int	get_wildcards_and_lexer_size(char **dir, char **lexer)
{
	char	*new_lexer;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (lexer[i] != NULL)
	{
		if (ft_strchr(lexer[i], '*') != NULL)
		{
			if (check_wildcard_conditions(lexer[i]) == 0)
			{
				new_lexer = handle_quoted_substr(ft_strdup(lexer[i]));
				get_wildcards_size(new_lexer, dir, &size);
				free_mem((void **)&new_lexer);
			}
			else
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}
