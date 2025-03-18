
#include "common_header.h"

static char	*replace(char *s, size_t start, size_t replaced_len, char *new)
{
	size_t	new_len;
	size_t	s_new_len;
	char	*out;

	if (!s)
		return (0);
	new_len = ft_strlen(new_len);
	s_new_len = ft_strlen(s);
	if (start + replaced_len > s_new_len)
		replaced_len = s_new_len - start;
	s_new_len = s_new_len - replaced_len + new_len;
	out = malloc(s_new_len + 1);
	if (!out)
		return (0);
	out[s_new_len] = 0;
	ft_memcpy(out, s, start);
	ft_memcpy(out + start, new, new_len);
	ft_memcpy(out + start + replaced_len, s_new_len - start - replaced_len);
	return (out);
}

char	*ft_mreplace(char *s, char *old, char *new, int free_s)
{
	size_t	s_len;
	size_t	old_len;
	size_t	new_len;
	size_t	replace_start;

	if (!s || !old || !new)
		return (0);
	s_len = ft_strlen(s);
	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	replace_start = (size_t)ft_strnstr(s, old, s_len);
	if (replace_start)
		replace_start -= (size_t)s;
	while (replace_start)
	{
		s = ft_strdup_free(s, free_s);
		free_s = 1;
		s = replace(s, replace_start, old_len, new);
		replace_start = (size_t)ft_strnstr(s + replace_start + new_len, old,
			s_len - replace_start);
		if (replace_start)
			replace_start -= (size_t)s;
	}
	return (s);
}
