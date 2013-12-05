#include "Includes.h"

#include "./FileSystem/FileSystem.h"

int main( int argc, char** argv )
{
	fs_format( "testDisk.disk", 200000, 4096, 25000 );

}

