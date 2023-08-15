#include "../../../include/minishell.h"

//Funcion que concatena en nv los string que no vengan entre comillado

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

//Funcion que concatena en nv los string que vengan entre comillado

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



// Funcion que obtiene la clave de la asignación pasandola en primer lugar por
// var_lexer_maker que no es mas que un split y el chequeo sintactico se hara 
// en el cálculo del size en caso de que algo falle no reservara memoria
static void	get_var_local(t_global *g)
{
	int		j;
	char	**d;
	char	*nv;
	int		i;
	char	*val;

	i = 0;
	nv = ft_strdup("");
	val = extract_value(g->input);
	d = var_lexer_maker(val);
	free(val);
	if (*d == NULL)
	{
		free(nv);
		nv = NULL;
	}
	while (d[i] != NULL)
	{
		j = 0;
		if ((d)[i][j] != '\'' && (d)[i][j] != '\"' && (d)[i][j] != ' '
			&& (d)[i][j] != '\0')
			no_quotes(j, &d[i], &nv);
		else if (((d)[i][j] == '\'' || (d)[i][j] == '\"') && nv)
			quotes(j, &d[i], &nv);
		i++;
	}
	free_lexer(d);
	if (nv != NULL)
		put_dictionary_local(nv, g);
}

//Función que chequea sintacticamente la clave (ARG) 

static int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(((int)key[i])))
	{	
		i++;
		while (key[i] != '\0' && ft_isalnum(key[i]))
			i++;
	}
	if (key[i] != '\0')
	{
		free(key);
		key = NULL;
		return (1);
	}
	else
	{
		free(key);
		key = NULL;
		return (0);
	}
}
//Funcion que sera llamada desde la principal si encuentra un = en el
// input devolvera 0 y lo tratara como una entrada de variable local
// si todo va bien lo introducira en el diccionario var_local

int	local_var(t_global *g, char *input)
{
	unsigned int	i;

	i = 0;
	while (input[i] != '\0')
		i++;
	if (ft_strrchr(input, '=') != NULL)
	{
		g->input = ft_strdup(input);
		if (check_key(extract_clue(g->input)) == 0)
		{
			get_var_local(g);
			free(g->input);
			g->input = NULL;
		}
		else
		{
			ft_putstr_fd("minishell: input: command not found ", 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
		return (1);
	print_stack(g->lst_local);
	return (0);
}