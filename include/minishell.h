#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_lexer
{
	char		*input;
	char		*variable;
	char		*expanded;
	int			position;
}				t_lexer;

typedef struct s_token
{
	char		*command;
	char		**arg;
	char		**infile;
	char		**heredoc;
	char		**outfile;
	char		**append;
	int			fd_in;
	int			fd_out;
}				t_token;

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_global
{
	char		*input;
	char		**env;
	int			pipeline;
	int			fd_stdin;
	int			fd_stdout;
	int			exit_status;
	t_node		*lst_env;
	t_node		*lst_local;
	t_token		*tokens;
}				t_global;

//parser/history/bash_history
void		add_and_store_history(char *input);

//parser/get_lexer/lexer_counter
void		quoted_lexer_counter(int *counter, char **s);
void		redirection_lexer_counter(int *counter, char **s);
void		words_counter(int *counter, char **s);
int			lexer_counter(char *s);

//parser/get_lexer/lexer_maker
char		*handle_quoted_substr(char *s);
void		redirection_lexer_splitter(int *n, char **s, char ***lexer);
void		words_splitter(int *n, char **s, char ***lexer);
char		**lexer_maker(char *s);

//parser/get_lexer/utils
char		reject_quotes(char *s, char *substr, int *i, int *j);
void		check_quotes(char *s, int *length);

//parser/get_lexer/get_lexer
char		**get_lexer(char *input, t_global *global);

//parser/expansion_variable/get_variables
int			variable_expansion_counter(char *input);
void		variable_lexer_filler(int *n, int length, char **s, t_lexer *lexer);
void		check_expansion_and_delimiters(int *n, char **s, t_lexer *lexer);
t_lexer		*get_variable_expansion_lexer(char *input);

//parser/expansion_variable/expand_variables
int			get_variable_from_env(int n, t_lexer *lexer, t_global *global);
int			get_variable_from_history(int n, t_lexer *lexer, t_global *global);
void		get_variable_expansion_value(int n, t_lexer *lexer, t_global *global);
char		*expansion_variable(char *input, t_global *global);

//parser/expansion_variable/replace_variables
void		get_size_variables(int *var, int *exp, t_lexer *lexer);
void		replace_function(char *new_input, char *input, t_lexer *lexer);
char		*replace_variables(char *input, t_lexer *lexer);

//parser/expansion_variable/utils
t_lexer		*create_expansion_lexer_struct(char *input, int size);
void		handle_edge_cases(char **input, int *counter);
void		skip_quotes(char **s, int *lock);
int			check_edge_cases(char *s);
void		read_from_history(int n, t_lexer *lexer, char *needle, int size); //obsoleta
t_lexer		*free_expansion_lexer(t_lexer *lexer, int flag);

//parser/utils/gnl
char		*gnl(int fd);
char		*read_fd(int fd, char *static_buffer);
char		*return_line(char *static_buffer);
char		*return_static(char *static_buffer);

//parser/get_struct/check_syntax
int			quotes_check(char *lexer);
int			pipes_and_redirections_check(char **lexer, int n);
int			next_lexer_check(char **lexer, int n);
int			syntax_error_check(char **lexer);

//parser/get_struct/get_struct
t_global	*init_struct(char **env);
void		get_struct_data(t_global *global, char *input);

//src/parser/get_struct/get_tokens
int			lexer_pipes_counter(char **lexer);
int			get_tokens(char *input, t_global *global);

//src/parser/get_struct/tokens_counter
void		redirection_and_command_token_counter(char ***lexer, int **size);
int			*token_counter(char **lexer);
void		check_last_token_file_fd(t_token *tokens, char **lexer, int n);
void		get_token_fd(t_token *tokens, char **lexer);

//src/parser/get_struct/tokens_maker
void		allocate_token_memory(t_token *tokens, int *size);
void		check_token_type(t_token *tokens, char ***lexer, int **i);
void		token_filler(t_token *tokens, char **lexer);
void		advance_lexer_tokens(char ***lexer, t_token **tokens);
void		token_maker(t_token *tokens, char **lexer);

//parser/var_environment
char		**copy_environment(char **env);
char		*search_env(char *var, char **envp);
void		free_env(char **env_copy);

//parser/variables/var_local
int			local_var(t_global *g, char *input);
char		*extract_clue(char *c);
char		*extract_value(char *c);
char		*search_key(t_node *lst, char *key);
int			search_key_and_replace(t_node *lst, char *key, char *val);
void		var_quoted_lexer_splitter(int *n, char **s, char ***lexer);
void		var_quoted_lexer_counter(int *counter, char **s);
void		var_words_counter(int *counter, char **s);
int			var_lexer_counter(char *s);
void		var_words_splitter(int *n, char **s, char ***lexer);
char		**var_lexer_maker(char *s);
void		put_dictionary_local(char *nv, t_global *g);
int			check_key(char *key);

//parser/utils
char		**free_matrix(char **matrix);
void		destroy_global(t_global *global);
void		free_global(t_global *global, int flag);

//parser/utils/list_utils
t_node		*init_list(void);
t_node		*create_nodo(char *key, char *value);
void		insert_last(t_node **list, t_node *new_nodo);
t_node		*final(t_node *list);
void		print_stack(t_node *list, int fd_out);
void		copy_environment_list(t_node **lst_env, char **env);
void		ft_envlst_short(t_node **lst);

//parser/utils/list_utils_2
void		ft_free_lst(t_node *lst);
int			ft_size_lst(t_node *lst);
void		error(void);

//signals/signals
void		ft_sigint_handler(int sig);
void		ft_sigquit_handler(int sig);
int			control_d(char *input);

//exec/execute_commands
int			create_pipes_and_pid(t_global *global, pid_t **pid, int ***fd);
int			child_process(t_global *global, int **fd, int n);
int			parent_process(t_global *global, int **fd, pid_t *pid, int n);
int			execute_commands(t_global *global);

//exec/heredocs
void		get_heredocs(char **heredoc, int fd);
int			process_heredocs(t_global *global);

//exec/infiles
int			handle_heredocs(int n);
int			handle_infiles(char ***infiles, int fd_type);
int			get_input_file(t_global *global, int n);
int			fd_in_handler(t_global *global, int n, int fd_in, int fd_out);

//exec/outfiles
int			handle_outfiles(char *outfile, int write_flag, int infile_type);
int			detect_output_file(char **outfiles, int infile_type, int fd_type);
int			get_output_file(t_global *global, int n);
int			fd_out_handler(t_global *global, int n, int fd_out);

//exec/get_command
char		**get_path(char **env);
int			check_cmd_path(char *cmd, char *cmd_path, char *path, int flag);
char		*get_command_path(t_global *global, int n);
char		**get_exec_command(t_global *global, int n);

//exec/utils
void		access_error_message(char *error, char *message);
char		*search_in_path(t_global *global, int n, char **path, char *cmd_path);
void		fd_closer(int **fd, int pipeline, int n);
void		print_error(char *message, int code_error);
void		write_on_fd(int fd_in, int fd_out);

//build_in
void		ft_pwd(int fd_in, int fd_out);
void		ft_env(t_global *g);
void		ft_export(t_global *g, int n, int fd_out);
int			check_built_ins(t_global *g, int n);
int			built_ins(t_global *g, int n, int fd_in, int fd_out);


#endif
