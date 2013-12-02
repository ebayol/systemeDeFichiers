
/* #################################################################################################### */
/* ###                                           FICHIER                                            ### */
/* #################################################################################################### */
#ifndef FICHIER_H_
#define FICHIER_H_

// Dependances standards:
#include "../Includes.h"

// Dependances Internes:
#include "FileSystem.h"
#include "SuperBlock.h"
#include "INode.h"
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

FileSystem* f_readFileSystem      ( FILE* ptrFile );
SuperBlock* f_readSuperBlock      ( FILE* ptrFile );

INode*      f_readINodeAt         ( FILE* ptrFile, u_int indexINode );
Block*      f_readBlockAt         ( FILE* ptrFile, u_int index, u_int size_block );
u_int       f_readAdressNextBlock ( FILE* ptrFile, u_int index );


/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_writeSuperblock      ( FILE* ptrFile, SuperBlock* ptrSuperblock );

FILE* f_writeINodeAt         ( FILE* ptrFile, u_int indexINode, INode* ptrINode );
FILE* f_writeBlockAt         ( FILE* ptrFile, u_int indexBlock, Block* ptrBlock, u_int index );
FILE* f_xriteAdressNextBlock ( FILE* ptrFile, u_int indexBlock, u_int nextBlock );

#endif /* FICHIER_H_ */
/* #################################################################################################### */
