#ifndef NM_H
#define NM_H

# include "../libft/libft.h"
# include <elf.h>
# include "utils.h"
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ar.h>

typedef struct s_elf_file
{
	void		*file;
	char		*fname;
	Elf32_Ehdr	elf32header;
	Elf64_Ehdr	elf64header;
	int			endian;
}				t_elf_file;

typedef struct s_symbol
{
	long int	addr;
	char		symbol;
	char		*name;

}				t_symbol;

int parse32elf(t_elf_file ef);
#endif