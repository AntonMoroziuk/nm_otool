#include "nm.h"

static void	handle_macho_64_file(void *file_start)
{
	uint32_t			ncmds;
	struct load_command	*first_cmd;

	ncmds = ((struct mach_header_64 *)file_start)->ncmds;
	first_cmd = (struct load_command *)(file_start + sizeof(struct mach_header_64));
	parse_load_commands(file_start, first_cmd, ncmds);
}

static void	handle_macho_file(void *file_start)
{
	uint32_t			ncmds;
	struct load_command	*first_cmd;

	ncmds = ((struct mach_header *)file_start)->ncmds;
	first_cmd = (struct load_command *)(file_start + sizeof(struct mach_header));
	parse_load_commands(file_start, first_cmd, ncmds);
}

static void	switch_architecture(void *file_start, const char *filename)
{
	uint32_t			magic;

	magic = *(uint32_t*)file_start;
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_macho_file(file_start);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_macho_64_file(file_start);
	else
		error_msg(filename, "The file was not recognized as a valid object file");
}

static void	map_file(int fd, const char *filename)
{
	struct stat			file_stats;
	void				*file_start;

	if (fstat(fd, &file_stats) < 0)
	{
		error_msg(filename, "Error getting file stats");
		return ;
	}
	if (!file_stats.st_size)
	{
		error_msg(filename, "The file was not recognized as a valid object file");
		return ;
	}
	if ((file_start = mmap(NULL, file_stats.st_size, PROT_READ, MAP_PRIVATE,
		fd, 0)) == MAP_FAILED)
	{
		error_msg(filename, "Failing to map file to memory");
		return ;
	}
	switch_architecture(file_start, filename);
}

int			main(int argc, char **argv)
{
	int					fd;
	int					i;

	if (argc == 1)
	{
		if ((fd = open("a.out", O_RDONLY)) < 0)
		{
			error_msg("a.out", "Error opening file");
			return (0);
		}
		map_file(fd, "a.out");
	}
	i = 0;
	while (++i < argc)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			error_msg(argv[i], "Error opening file");
		else
		{
			ft_printf("\n%s:\n", argv[i]);
			map_file(fd, argv[i]);
		}
	}
	return (0);
}