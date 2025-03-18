
#include "libft.h"

char	*ft_strdup_free(char *s, int free_s)
{
	char *out = ft_strdup(s);
	if (free_s)
		free(s);
}
