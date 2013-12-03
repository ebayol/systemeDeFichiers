
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


SuperBlock* f_readSuperBlock      ( FILE* ptrFile );
INode*      f_readINodeAt         ( FILE* ptrFile, u_int indexINode );
Block*      f_readBlockAt         ( FILE* ptrFile, u_int index, u_int size_block );
u_int       f_readAdressNextBlock ( FILE* ptrFile, u_int index );


/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_writeSuperblock        ( FILE* ptrFile, SuperBlock* ptrSuperblock );
FILE* f_writeINodeAt           ( FILE* ptrFile, INode* ptrINode, u_int index );
FILE* f_writeBlockAt           ( FILE* ptrFile, Block* ptrBlock, u_int size_block, u_int index );
FILE* f_writeAdressNextBlockAt ( FILE* ptrFile, u_int nextBlock, u_int index );

#endif /* FILE_H */
/* #################################################################################################### */
