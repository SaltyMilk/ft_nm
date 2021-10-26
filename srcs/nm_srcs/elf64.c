#include "nm.h"
#include <stdio.h>


void print_symbols64(Elf64_Sym *sects, t_symbol *syms, unsigned int n_sym)
{
	unsigned int max = 0;
	unsigned int i;
	for (unsigned int x = 0; x < n_sym; x++)
		if (!sects[x].st_name)
			syms[x].valid = 0;
	for (unsigned int j = 0; j < n_sym; j++)
	{
		for (unsigned int x = 0; x < n_sym; x++) // First max has to be valid
		{
			if (syms[x].valid && !syms[x].used)
			{
				max = x;
				break;
			}
		}
		i = 0;
		while (i < n_sym) //Find the most alpha sorted that hasn't been used
		{
			if (!syms[i].used && syms[i].valid && ft_strncmp(syms[i].name, syms[max].name, smallest_len(syms[i].name, syms[max].name) + 1) < 0)
				max = i;
			i++;
		}
		if (!syms[max].valid || syms[max].used)//Only used or invalid symbols left
			break;
		if (syms[max].letter == 'v' || syms[max].letter == 'w' || syms[max].letter == 'U')
			ft_printf("%16c %c %s\n", ' ', syms[max].letter, syms[max].name);
		else
			ft_printf("%016l %c %s\n", syms[max].addr , syms[max].letter, syms[max].name);
		syms[max].used = 1;
		max = 0;
	}

}

int parse64elf(t_elf_file ef)
{
	unsigned long n_sec = ef.elf64header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf64header.e_shoff;
	Elf64_Shdr sect_headers[n_sec];
	unsigned int sym_count = 0;

	if ((ef.elf32header.e_shoff+ (sizeof(Elf64_Shdr) * n_sec)) > ef.fsize)//boundary check
		return (1);
	for (unsigned long i = 0; i < n_sec; i++) // Parse section headers
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf64_Shdr) * i), sizeof(Elf64_Shdr)); 
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if (sect_headers[i].sh_type == SHT_SYMTAB)//Parse symbole tables
		{
			unsigned int n_sym = sect_headers[i].sh_size / sizeof(Elf64_Sym);
			Elf64_Sym sects[n_sym];
			t_symbol symbols[n_sym];
			ft_bzero(&symbols, sizeof(t_symbol) * n_sym);
			if ((sect_headers[i].sh_offset + (sizeof(Elf64_Sym) * n_sym)) > ef.fsize)//boundary check
				return (1);
			for (unsigned long x = 0; x < n_sym; x++)
				ft_memcpy(&sects[x], (unsigned char*)ef.file + sect_headers[i].sh_offset + (sizeof(Elf64_Sym) * x), sizeof(Elf64_Sym));
			for (unsigned int j = 0; j < n_sym; j++)
			{
				int ttype = ELF64_ST_TYPE(sects[j].st_info);
				if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
				{
					sym_count++;
					if (sect_headers[sect_headers[i].sh_link].sh_offset + sects[j].st_name > ef.fsize)//boundary_check
						return (1);
					symbols[j].name = (char *)ef.file + sect_headers[sect_headers[i].sh_link].sh_offset + sects[j].st_name;
					symbols[j].addr = sects[j].st_value;
					if (!ft_strncmp(symbols[j].name, "__local_asan_preinit", ft_strlen(symbols[j].name) + 1))
						symbols[j].letter = 'D';
					else 
						symbols[j].letter = get_symletter64(sects[j], sect_headers);
					symbols[j].valid = 1;
				}
			}
			print_symbols64(sects, symbols, n_sym);
		}
	}
	if (!sym_count)
		ft_printf("nm: %s: no symbols\n", ef.fname);
	return (0);	
}