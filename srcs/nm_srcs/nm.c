#include "nm.h"

void	*open_file(char **argv, int file_n)
{
	struct stat	buff;
	int			fd;
	void		*f;

	if ((fd = open(argv[file_n], O_RDONLY)) < 0)
	{
		ft_printf("nm: '%s': No such file\n", argv[file_n]);
		return (NULL);
	}
	if (fstat(fd, &buff) < 0
	|| !buff.st_size)
		return (NULL);
	f = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	return (f == MAP_FAILED ? NULL : f);
}

int parse_magic(t_elf_file ef)
{
	ft_memcpy(&ef.elf32header, ef.file, sizeof(Elf32_Ehdr));
	if (ef.elf32header.e_ident[EI_MAG0] != ELFMAG0  ||
		ef.elf32header.e_ident[EI_MAG1] != ELFMAG1  ||
		ef.elf32header.e_ident[EI_MAG2] != ELFMAG2  ||
		ef.elf32header.e_ident[EI_MAG3] != ELFMAG3  ||
	 	ef.elf32header.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_printf("nm: %s: file format not recognized\n", ef.fname);
		return (0);
	}
	if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS32)
		parse32elf(ef);
	else if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS64)
	{
		ft_memcpy(&ef.elf64header, ef.file, sizeof(Elf64_Ehdr));
		ft_printf("this is a 64 file\n");
	}
	return (0);
}

int ft_nm(void *file, char *fname)
{
	t_elf_file	ef;
	ef.fname = fname;
	ef.file = file;
	(void) ef;
	if (parse_magic(ef))
		return (1);	
	return (0);
}


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
	{
		if ((file = open_file(arg_cpy, argn)))
		{
			if (argc > 2)
				ft_printf("\n%s:\n", argv[argn]);
			if (ft_nm(file, arg_cpy[argn]))
				return (1);
		}
		argn++;
	}
	free_sp(arg_cpy);
	return (0);
}