#include "includes.h"
#include "commands.h"

int 
do_help (fs_t * fs, int argc, char *argv[])
{
    printf (
	    "The interface supports the following commands:\n\n"
	    "quit\n"
	    "\n"
	    "open <file> <mode>\n"
	    "close <desc>\n"
	    "\n"
	    "read <desc> <nb>\n"
	    "write <desc> <string>\n"
	    "lseek <desc> <offset> <whence>\n"
	    "flush <desc>\n"
	    "\n"
	    "stat <f>\n"
	    "\n"
	    "creat <file>\n"
	    "link [-s] <f1> <f2>\n"
	    "unlink [-r] <f1>\n"
	    "\n"
	    "move <f1> <f2>\n"
	    "\n"
	    "mkdir <dir>\n"
	    "rmdir <dir>\n"
	    "\n"
	    "pwd\n"
	    "cd <dir>\n"
	    "ls [dir]\n"
	    "\n"
	    "copy [-r] <f1> <f2>\n"
	    "\n"
	    "cat <file>\n"
	    "\n"
	    "flush_cache\n"
	    "\n"
	    "info_openfiles\n"
	    "info_inodes [inode | begin end]\n"
	    "info_freeblocks\n"
	    "info_cache\n"
    );

    return 0;
}

static void 
print_args (int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++)
	puts (argv[i]);
}

int 
do_open (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_close (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_stat (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}


int 
do_creat (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_link (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}


int 
do_unlink (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_cd (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_pwd (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_mkdir (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_rmdir (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_read (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_write (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_lseek (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_flush (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_move (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_cat (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_openfiles (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_inodes (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_freeblocks (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_cache (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_flush_cache (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_ls (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}


int 
do_copy (fs_t * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}
