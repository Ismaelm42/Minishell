#include "../include/minishell.h"

char	*get_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (*input)
		add_history(input);
	return (input);
}

void	handler_signal(int signal)
{
	printf("signal %d", signal);
	exit(1);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = get_input(">> ");
		//signal(SIGINT, handler_signal);
		if (ft_strncmp(input, "exit", 5) == 0)
			exit(0);
		//esto se debe parsear primero.
		//Pero esto sería una opción después de haberlo parseado.
		//Sino saldría con exit123 cuando no debe.
		//Si aparece exit 123 sale.
		free(input);
		hola(1);
	}
	return (0);
}
