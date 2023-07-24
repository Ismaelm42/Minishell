#include "../include/minishell.h"

int	main(void)
{
	char	*input;
	char	**lexer;
	int		i;

	i = 0;
	while (i < 1)
	{
		rl_on_new_line();
		//input = readline(">> ");
		input = ft_strdup("$$ $ $12345 $ARG ${ARG}|$HOME ${LOGNAME} $PWD $NOARG");
		printf("%s\n\n", input);
		add_and_store_history(input);
		lexer = get_lexer(input);
		int n = 0;
		while (lexer[n] != NULL)
		{
			printf("token[%d]\t%s\n", n, lexer[n]);
			n++;
		}
		if (ft_strncmp(input, "exit", 5) == 0)
			exit (0);
		i++;
	}
	return (0);
}
