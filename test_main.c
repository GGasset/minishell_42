
#include "libft.h"
#include "stdio.h"
#include "parsing_header.h"
#include "execution_header.h"

int main(int argc, char  *argv[], char **envp)
{
	if (argc != 2 && 1)
	{
		printf("%s\n", argv[0]);
		return 0;
	}
	t_shell shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.envp = envp;

	printf("ARGV[1]=%s| end\n\n", argv[1]);

	int err = 0;
	t_raw_line tokenized = parse_input(argv[1], &err, &shell);
	printf("error: %i\n", err);


	t_exe exxxe = prepare(tokenized, &shell);
	for (size_t i = 0; i < exxxe.command_count; i++)
	{
		printf("------ %d/%d ------\nPath -> %s\nInput_Fd -> %d\nOutput_Fd -> %d\n", i+1, exxxe.command_count, 
			exxxe.commands[i].path, exxxe.commands[i].input_fd, exxxe.commands[i].output_fd);
		for (int w = 0; exxxe.commands[i].argv[w] != NULL; w++)
			printf("Argv -> %s\n", exxxe.commands[i].argv[w]);
	}
	free_raw_line(&tokenized, FALSE);
}

