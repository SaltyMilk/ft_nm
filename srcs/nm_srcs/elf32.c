#include "nm.h"

int parse32elf(t_elf_file ef)
{
	unsigned long n_sec = ef.elf32header.e_shnum;
	unsigned char *ptr = (unsigned char *)ef.file + ef.elf32header.e_shoff;
	Elf32_Shdr sect_headers[n_sec];
	Elf32_Sym sects[n_sec];
	for (unsigned long i = 0; i < n_sec; i++)
		ft_memcpy(&sect_headers[i], ptr + (sizeof(Elf32_Shdr) * i), sizeof(Elf32_Shdr));
	for (unsigned long i = 0; i < n_sec; i++)
		ft_memcpy(&sects[i], (unsigned char *)ef.file + sect_headers[i].sh_offset, sizeof(Elf32_Sym));
	for (unsigned long i = 0; i < n_sec; i++)
	{
		int ttype = ELF32_ST_TYPE(sects[i].st_info);
		if (sect_headers[i].sh_type == SHT_SYMTAB && (ttype == STT_FUNC || ttype == STT_OBJECT || ttype == STT_NOTYPE))
			ft_printf("sym_name=%s\n", (unsigned char *)ef.file + sect_headers[sect_headers[i].sh_link].sh_offset + sects[i].st_name);
	}
	return (0);	
}