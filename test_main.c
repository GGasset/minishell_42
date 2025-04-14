
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

	printf("ARGV[1]=%s| end\n", argv[1]);

	if (check_invalid_quotes(argv[1]))
	{
		printf("Invalid quotes. Exiting...\n");
		return TRUE;
	}

	char *tmp = ft_replace(argv[1], "$ ", "$", FALSE);
	printf("Replacing \"$ \" with \"$\"...\nNew ARGV[1]=%s| end\n\n", tmp);

	
	char *out = ft_shell_replace(tmp, &shell);
	printf("Expanded->%s| end\n", out);

	free(tmp);

	out = ft_normalize_spaces(out, TRUE);
	printf("Normalized->%s| end\n\n", out);

	char **splitted = shell_split(out, '|');
	printf("Splitted..\n");
	size_t i = 0;
	for (i = 0; splitted && splitted[i]; i++)
	{
		printf("Split_out=\"%s\"\n", splitted[i]);
	}
	printf("%s\n", splitted[i]);
	ft_free_splitted(splitted);

	char delimiter = 1;
	i = 0;
	while (delimiter)
	{
		char *word = shell_get_word(out, i, &delimiter);
		printf("Word=[%s] Next_token=[%i, %c]\n", word, delimiter, delimiter);
		free(word);

		i = get_next_word_start_i(out, i);
	}

	int err = 0;
	t_raw_line tokenized = tokenize_line(out, &err, &shell);
	printf("error: %i\n", err);
	free_raw_line(&tokenized, FALSE);
	free(out);
}

