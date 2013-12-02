
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

	u_int directBlocksAdresses   [ NB_DIRECT_BLOCKS ];
	u_int IndirectBlocksAdresses [ NB_INDIRECT_BLOCKS ];
}
INode;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

INode* in_AllocateEmpty ( void );
INode* in_Allocate      ( u_int type, u_int nb_links, u_int file_size, u_int* indexFreeBlocks );

INode* in_Free ( INode* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

int   in_getType     ( INode* this );
u_int in_getNbLinks  ( INode* this );
u_int in_getFileSize ( INode* this );

const u_int* in_getDirectBlocksAdresses ( INode* this );
u_int        in_getDirectBlockAdressAt  ( INode* this, u_int index );

const u_int* in_getIndirectBlocksAdresses ( INode* this );
u_int        in_getIndirectBlocksAdressAt ( INode* this, u_int index );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

INode* in_setType     ( INode* this, u_int type );
INode* in_setNbLinks  ( INode* this, u_int nb_links );
INode* in_setFileSize ( INode* this, u_int file_size );

INode* in_setDirectBlockAdressAt  ( INode* this, u_int index, u_int indexDirectBlock );
INode* in_setDirectBlocksAdresses ( INode* this, u_int* indexDirectBlocks );

INode* in_setIndirectBlockAdressAt  ( INode* this, u_int index, u_int indexIndirectBlock  );
INode* in_setIndirectBlocksAdresses ( INode* this, u_int* indexIndirectBlocks );

#endif /* FIN INODE_H_ */
/* #################################################################################################### */
