
/* #################################################################################################### */
/* ###                                          FILE SYSTEM                                         ### */
/* #################################################################################################### */
#ifndef FS_H
#define FS_H

// Dependances standards:
#include "../Includes.h"

/* DEPENDANCES INTERNES */
#include "SuperBlock.h"
#include "INode.h"
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct {
	SuperBlock* ptrSuperblock;
	FILE* ptrFile;
}
FileSystem;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

FileSystem* fs_AllocateEmpty ( void );
FileSystem* fs_Allocate      ( size nb_blocks, size size_blocks,
                               size nb_inodes, size size_inode );
void        fs_Free          ( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperblock ( FileSystem* this );
FILE*       fs_getFile       ( FileSystem* this );
INode*      fs_getInodeAt    ( FileSystem* this, adress index );
Block*      fs_getBlockAt    ( FileSystem* this, adress index );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* superblok );
FileSystem* fs_setFile       ( FileSystem* this, FILE* ptrFile );
FileSystem* fs_setInodeAt    ( FileSystem* this, INode* ptrInode );
FileSystem* fs_setBlockAt    ( FileSystem* this, Block* ptrBlock );

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

int fs_format( const char *path, adress nb_blocks, adress size_block, adress nb_inodes );
int fs_mount ( FileSystem* fs, const char *path, size size_cache );
int fs_umount( FileSystem* fs );

#endif /* FILE SYSTEM */
/* #################################################################################################### */
