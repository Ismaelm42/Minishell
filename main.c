#include "minishell.h"

//funcion para leer de la terminal 
static char	*get_imput(const char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (*input)
		add_history(input);
	return (input);
}

//Manejador de señales para probar control+c exit (duda si hay q silenciarlo para q no muestre "C")
void	handler_signal(int signal)
{
	printf("signal %d", signal);
	exit(1);
}

int	main(void)
{
	char	*input;

	//bucle principal que solicite y procese 
	//los comandos del usuario, sale cuando rebie un exit para compilar read line hay q añadir el flag
	//-lreadline que tiene que ir al final de la compilacion 
	//signal(SIGINT, handler_signal);
	while (1)
	{
		input = get_imput(">> ");
		if (ft_strncmp(input, "exit", 4) == 0)
			break;
		// controlariamos los comandos recibidos
	}
	write_history("./history.txt");
	free(input);
	return (0);
}
