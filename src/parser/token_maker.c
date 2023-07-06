#include "../../include/minishell.h"

void	quoted_token_splitter(int *n, char **s, char ***tokens)
{
	char	c;
	int		length;

	length = 0;
	c = **s;
	while ((*s)[length + 1] != c)
		length++;
	length += 2;
	(*tokens)[*n] = ft_substr(*s, 0, length);
	*n += 1;
	while (length -- > 0)
		(*s)++;
}

void	redirection_token_splitter(int *n, char **s, char ***tokens)
{
	int	length;

	if (**s == '|')
	{
		(*tokens)[*n] = ft_substr(*s, 0, 1);
		(*s)++;
		*n += 1;
	}
	else
	{
		length = 0;
		while ((*s)[length] == '<' || (*s)[length] == '>')
			length++;
		(*tokens)[*n] = ft_substr(*s, 0, length);
		*n += 1;
		while (length -- > 0)
			(*s)++;
	}
}

void	words_splitter(int *n, char **s, char ***tokens)
{
	int	length;

	length = 0;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	while ((*s)[length] != '\'' && (*s)[length] != '"'
		&& (*s)[length] != '<' && (*s)[length] != '>'
		&& (*s)[length] != ' ' && (*s)[length] != '\t'
		&& (*s)[length] != '|' && (*s)[length] != '\0')
		length++;
	if (length > 0)
	{
		(*tokens)[*n] = ft_substr(*s, 0, length);
		*n += 1;
		while (length -- > 0)
		(*s)++;
	}

}

void	token_splitter(int *n, char **s, char ***tokens)
{
	if (**s == '\'' || **s == '"')
		quoted_token_splitter(n, s, tokens);
	else if (**s == '<' || **s == '>' || **s == '|')
		redirection_token_splitter(n, s, tokens);
	else
		words_splitter(n, s, tokens);
	//puedo proteger substrings de tokens aqui, ya que en cada bucle se reservara memoria
	//y ninguno debe ser null que devuelva -1 si hay una reserva de memoria fallida.
	//y usar el exit o lo que sea en tal caso.
}

char	**token_maker(char *s)
{
	char	**tokens;
	int		size;
	int		n;

	n = 0;
	size = token_counter(s);
	tokens = (char **)malloc(sizeof(char **) * size + 1);
	if (!tokens)
		return (NULL);
	while (n < size)
		token_splitter(&n, &s, &tokens);
	tokens[n] = 0;
	return (tokens);
}

int	main(void)
{
	char	**str;
	char	*phrase = "   cat | ls -a awk\"blib|\" hola amigo \"lablu\"";
	int		i;

	printf("counter = %d\n", token_counter(phrase));

	str = token_maker(phrase);
	i = 0;
	while (str[i] != NULL)
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
	printf("str[%d] = %s\n", i, str[i]);


}



//awk'wc -ls'
