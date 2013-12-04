
/* #################################################################################################### */
/* ###                                           FICHIER                                            ### */
/* #################################################################################################### */
#ifndef FILE_C
#define FILE_C

// Dependances Internes:
#include "File.h"

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

FILE* f_checkFile ( FILE* ptrFile ) {
	if ( ptrFile == NULL ) {
		perror( "check file" );
		exit(-1);
	}
	return ptrFile;
}

void* f_read ( void* data, u_int size, u_int count, FILE* ptrFile ) {
	f_checkFile( ptrFile );
	if ( fread( data, size, count, ptrFile ) != count ) {
		perror("fread");
		exit(-1);
	}
	return data;
}

void* f_readAt ( void* data, u_int size, u_int count, FILE* ptrFile, u_int index ) {
	f_checkFile( ptrFile );
	f_seek     ( ptrFile, index );
	return f_read( data, size, count, ptrFile );
}

SuperBlock* f_readSuperBlock ( FILE* ptrFile ) {
	return f_readAt( sb_AllocateEmpty(), sizeof( SuperBlock ), 1, ptrFile, 0 );
}

INode* f_readINodeAt ( FILE* ptrFile, u_int index ) {
	return f_readAt( sb_AllocateEmpty(), sizeof( INode ), 1, ptrFile, index );
}

Block* f_readBlockAt ( FILE* ptrFile, u_int index, u_int size_block ) {
	return f_readAt( sb_AllocateEmpty(), size_block, 1, ptrFile, index );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_seek  ( FILE* ptrFile, u_int index ) {
	f_checkFile( ptrFile );
	if ( fseek( ptrFile, index, SEEK_SET ) == -1 ) {
		perror("fseek");
		exit(-1);
	}
	return ptrFile;
}

FILE* f_write ( void* data, u_int size, u_int count, FILE* ptrFile ) {
	f_checkFile( ptrFile );
	if ( fwrite( data, size, count, ptrFile ) != count ) {
		perror("fwrite");
		exit(-1);
	}
	return ptrFile;
}

FILE*  f_writeAt ( void* data, u_int size, u_int count, FILE* ptrFile, u_int index ) {
	f_checkFile( ptrFile );
	f_seek( ptrFile, index );
	return f_write( data, size, count, ptrFile );
}

FILE* f_writeSuperblock ( SuperBlock* ptrSuperblock, FILE* ptrFile ) {
	return f_writeAt( ptrSuperblock, sizeof( SuperBlock ), 1, ptrFile, 0 );
}


FILE* f_writeINodeAt ( INode* ptrINode, FILE* ptrFile, u_int index ) {
	return f_writeAt( ptrINode, sizeof( INode ), 1, ptrFile, index );
}


FILE* f_writeBlockAt ( Block* ptrBlock, u_int size_block, FILE* ptrFile, u_int index ) {
	return f_writeAt( ptrBlock, sizeof( Block ), 1, ptrFile, index );
}

#endif /* FILE_C */
/* #################################################################################################### */
