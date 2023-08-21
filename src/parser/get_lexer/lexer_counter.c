#include "../../../include/minishell.h"

/*
Cuando el argumento esté entre comillas (simples o dobles), esta
función lo contará como un string y avanzará el puntero hasta
salir de las comillas.
*/
void	quoted_lexer_counter(int *counter, char **s)
{
	char	c;

	while (1)
	{
		c = 0;
		if (**s == '\'' || **s == '\"')
		{
			c = **s;
			(*s)++;
		}
		while (**s != c && **s != '\0')
			(*s)++;
		while (**s != '\0' && **s != ' ' && **s != '\t' && **s != '|'
			&& **s != '<' && **s != '>')
			(*s)++;
		if (**s == '\0' || **s == ' ' || **s == '\t' || **s == '|'
			|| **s == '<' || **s == '>')
			break ;
	}
	*counter += 1;
}

/*
Hace lo mismo que la función anterior pero con los
metacaracteres: |, <, <<, >, >>.
*/
void	redirection_lexer_counter(int *counter, char **s)
{
	if (**s == '|')
		while (**s == '|')
			(*s)++;
	else
		while (**s == '<' || **s == '>')
			(*s)++;
	*counter += 1;
}

/*
Se encarga de contar el resto de palabras.
*/

void	words_counter(int *counter, char **s)
{
	if (**s != '\0')
	{
		if (**s != ' ' && **s != '\t'
			&& ((*s)[1] == ' ' || (*s)[1] == '\t'
			|| (*s)[1] == '<' || (*s)[1] == '>'
			|| (*s)[1] == '|' || (*s)[1] == '\0' ))
			*counter += 1;
		(*s)++;
	}
}

/*
Esta función calcula la memoria que hará falta para guardar
los argumentos pasados por terminal en strings individuales.
*/
int	lexer_counter(char *s)
{
	int		counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '"')
			quoted_lexer_counter(&counter, &s);
		else if (*s == '<' || *s == '>' || *s == '|')
			redirection_lexer_counter(&counter, &s);
		else
			words_counter(&counter, &s);
	}
	return (counter);
}
