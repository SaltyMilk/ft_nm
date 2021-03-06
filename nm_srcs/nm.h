#ifndef NM_H
#define NM_H

# include "../libft/libft.h"
# include <elf.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <ar.h>

typedef struct s_elf_file
{
	void			*file;
	char			*fname;
	Elf32_Ehdr		elf32header;
	Elf64_Ehdr		elf64header;
	int				endian;
	unsigned int	fsize;
}				t_elf_file;

typedef struct s_symbol
{
	long int	addr;
	char		letter;
	char		*name;
	char		used;
	char		valid;
}				t_symbol;

int 	parse32elf(t_elf_file ef);
int		parse64elf(t_elf_file ef);
char	get_symletter32(Elf32_Sym sym, Elf32_Shdr *shdr);
char 	get_symletter64(Elf64_Sym sym, Elf64_Shdr *shdr);
unsigned int sp_len(char **sp);
void free_sp(char **sp);
char **copy_sp(char **sp);
unsigned int smallest_len(char *s1, char *s2);
int str_is_nullterm(t_elf_file ef, unsigned int offset);

#endif