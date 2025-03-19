
#include "libft.h"
#include "stdio.h"

int main(int argc, char  *argv[])
{
	if (argc != 4)
	{
		return 0;
	}
	char *out = ft_replace(argv[1], argv[2], argv[3], 0);
	printf("%s\n", out);
	free(out);
}

