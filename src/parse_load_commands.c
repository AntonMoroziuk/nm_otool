#include "nm.h"

static void	parse_symtab(struct symtab_command *cmd, void *file_start)
{
	void			*strtab;
	struct nlist_64	*symtab;
	uint32_t		i;

	strtab = file_start + cmd->stroff;
	symtab = (struct nlist_64 *)(file_start + cmd->symoff);
	i = -1;
	while (++i < cmd->nsyms)
	{
		ft_printf("%016llx %s\n", symtab[i].n_value,strtab + symtab[i].n_un.n_strx);
	}
}

void		parse_load_commands(void *file_start,
	struct load_command *cmd, uint32_t ncmds)
{
	while (ncmds--)
	{
		if (cmd->cmd == LC_SYMTAB)
			parse_symtab((struct symtab_command *)cmd, file_start);
		else if (cmd->cmd == LC_SEGMENT)
		{
			// handle segment
		}
		cmd = ((void*)cmd + cmd->cmdsize);
	}
}