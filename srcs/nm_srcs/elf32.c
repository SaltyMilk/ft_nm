#include "nm.h"
#include <stdio.h>
int parse32elf(t_elf_file ef)
{
	unsigned long n_sec = ef.elf32header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf32header.e_shoff;
	Elf32_Shdr sect_headers[n_sec];
	for (unsigned long i = 0; i < n_sec; i++)
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf32_Shdr) * i), sizeof(Elf32_Shdr));
//	for (unsigned long i = 0; i < n_sec; i++)
//		ft_memcpy(&sects[i], (unsigned char *)ef.file + sect_headers[i].sh_offset, sizeof(Elf32_Sym));
	for (unsigned long i = 0; i < n_sec; i++)
	{
		if (sect_headers[i].sh_type == SHT_SYMTAB)
		{
			unsigned int n_sym = sect_headers[i].sh_size / sizeof(Elf32_Sym);
			Elf32_Sym sects[n_sym];
			t_symbol symbols[n_sym];
			for (unsigned long x = 0; x < n_sym; x++)
				ft_memcpy(&sects[x], (unsigned char*)ef.file + sect_headers[i].sh_offset + (sizeof(Elf32_Sym) * x), sizeof(Elf32_Sym));
			for (unsigned int j = 0; j < n_sym; j++)
			{
				int ttype = ELF32_ST_TYPE(sects[j].st_info);
				if (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE)
				{
			//	printf("sym_name=%s\n", (unsigned char *)ef.file + sect_headers[sect_headers[i].sh_link].sh_offset + sects[j].st_name);
					symbols[j].name = (char *)ef.file + sect_headers[sect_headers[i].sh_link].sh_offset + sects[j].st_name;
					symbols[j].addr = sects[j].st_value;
					symbols[j].letter = get_symletter32(sects[j], sect_headers);
					if (sects[j].st_name)
					{
						if (symbols[j].letter == 'v' || symbols[j].letter == 'w' || symbols[j].letter == 'U')
							printf("%8c %c %s\n", ' ', symbols[j].letter, symbols[j].name);
						else
							printf("%08lx %c %s\n", symbols[j].addr, symbols[j].letter, symbols[j].name);
					}
				}
			}

		}
	}
	return (0);	
}