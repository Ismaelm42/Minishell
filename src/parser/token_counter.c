#include "../../include/minishell.h"

void	quoted_token_counter(int *counter, char **s)
{
	char	c;

	c = **s;
	(*s)++;
	while (**s != c && **s != '\0')
		(*s)++;
	if ((**s) == c)
		(*s)++;
	*counter += 1;
}

void	redirection_token_counter(int *counter, char **s)
{
	if (**s == '|')
		(*s)++;
	else
		while (**s == '<' || **s == '>')
			(*s)++;
	*counter += 1;
}

void	words_counter(int *counter, char **s)
{
	if (**s != '\0')
	{
		if (**s != ' ' && ((*s)[1] == ' '
			|| (*s)[1] == '\'' || (*s)[1] == '"'
			|| (*s)[1] == '<' || (*s)[1] == '>'
			|| (*s)[1] == '|' || (*s)[1] == '\0' ))
			*counter += 1;
		(*s)++;
	}
}

int	token_counter(char *s)
{
	int		counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
			quoted_token_counter(&counter, &s);
		else if (*s == '<' || *s == '>' || *s == '|')
			redirection_token_counter(&counter, &s);
		else
			words_counter(&counter, &s);
	}
	return (counter);
}

// int	main(void)
// {
// 	int i = token_counter("buenos ' dias '   >< <hola   ");
// 	printf("%d\n", i);

// }
