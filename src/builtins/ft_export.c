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
-si export recibe un parametro con formato clave = valor ( no vacio ) la añada
 a ambas copias en la de export ordenada alfabeticamente pero si valor esta 
 vacio o es NULL solo la añada a la lista export.
*/
void	ft_export(t_global *g, int n)
{
	printf("ft_export\n");
	if (g->tokens[n].arg[0] == NULL)
		print_stack(g->lst_env);
	else
		printf("tiene argumentos, esta x terminar\n");
}