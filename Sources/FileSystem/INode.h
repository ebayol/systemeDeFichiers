
/* #################################################################################################### */
/* ###                                             INODE                                            ### */
/* #################################################################################################### */
#ifndef INODE_H_
#define INODE_H_

// Dependances standards:
#include "../Includes.h"

#define FS_INODE_UNUSED    0
#define FS_INODE_FILE      1
#define FS_INODE_DIRECTORY 2
#define FS_INODE_SYMLINK   3

#define NB_DIRECT_BLOCKS   1
#define NB_INDIRECT_BLOCKS 1

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct {
	int type;
	size nb_links;
	size file_size;

	adress directBlocksAdresses   [ NB_DIRECT_BLOCKS ];
	adress IndirectBlocksAdresses [ NB_INDIRECT_BLOCKS ];
}
INode;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

INode* in_AllocateEmpty ( void );
INode* in_Allocate      ( adress type, adress nb_links, adress file_size, adress* indexFreeBlocks );

INode* in_Free ( INode* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

int    in_getType     ( INode* this );
adress in_getNbLinks  ( INode* this );
adress in_getFileSize ( INode* this );

const adress* in_getDirectBlocksAdresses ( INode* this );
adress        in_getDirectBlockAdressAt  ( INode* this, adress index );

const adress* in_getIndirectBlocksAdresses ( INode* this );
adress        in_getIndirectBlocksAdressAt ( INode* this, adress index );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

INode* in_setType     ( INode* this, adress type );
INode* in_setNbLinks  ( INode* this, adress nb_links );
INode* in_setFileSize ( INode* this, adress file_size );

INode* in_setDirectBlockAdressAt  ( INode* this, adress index, adress indexDirectBlock );
INode* in_setDirectBlocksAdresses ( INode* this, adress* indexDirectBlocks );

INode* in_setIndirectBlockAdressAt  ( INode* this, adress index, adress indexIndirectBlock  );
INode* in_setIndirectBlocksAdresses ( INode* this, adress* indexIndirectBlocks );

#endif /* FIN INODE_H_ */
/* #################################################################################################### */
