#include "nm.h"

void	*open_file(char **argv, int file_n, unsigned int *fsize)
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
	*fsize = buff.st_size;
	return (f == MAP_FAILED ? NULL : f);
}

int parse_magic(t_elf_file ef)
{
	ft_memcpy(&ef.elf32header, ef.file, sizeof(Elf32_Ehdr));
	if (sizeof(Elf32_Addr) > ef.fsize				||
		ef.elf32header.e_ident[EI_MAG0] != ELFMAG0  ||
		ef.elf32header.e_ident[EI_MAG1] != ELFMAG1  ||
		ef.elf32header.e_ident[EI_MAG2] != ELFMAG2  ||
		ef.elf32header.e_ident[EI_MAG3] != ELFMAG3  ||
	 	ef.elf32header.e_ident[EI_CLASS] == ELFCLASSNONE)
	{
		ft_printf("nm: %s: file format not recognized\n", ef.fname);
		return (0);
	}
	if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS32)
	{
		if (parse32elf(ef))
			ft_printf("nm: File corrupted\n");
	}
	else if (ef.elf32header.e_ident[EI_CLASS] == ELFCLASS64)
	{
		ft_memcpy(&ef.elf64header, ef.file, sizeof(Elf64_Ehdr));
		if (parse64elf(ef))
			ft_printf("nm: File corrupted\n");
	}
	return (0);
}

int ft_nm(void *file, char *fname, unsigned int fsize)
{
	t_elf_file	ef;
	ef.fname = fname;
	ef.file = file;
	ef.fsize = fsize;
	(void) ef;
	if (parse_magic(ef))
		return (1);	
	return (0);
}


int		main(int argc, char **argv)
{
	void			*file;
	int				argn;
	unsigned int	fsize;

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
		if ((file = open_file(arg_cpy, argn, &fsize)))
		{
			if (argc > 2)
				ft_printf("\n%s:\n", argv[argn]);
			if (ft_nm(file, arg_cpy[argn], fsize))
				return (1);
		}
		argn++;
	}
	free_sp(arg_cpy);
	return (0);
}