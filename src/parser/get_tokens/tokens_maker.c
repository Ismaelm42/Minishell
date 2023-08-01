#include "../../../include/minishell.h"

void	allocate_token_memory(t_token *tokens, int *size)
{
	tokens->infile = (char **)ft_calloc(sizeof(char *), size[0] + 1);
	tokens->outfile = (char **)ft_calloc(sizeof(char *), size[1] + 1);
	tokens->heredoc = (char **)ft_calloc(sizeof(char *), size[2] + 1);
	tokens->append = (char **)ft_calloc(sizeof(char *), size[3] + 1);
	tokens->arg = (char **)ft_calloc(sizeof(char *), size[5] + 1);
}

void	check_token_type(t_token *tokens, char ***lexer, int **i)
{
	if (ft_strncmp(**lexer, "<", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->infile[(*i)[0]++] = ft_strdup(**lexer);
	}
	else if (ft_strncmp(**lexer, ">", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->outfile[(*i)[1]++] = ft_strdup(**lexer);
	}
	else if (ft_strncmp(**lexer, "<<", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->heredoc[(*i)[2]++] = ft_strdup(**lexer);
	}
	else if (ft_strncmp(**lexer, ">>", ft_strlen(**lexer)) == 0)
	{
		(*lexer)++;
		tokens->append[(*i)[3]++] = ft_strdup(**lexer);
	}
	else if (tokens->command == NULL)
		tokens->command = ft_strdup(**lexer);
	else
		tokens->arg[(*i)[5]++] = ft_strdup(**lexer);
}

void	token_filler(t_token *tokens, char **lexer)
{
	int	*i;

	i = (int *)ft_calloc(sizeof(int), 6);
	while (*lexer != NULL && ft_strncmp(*lexer, "|", ft_strlen(*lexer)) != 0)
	{
		check_token_type(tokens, &lexer, &i);
		lexer++;
	}
}

void	advance_lexer_tokens_and_free_size(char ***lexer, t_token **tokens)
{
	while (**lexer != NULL && ft_strncmp(**lexer, "|", ft_strlen(**lexer)) != 0)
		(*lexer)++;
	if (**lexer != NULL)
	{
		(*lexer)++;
		(*tokens)++;
	}
}

void	print_result(t_token *tokens, int *size)
{
	int	i;

	i = 0;
	(void)size;
	while (tokens->infile[i] != NULL)
	{
		printf("tokens->infile[%d] = %s\n", i, tokens->infile[i]);
		i++;
	}
	// printf("size->infile = %d\n", size[0]);
	// printf("\n");

	i = 0;
	while (tokens->outfile[i] != NULL)
	{
		printf("tokens->outfile[%d] = %s\n", i, tokens->outfile[i]);
		i++;
	}
	// printf("size->outfile = %d\n", size[1]);
	// printf("\n");

	i = 0;
	while (tokens->heredoc[i] != NULL)
	{
		printf("tokens->heredoc[%d] = %s\n", i, tokens->heredoc[i]);
		i++;
	}
	// printf("size->heredoc = %d\n", size[2]);
	// printf("\n");

	i = 0;
	while (tokens->append[i] != NULL)
	{
		printf("tokens->append[%d] = %s\n", i, tokens->append[i]);
		i++;
	}
	// printf("size->append = %d\n", size[3]);
	// printf("\n");

	printf("tokens->command = %s\n", tokens->command);
	// printf("\n");

	i = 0;
	while (tokens->arg[i] != NULL)
	{
		printf("tokens->arg[%d] = %s\n", i, tokens->arg[i]);
		i++;
	}
	// printf("size->arg = %d\n", size[5]);
	printf("\n");
	printf("\n");
}

void	token_maker(t_token *tokens, char **lexer)
{
	int	*size;

	size = token_counter(lexer);
	while (*lexer != NULL)
	{
		size = token_counter(lexer);
		allocate_token_memory(tokens, size);
		token_filler(tokens, lexer);
		printf("hola\n");
		print_result(tokens, size);
		advance_lexer_tokens_and_free_size(&lexer, &tokens);
	}
}

