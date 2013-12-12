#include "Includes.h"
#include "commands.h"

int 
do_help (FileSystem * fs, int argc, char *argv[])
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
do_open ( FileSystem* fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_close ( FileSystem* fs, int argc, char *argv[] )
{
    print_args (argc, argv);
    return 0;
}

int 
do_stat ( FileSystem * fs, int argc, char *argv[] )
{
    print_args (argc, argv);
    return 0;
}


int 
do_creat (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_link (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}


int 
do_unlink (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_cd ( FileSystem* fs, int argc, char* argv[] )
{
    if ( argc != 1 )
    	printf( "Usage : \"cd <rep>\"\n" );

    INode* ptrINode = NULL;
    u_int indexCurrentDir = fs_getCurrentDirectory( fs );
    ptrINode = fs_FindINode( fs, argv[0], &indexCurrentDir );
    if ( ptrINode != NULL ) {
    	fs_setCurrentDirectory( fs, indexCurrentDir );
    	in_Free( ptrINode );
    }
    else
    	printf( "\"%s\" no such file or directory in current path\n" );
    return 0;
}

int 
do_pwd (FileSystem * fs, int argc, char *argv[])
{
	u_int repCurrent = fs_getCurrentDirectory( fs );

	char* finalPath = (char*) malloc( sizeof( char ) );
	finalPath[0] = '\0';

    while ( getIndexOfNamedContent( fs, fs_readINodeAt( fs, fs_getCurrentDirectory( fs ) ), "." )
    	 != getIndexOfNamedContent( fs, fs_readINodeAt( fs, fs_getCurrentDirectory( fs ) ), ".." )
    ){
    	u_int indexRepFils = fs_getCurrentDirectory( fs );

    	char* to = "..";
    	do_cd( fs, 1, &to );

    	char* bufferName = (char*) malloc( sizeof( char ) * 256 );
    	if( getNameOfIndexedContent( fs, fs_readINodeAt( fs, fs_getCurrentDirectory( fs ) ), bufferName ) != -1 ) {
    		bufferName = realloc( bufferName, sizeof( char ) * ( strlen( finalPath ) + strlen( bufferName ) ) );
    		strcat( bufferName, "/" );
    		strcat( bufferName, finalPath );
    		free( finalPath );
    		finalPath = bufferName;
    	}
    	else
    		free( bufferName );
    }

    printf( "/%s\n", finalPath );
    free( finalPath );
    fs_setCurrentDirectory( fs, repCurrent );
    return 0;
}

int 
do_mkdir (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_rmdir (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_read (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_write (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_lseek (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_flush (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_move (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_cat (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_openfiles (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_inodes (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_freeblocks (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_info_cache (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_flush_cache (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}

int 
do_ls (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}


int 
do_copy (FileSystem * fs, int argc, char *argv[])
{
    print_args (argc, argv);
    return 0;
}
