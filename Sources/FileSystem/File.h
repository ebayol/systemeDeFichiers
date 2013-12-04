
/* #################################################################################################### */
/* ###                                           FICHIER                                            ### */
/* #################################################################################################### */
#ifndef FILE_H
#define FILE_H

// Dependances standards:
#include "../Includes.h"

// Dependances Internes:
#include "SuperBlock.h"
#include "INode.h"
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

FILE* f_checkFile ( FILE* ptrFile );
void* f_read      ( void* data, u_int size, u_int count, FILE* ptrFile );
void* f_readAt    ( void* data, u_int size, u_int count, FILE* ptrFile, u_int index );

SuperBlock* f_readSuperBlock ( FILE* ptrFile );
INode*      f_readINodeAt    ( FILE* ptrFile, u_int index );
Block*      f_readBlockAt    ( FILE* ptrFile, u_int index, u_int size_block );


/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_seek    ( FILE* ptrFile, u_int index );
FILE* f_write   ( void* data, u_int size, u_int count, FILE* ptrFile );
FILE* f_writeAt ( void* data, u_int size, u_int count, FILE* ptrFile, u_int index );

FILE* f_writeSuperblock ( SuperBlock* ptrSuperblock,              FILE* ptrFile );
FILE* f_writeINodeAt    ( INode*      ptrINode,                   FILE* ptrFile, u_int index );
FILE* f_writeBlockAt    ( Block*      ptrBlock, u_int size_block, FILE* ptrFile, u_int index );

#endif /* FILE_H */
/* #################################################################################################### */
