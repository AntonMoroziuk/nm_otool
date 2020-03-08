#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include "libft.h"
# include "error.h"

void	parse_load_commands(void *file_start,
	struct load_command *cmd, uint32_t ncmds);

#endif