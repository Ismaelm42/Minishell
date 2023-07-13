#include "../../../include/minishell.h"

char	*gnl(int fd)
{
	static char		*static_buffer;
	char			*buffer;

	if (fd == -1)
		return (NULL);
	static_buffer = read_fd(fd, static_buffer);
	if (static_buffer == NULL || !static_buffer)
		return (NULL);
	buffer = return_line(static_buffer);
	static_buffer = return_static(static_buffer);
	return (buffer);
}

char	*read_fd(int fd, char *static_buffer)
{
	char		*buffer;
	long int	bytes_read;

	if (static_buffer && ft_strchr(static_buffer, 10))
		return (static_buffer);
	bytes_read = 1;
	while (bytes_read > 0 && !(ft_strchr(static_buffer, 10)))
	{
		buffer = ft_calloc(100 + 1, sizeof(char));
		bytes_read = read(fd, buffer, 100);
		if (bytes_read == -1)
			return (free(buffer), free(static_buffer), NULL);
		else if (bytes_read == 0)
			return (free(buffer), static_buffer);
		else if (!static_buffer)
			static_buffer = ft_strdup(buffer);
		else
			static_buffer = ft_strjoin(static_buffer, buffer);
		free(buffer);
	}
	return (static_buffer);
}

char	*return_line(char *static_buffer)
{
	char	*buffer;
	int		length;

	if (static_buffer && ft_strchr(static_buffer, 10))
	{
		length = 0;
		while (static_buffer[length] != 10)
			length++;
		length++;
		buffer = ft_substr(static_buffer, 0, length);
		return (buffer);
	}
	return (static_buffer);
}

char	*return_static(char *static_buffer)
{
	char	*buffer;
	int		n;
	int		length;

	if (static_buffer && ft_strchr(static_buffer, 10))
	{
		n = 0;
		while (static_buffer[n] != 10)
			n++;
		n++;
		length = 0;
		while (static_buffer[n + length] != '\0')
			length++;
		if (length == 0)
			return (free (static_buffer), NULL);
		buffer = ft_substr(static_buffer, n, length);
		return (free (static_buffer), buffer);
	}
	return (NULL);
}
