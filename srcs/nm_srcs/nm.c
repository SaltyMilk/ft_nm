#include "nm.h"

int		main(int argc, char **argv)
{
	void	*file;
	int		argn;

	char **arg_cpy;

	if (!(arg_cpy = copy_sp(argv)))
		return (1);
	if (argc < 2)
	{
		free_sp(arg_cpy);
		if (!(arg_cpy = malloc(sizeof(char *) * 3)))
			return (1);
		if (!(arg_cpy[0] = ft_strdup(argv[0])))
			return (1);
		if (!(arg_cpy[1] = ft_strdup("a.out")))
			return (1);
		arg_cpy[2] = NULL;
		argc = 2;
	}
	argn = 1;
	while (argn < argc)
	{ (void) file;
	//	if (!(file = open_file(arg_cpy, argn)))
	//		return (1);
		argn++;
	}
	free_sp(arg_cpy);
	ft_printf("done\n");
	return (0);
}