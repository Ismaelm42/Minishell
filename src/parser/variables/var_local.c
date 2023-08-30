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


// Funcion que obtiene la clave de la asignación pasandola en primer lugar por
// var_lexer_maker que no es mas que un split y el chequeo sintactico se hara 
// en el cálculo del size en caso de que algo falle no reservara memoria
static int	get_var_local(t_global *g)
{
	char	**d;
	char	*nv;
	char	*val;

	nv = ft_strdup("");
	val = extract_value(g->input);
	d = var_lexer_maker(val);
	free(val);
	if (*d == NULL)
	{
		free(nv);
		nv = NULL;
	}
	build_var_local(&nv, d);
	free_matrix((void ***)&d, 0);
	

	printf("Nv = %s\n", nv);
	if (nv != NULL)
		return (put_dictionary_local(nv, g), 0);
	else
		return (1);
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
