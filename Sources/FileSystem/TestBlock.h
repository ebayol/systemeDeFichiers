#include "Block.h"
#include "File.h"

void TestBlock( void )
{
	printf( "########################################\n" );
	printf( "###             TEST BLOCK           ###\n" );
	printf( "########################################\n\n" );

	int sizeBlock = 128;
	Block* this = b_Allocate( sizeBlock );
	b_printf( this, 48 );
	b_setAdressNextEmpty( this, sizeBlock, 666 );
	b_printf( this, 48 );
	b_clear( this, sizeBlock );
	b_appendSubNode( this, sizeBlock, "foler_0", 404 );
	b_appendSubNode( this, sizeBlock, "foler_0", 898 );
	b_printf( this, 48 );
	b_Free( this );

	printf( "########################################\n" );
	printf( "###          FIN TEST BLOCK          ###\n" );
	printf( "########################################\n\n" );
}
