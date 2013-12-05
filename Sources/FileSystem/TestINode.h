#include "INode.h"
#include "File.h"

void TestINode( void )
{
	printf( "########################################\n" );
	printf( "###             TEST INODE           ###\n" );
	printf( "########################################\n\n" );

	// Creation d'un INode:
	printf( " Allocate INode:\n" );
	INode* ptrINode = in_Allocate( 1, 2, 128, NULL );
	if ( ptrINode == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Affichage:
	printf( " Show INode:\n" );
	in_printf( ptrINode, 64 );
	printf( "\tDone !\n\n" );

	// Ouverture d'un fichier
	printf( " Open File \"testINode.disk\":\n" );
	FILE* ptrFile = fopen( "testINode.disk", "w+" );
	if ( ptrFile == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Ecriture dans celui-ci:
	printf( " Write INode in file:\n" );
	f_writeINodeAt( ptrINode, ptrFile, 64 );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete INode:\n" );
	ptrINode = in_Free( ptrINode );
	if ( ptrINode != NULL ) {
		printf( "\tFail : %p !\n", ptrINode );
		return;
	}
	printf( "\tDone !\n\n" );

	// Lecture dans le fichier:
	printf( " Read INode in file:\n" );
	ptrINode = f_readINodeAt( ptrFile, 64 );
	if ( ptrINode == NULL ) {
		printf( "\tFail !\n" );
		return;
	}
	printf( "\tDone !\n\n" );

	// Affichage:
	printf( " Show INode:\n" );
	in_printf( ptrINode, 64 );
	printf( "\tDone !\n\n" );

	// Destruction du superblock:
	printf( " Delete INode:\n" );
	ptrINode = in_Free( ptrINode );
	if ( ptrINode != NULL ) {
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
