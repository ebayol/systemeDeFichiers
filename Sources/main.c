#include "Includes.h"
#include "./FileSystem/FileSystem.h"

int main( int argc, char** argv )
{
	//fs_format( "testDisk.disk", 16, 16, 4 );

	FileSystem* this = fs_Allocate( 16, 16, 4, "testDisk.disk", true );
	//fs_printf( this );
	fs_Free( this );
}

