

#include "FileSystem.h"

void TestfileSystem( void ) {

	FileSystem* ptrfileSystem = fs_AllocateNew( 10, 4096, 10, "testSuperBlock.disk" );
	fs_InitRootFolder( ptrfileSystem );

	u_int indexBlock = 0;
	Block* ptrBlock = fs_OpenRootBlock( ptrfileSystem, &indexBlock );

	printf( "%d : %s\n", indexBlock, ptrBlock );

	b_Free( ptrBlock );
	fs_Free( ptrfileSystem );
}



