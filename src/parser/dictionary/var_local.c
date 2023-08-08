#include "../../../include/minishell.h"

static void	control_quotation_marks_2(char *str)
{
	char	*key;
	char	*val;
	int		flag;
	int		i;

	flag = 0;
	i = -1;
	key = extract_clue(str);
	val = extract_value(str);
	if (val[0] != ' ' && val[0] != '\0')
	{
		if (val[0] == '\"')
		{
			i++;
			while (val[++i] != '\"' && val[i])
				flag = 1;
			if (val[i] == '\"' && flag == 1)
			{	
				free(val);
				val = ft_substr(val, 1, i - 1, 0);
				printf("key = %s\n", key);//busco en dicc_local si existe cambio value si no la añado al final
				printf("val = %s\n", val);
			}
			else
			{
				printf("error No cierre de comillas");
				exit (1);
			}
		}
	}
}

static void	control_quotation_marks_1(char *str)
{
	char	*key;
	char	*val;
	int		flag;
	int		i;

	flag = 0;
	i = -1;
	key = extract_clue(str);
	val = extract_value(str);
	if (val[0] != ' ' && val[0] != '\0')
	{
		if (val[0] == '\'')
		{
			i++;
			while (val[++i] != '\'' && val[i])
				flag = 1;
			if (val[i] == '\'' && flag == 1)
			{	
				free(val);
				val = ft_substr(val, 1, i - 1, 0);
				printf("key = %s\n", key);//busco en dicc_local si existe cambio value si no la añado al final
				printf("val = %s\n", val);
			}
			else
			{
				printf("error No cierre de comillas");
				exit (1);
			}
		}
	}
}

int	local_var(char *s)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (ft_isalpha(((int)s[0])))
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i])
				i++;
		str = ft_substr(s, 0, i, 0);
		printf("str->%s\n", str);
		//busco comillas el cierre y concateno con la anterior strjoin
		if (ft_strrchr(str, 61) != NULL)
		{
			control_quotation_marks_1(str);
			control_quotation_marks_2(str);
			//printf("key = %s\n", extract_clue(str));
			//printf("val = %s\n", extract_value(str));
		}
		else
			return (1);
	}
	else
		return (1);
	return (0);
}
