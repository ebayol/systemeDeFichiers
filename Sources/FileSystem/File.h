
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
INode*      f_readINodeAt         ( FILE* ptrFile, adress indexINode );
Block*      f_readBlockAt         ( FILE* ptrFile, adress size_Block, adress indexBlock );
adress      f_readAdressNextBlock ( FILE* ptrFile, adress indexBlock );


/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FILE* f_writeSuperblock      ( FILE* ptrFile, SuperBlock* ptrSuperblock );
FILE* f_writeINodeAt         ( FILE* ptrFile, adress indexINode, INode* ptrINode );
FILE* f_writeBlockAt         ( FILE* ptrFile, adress indexBlock, adress size_Block, Block* ptrBlock );
FILE* f_xriteAdressNextBlock ( FILE* ptrFile, adress indexBlock, adress nextBlock );

#endif /* FICHIER_H_ */
/* #################################################################################################### */
