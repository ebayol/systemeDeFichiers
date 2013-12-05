#include "Block.h"
#include "File.h"

void TestBlock( void )
{
	printf( "########################################\n" );
	printf( "###             TEST BLOCK           ###\n" );
	printf( "########################################\n\n" );

	u_int block_size = 128;
	char lettre = 'x';
	u_int pos = 16;

	// Creation d'un Block:
	printf( " Allocate Block:\n" );
	Block* ptrBlock = b_Allocate( block_size );
	if ( ptrBlock == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	b_setDataAt( ptrBlock, pos, (octet_t)lettre );

	// Affichage:
	printf( " Show Block:\n" );
	b_printf( ptrBlock, 64 );
	printf( "char at %d : '%c'\n", pos, (char)b_getDataAt( ptrBlock, pos ) );
	printf( "\tDone !\n\n" );

	// Ouverture d'un fichier
	printf( " Open File \"testBlock.disk\":\n" );
	FILE* ptrFile = fopen( "testBlock.disk", "r+" );

	if ( ptrFile == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Ecriture dans celui-ci:
	printf( " Write Block in file:\n" );
	f_writeBlockAt( ptrBlock, block_size, ptrFile, 64 );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete Block:\n" );
	ptrBlock = b_Free( ptrBlock );
	if ( ptrBlock != NULL ) {
		printf( "\tFail : %p !\n", ptrBlock );
		return;
	}
	printf( "\tDone !\n\n" );

	// Lecture dans le fichier:
	printf( " Read Block in file:\n" );
	ptrBlock = f_readBlockAt( ptrFile, block_size, 64 );
	if ( ptrBlock == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Affichage:
	printf( " Show Block:\n" );
	b_printf( ptrBlock, 64 );
	printf( "char at %d : '%c'\n", pos, (char)b_getDataAt( ptrBlock, pos ) );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete Block:\n" );
	ptrBlock = b_Free( ptrBlock );
	if ( ptrBlock != NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// fermture du fichier:
	printf( " Close File:\n" );
	if ( fclose( ptrFile ) == -1 ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	printf( "########################################\n" );
	printf( "###        FIN TEST SUPERBLOCK       ###\n" );
	printf( "########################################\n\n" );
}
