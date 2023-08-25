#include "../../include/minishell.h"

/*
Observaciones -> export sin argumentos muestra todos los environment
pero precedidos de la cadena declare -x , tiene la particularidad que 
cuando hacemos export VAR= (sin valor) con env no se mostraran y con
export si aunque su valor este vacio, tb que con export nos mostrara
a lista ordenada alfabeticamente , mientras que con env con
sus posiciones originales 
*/
/*
PASOS:
    
-crear una nueva copia de char ** env pero esta vez ordenada alfabeticamente

-si export recibe un parametro con formato clave = valor la añada
 a ambas copias en la de export ordenada alfabeticamente pero si 
 el argumento no tiene = solo la añada a la lista export.
*/

/*
CORREGIR check_key  comprueba que el primer caracter sea alfanumerico si el
parametro tiene comillas peta y noo debe petar
*/

static int	parse_arg(t_global *g, int n)
{
	int		i;
	// char	*key;
	// char	*val;

	i = 0;
	
	if (ft_strrchr(g->tokens[n].arg[i], '=') == NULL)
	{	
		//dprintf(1, "ENTRA EN PARSE NO =");
		if (check_key(g->tokens[n].arg[i], 0) != 0)
			return (1);
	}	
	else
	{
		//dprintf(1, "ENTRA EN PARSE =");
		if (check_key(extract_clue(g->tokens[n].arg[i]), 1) != 0)
			return (1);
		else if (ft_strchr(extract_value(g->tokens[n].arg[i]), '!' ) != NULL)
			return (1);
	}
	// printf("ARGUMENTO %d %s\n", i, g->tokens[n].arg[i]);
	// printf("llega fin parse\n");
	return (0);
}

void	action_export(t_global *g, int n, int i)
{
	char	*key;

	while ((g->tokens[n].arg[i] != NULL))
	{
		if(parse_arg(g, n) == 0)
		{
		if (ft_strrchr(g->tokens[n].arg[i], '=') == NULL)
		{
			if (search_key(g->lst_env, g->tokens[n].arg[i]) == NULL)
			{
				key = ft_strdup(g->tokens[n].arg[i]);
				insert_last(&g->lst_env, create_nodo(key, ""));
			}
		}
		else
		{
			if (search_key_and_replace(g->lst_env, extract_clue \
			(g->tokens[n].arg[i]), extract_value(g->tokens[n].arg[i])) == -1)
				insert_last(&g->lst_env, create_nodo(extract_clue \
				(g->tokens[n].arg[i]), extract_value(g->tokens[n].arg[i])));
		}
		}
		i++;
	}
	ft_envlst_short(&g->lst_env);
}

void	ft_export(t_global *g, int n, int fd_out)
{
	if (g->tokens[n].arg[0] == NULL)
		print_stack(g->lst_env, fd_out);
}

/*

En export el valos de los envirnments sale con comillas

Dinstinguir si el argumento tienen = \ si tiene valor no nulo \
para meterlo en ambas env o solo en la lista, ..parsear 

clave -> solo caracteres alfanumericos pero el primer caracter solo alfabetico(!ARG accede a algo raro)
Value -> Le vale cualquier caracter imprimible excepto ! en primera posicion 
Casos:
// en Bash parsea el argumento recibido, si no cumple parseo muestra mensaje de error :" bash: export: `1ARG=0': not a valid identifier "
	y pasa al siguiente

	1- Si ARG= guarda ARG="" en ambas(parsear key)
	2- Si ARG guarda solo ARG (solo en lst->env)
	2- Si export var_entorno ya existe -> reemplaza su valor excepto si tenia valor asignado y el export se le pasa sin signo =, en tal caso permanece como esta
		si lleva signo = y nada mas lo reemplaza por un valor "" (vacio)

Tener en cuenta al buscar subcadena avanzar el punero por si hay que buscar el mismo string
	Ej: javi"hola" javi"adios"
	

*/
