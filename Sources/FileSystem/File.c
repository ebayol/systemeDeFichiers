
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

SuperBlock* f_readSuperBlock ( FILE* ptrFile ) {

	// Place in the file:
	fseek( ptrFile, 0, SEEK_SET );

	// Make result pointer:
	SuperBlock* ptrSuperblock = sb_AllocateEmpty();

	// Read in the file:
	u_int nbLues = fread( ptrSuperblock, sizeof(SuperBlock), 1, ptrFile );
	if ( nbLues != 1 ) {
		perror("fread");
		exit(-1);
	}

	// return:
	return ptrSuperblock;
}

INode* f_readINodeAt ( FILE* ptrFile, u_int indexINode ) {

	// Place in the file:
	fseek( ptrFile, indexINode, SEEK_SET );

	// Make result pointer:
	INode* ptrINode = in_AllocateEmpty();

	// Read in the file:
	u_int nbLues = fread( ptrINode, sizeof(INode), 1, ptrFile );
	if ( nbLues != 1 ) {
		perror("fread");
		exit(-1);
	}

	// return:
	return ptrINode;
}


Block* f_readBlockAt ( FILE* ptrFile, u_int size_block, u_int index ) {

	// Place in the file:
	fseek( ptrFile, index, SEEK_SET );

	// Make result pointer:
	Block* ptrBlock = b_Allocate( size_block );

	// Read in the file:
	u_int nbLues = fread( ptrBlock, size_block, 1, ptrFile );
	if ( nbLues != 1 ) {
		perror("fread");
		exit(-1);
	}

	// return:
	return ptrBlock;
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_writeSuperblock ( FILE* ptrFile, SuperBlock* ptrSuperblock ) {

	// Place in the file:
	fseek( ptrFile, 0, SEEK_SET );

	// write in the file:
	u_int nbEcris = fwrite( ptrSuperblock, sizeof(SuperBlock), 1, ptrFile );
	if ( nbEcris != 1 ) {
		perror("fwrite");
		exit(-1);
	}
	// Return
	return ptrFile;
}


FILE* f_writeINodeAt ( FILE* ptrFile, INode* ptrINode, u_int index ) {

	// Place in the file:
	fseek( ptrFile, index, SEEK_SET );

	// write in the file:
	u_int nbEcris = fwrite( ptrINode, sizeof(INode), 1, ptrFile );
	if ( nbEcris != 1 ) {
		perror("fwrite");
		exit(-1);
	}
	// Return
	return ptrFile;
}


FILE* f_writeBlockAt ( FILE* ptrFile, Block* ptrBlock, u_int size_block, u_int index ) {

	// Place in the file:
	fseek( ptrFile, index, SEEK_SET );

	// write in the file:
	u_int nbEcris = fwrite( ptrBlock, size_block, 1, ptrFile );
	if ( nbEcris != 1 ) {
		perror("fwrite");
		exit(-1);
	}
	// Return
	return ptrFile;
}

#endif /* FILE_C */
/* #################################################################################################### */
