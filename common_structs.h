
enum operator_type
{
	no_stdout_redirect,
	no_pipe_stdout_redirect,
	stdin_redirect,
	stdout_redirect,
	stdin_delimiter,
	stdout_append,
	pipe
};

typedef struct s_raw_cmd
{
	char *file;
	char **argv;
	operator_type type;
	int is_builtin;
}		t_raw_cmd;

/*
 * example "<in cat | cat>outi"
 raw_commands:
	- {in, 0, stdin_redirect}
	- {cat, {"cat"}, pipe}
	- {cat, {"cat"}, pipe}
	- {outi, 0, stdout_redirect}
 len: 4
 * example "<< "EOF" cat | cat -e | cat"
 raw_commands:
	- {EOF, 0, stdin_delimiter}
	- {cat, {"cat"}, pipe}
	- {cat, {"cat", "-e"}, pipe}
	- {cat, {"cat"}, pipe}
 * example "<in cat"
 raw_commands:
	- {in, 0, stdin_redirect}
	- {cat, {"cat"}, no_stdout_redirect}
 * example "<in cat > out"
	- {in, 0, stdin_redirect}
	- {cat, {"cat"}, no_pipe_stdout_redirect}
	- {out, 0, stdout_redirect}
*/
typedef struct s_raw_line
{
	t_raw_cmd		*raw_commands;
	size_t			len;
}		t_raw_line;

typedef struct s_shell
{
	char **envp;
}		t_shell;
