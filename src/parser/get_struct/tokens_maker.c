#include "../../../include/minishell.h"

char	*handle_quoted_substr(char *s)
{
	char	*substr;
	int		c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = 0;
	substr = (char *) ft_calloc(sizeof(char), ft_strlen(s) + 1);
	while (s[j] != '\0')
	{
		while (s[j] != '\'' && s[j] != '\"' && s[j] != '\0')
			substr[i++] = s[j++];
		c = reject_quotes(s, substr, &i, &j);
	}
	if (c != 0)
		return (free_mem((void **)&substr), s);
	return (free_mem((void **)&s), substr);
}

/*
Reserva la memoria necesaria para cada campo de la estructura tokens.
*/
void	allocate_token_memory(t_token *tokens, int *size)
{
	tokens->infile = (char **)ft_calloc(sizeof(char *), size[0] + 1);
	tokens->outfile = (char **)ft_calloc(sizeof(char *), size[1] + 1);
	tokens->heredoc = (char **)ft_calloc(sizeof(char *), size[2] + 1);
	tokens->append = (char **)ft_calloc(sizeof(char *), size[3] + 1);
	tokens->arg = (char **)ft_calloc(sizeof(char *), size[5] + 1);
	free_mem((void **)&size);
}

/*
Identifica el tipo de token.
*/
void	check_token_type(t_token *tokens, char ***lexer, int **i)
{
	if (ft_strncmp(**lexer, "<", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->infile[(*i)[0]++] = handle_quoted_substr(ft_strdup(**lexer));
	}
	else if (ft_strncmp(**lexer, ">", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->outfile[(*i)[1]++] = handle_quoted_substr(ft_strdup(**lexer));
	}
	else if (ft_strncmp(**lexer, "<<", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->heredoc[(*i)[2]++] = handle_quoted_substr(ft_strdup(**lexer));
	}
	else if (ft_strncmp(**lexer, ">>", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->append[(*i)[3]++] = handle_quoted_substr(ft_strdup(**lexer));
	}
	else if (tokens->command == NULL)
		tokens->command = handle_quoted_substr(ft_strdup(**lexer));
	else
		tokens->arg[(*i)[5]++] = handle_quoted_substr(ft_strdup(**lexer));
}

/*
Rellena el campo del token específico haciendo una copia del lexer.
*/
void	token_filler(t_token *tokens, char **lexer)
{
	int	*i;

	i = (int *)ft_calloc(sizeof(int), 6);
	while (*lexer != NULL && ft_strncmp(*lexer, "|", ft_strlen(*lexer)) != 0)
	{
		check_token_type(tokens, &lexer, &i);
		lexer++;
	}
	free_mem((void **)&i);
}

/*
Avanza el lexer para el nuevo bucle.
*/
void	advance_lexer_tokens(char ***lexer, t_token **tokens)
{
	while (**lexer != NULL && ft_strncmp(**lexer, "|", ft_strlen(**lexer)) != 0)
		(*lexer)++;
	if (**lexer != NULL)
	{
		(*lexer)++;
		(*tokens)++;
	}
}
