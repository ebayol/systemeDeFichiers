#include "SuperBlock.h"
#include "File.h"

void TestSuperBlock( void )
{
	printf( "########################################\n" );
	printf( "###          TEST SUPERBLOCK         ###\n" );
	printf( "########################################\n\n" );

	// Creation d'un superblock:
	printf( " Allocate SuperBlock:\n" );
	SuperBlock* ptrSuperBlock = sb_Allocate( 32, 128, 8 );
	if ( ptrSuperBlock == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Affichage:
	printf( " Show SuperBlock:\n" );
	sb_printf( ptrSuperBlock );
	printf( "\tDone !\n\n" );

	// Ouverture d'un fichier
	printf( " Open File \"testSuperblock.disk\":\n" );
	FILE* ptrFile = fopen( "testSuperblock.disk", "w+" );
	if ( ptrFile == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Ecriture dans celui-ci:
	printf( " Write SuperBlock in file:\n" );
	f_writeSuperblock( ptrSuperBlock, ptrFile );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete SuperBlock:\n" );
	ptrSuperBlock = sb_Free( ptrSuperBlock );
	if ( ptrSuperBlock != NULL ) {
		printf( "\tFail : %p !\n", ptrSuperBlock );
		return;
	}
	printf( "\tDone !\n\n" );

	// Lecture dans le fichier:
	printf( " Read SuperBlock in file:\n" );
	ptrSuperBlock = f_readSuperBlock( ptrFile );
	if ( ptrSuperBlock == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Affichage:
	printf( " Show SuperBlock:\n" );
	sb_printf( ptrSuperBlock );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete SuperBlock:\n" );
	ptrSuperBlock = sb_Free( ptrSuperBlock );
	if ( ptrSuperBlock != NULL ) {
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



