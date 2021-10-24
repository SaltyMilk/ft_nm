#include "utils.h"

unsigned int sp_len(char **sp)
{
	unsigned int i = 0;

	while (sp[i])
		i++;
	return (i);
}

void free_sp(char **sp)
{
	for (unsigned int i = 0; sp[i]; i++)
		free(sp[i]);
	free(sp);
}

char **copy_sp(char **sp)
{
	unsigned int i = 0;
	char **cpy;

	if (!(cpy = malloc(sizeof(char *) * (sp_len(sp) + 1))))
		return (NULL);
	while (sp[i])
	{
		if (!(cpy[i] = ft_strdup(sp[i])))
			return (NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
