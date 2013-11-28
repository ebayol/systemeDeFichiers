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
                               size nb_inodes, size size_inodes );
FileSystem* fs_Free          ( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperblock ( FileSystem* this );
FILE*       fs_getFile       ( FileSystem* this );
INode*      fs_getInodeAt    ( FileSystem* this, u_int index );
Block*      fs_getBlockAt    ( FileSystem* this, u_int index );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* ptrSuperblok );
FileSystem* fs_setFile       ( FileSystem* this, FILE* ptrFile );
FileSystem* fs_setInodeAt    ( FileSystem* this, u_int index, INode* ptrInode );
FileSystem* fs_setBlockAt    ( FileSystem* this, u_int index, Block* ptrBlock );

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

int fs_format( const char* path, u_int nb_blocks, u_int size_blocks, u_int nb_inodes );
int fs_mount ( FileSystem* this, const char* path, size size_cache );
int fs_umount( FileSystem* this );

#endif /* FILE SYSTEM */
/* #################################################################################################### */
