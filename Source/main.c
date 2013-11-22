#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "commands.h"

#define MAX_LINE_SIZE  255

typedef char commandline_t[MAX_LINE_SIZE];
typedef char *argv_t[MAX_LINE_SIZE];



typedef struct
{
    const char *command;
    int nb_params;
    int nb_opt_params;
    int (*function) (fs_t *, int, char **);
} command;


command table[] =
{
    {"help", 0, 0, do_help},
    {"open", 2, 2, do_open},
    {"close", 1, 1, do_close},

    {"read", 2, 2, do_read},
    {"write", 2, -1, do_write},
    {"lseek", 3, 3, do_lseek},
    {"flush", 1, 1, do_flush},

    {"stat", 1, 1, do_stat},

    {"creat", 1, 1, do_creat},
    {"link", 2, 3, do_link},
    {"unlink", 1, 2, do_unlink},

    {"move", 2, 2, do_move},

    {"mkdir", 1, 1, do_mkdir},
    {"rmdir", 1, 1, do_rmdir},

    {"cd", 1, 1, do_cd},
    {"pwd", 0, 0, do_pwd},
    {"ls", 0, 1, do_ls},

    {"copy", 2, 3, do_copy},

    {"cat", 1, 1, do_cat},

    {"flush_cache", 0, 0, do_flush_cache},

    {"info_openfiles", 0, 0, do_info_openfiles},
    {"info_inodes", 0, 2, do_info_inodes},
    {"info_freeblocks", 0, 0, do_info_freeblocks},
    {"info_cache", 0, 0, do_info_cache}
};

void 
usage (const char *s)
{
    fprintf (stderr, "Usage: %s format <disk> <nb_b> <size_b> <nb_i>\n"
	     "       %s mount <disk> [size_cache]\n",
	     s, s);
}


void
extract_args (commandline_t cmd, int *argc, argv_t argv)
{
    int i = 0;

    for (*argc = 0;; (*argc)++)
    {
	for (; cmd[i] == ' '; i++)
	    cmd[i] = 0;

	if (cmd[i] == '\n')
	{
	    cmd[i] = 0;
	    break;
	}

	argv[*argc] = &cmd[i];

	for (; cmd[i] != ' ' && cmd[i] != '\n'; i++)
	    ;
    }
}


void 
launch_interface (fs_t * fs)
{
    commandline_t buffer;

    printf ("\n0> ");
    fflush (stdout);



    while (fgets (buffer, sizeof buffer, stdin))
    {
	int ret = 1;
	argv_t argv;
	int argc;

	extract_args (buffer, &argc, argv);

	if (argc == 0)
	{
	    fprintf (stderr, "No command given\n");
	}
	else
	{

	    if (!strcmp (argv[0], "quit"))
	    {
			printf ("\n");
			return;
	    }

	    bool found = false;
	    for (size_t i = 0; i < sizeof table / sizeof *table; i++)
	    {
			if (!strcmp (argv[0], table[i].command))
			{
				if (argc - 1 >= table[i].nb_params && (table[i].nb_opt_params < 0 || argc - 1 <= table[i].nb_opt_params))
				ret = table[i].function (fs, argc, argv);
				else
				fprintf (stderr, "Wrong number of parameters for command %s\n", table[i].command);

				found = true;
				break;
			}
	    }

	    if (!found)
		fprintf (stderr, "Unknown command\n");
	}

	printf ("%d> ", ret);
	fflush (stdout);
    }
}

int 
main (int argc, char *argv[])
{
    if (argc == 6 && !strcmp (argv[1], "format"))
    {
		index_t nb_b = atoi (argv[3]);
		index_t size_b = atoi (argv[4]);
		index_t nb_i = atoi (argv[5]);
		return fs_format (argv[2], nb_b, size_b, nb_i) == -1;
    }

    if ((argc == 3 || argc == 4) && !strcmp (argv[1], "mount"))
    {
		fs_t fs;
		size_t size_cache = 0;
		if (argc == 4)
			size_cache = atoi (argv[3]);

		if (fs_mount (&fs, argv[2], size_cache) == -1)
			return 1;

		launch_interface (&fs);
		return fs_umount (&fs) == -1;
    }

    usage (argv[0]);
    return 1;
}
