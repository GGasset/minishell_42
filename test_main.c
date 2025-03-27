
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

	//char *out = ft_shell_replace(argv[1], &shell);
	//char *out = ft_shell_replace("$USER'$USER $USER'$USER", &shell);
	if (check_invalid_quotes(argv[1]))
		return TRUE;

	char *out = ft_normalize_spaces(argv[1], 0);
	printf("Normalized->%s| end\n\n", out);
	
	char delimiter = 1;
	size_t i = 0;
	while (delimiter)
	{
		char *word = shell_get_word(out, i, &delimiter);
		printf("Word=[%s] Next_token=[%i, %c]", word, delimiter, delimiter);
		free(word);

		i = get_next_word_start_i(out, i);
	}
	free(out);
}

