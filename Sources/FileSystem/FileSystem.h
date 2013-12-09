/* #################################################################################################### */
/* ###                                          FILE SYSTEM                                         ### */
/* #################################################################################################### */
#ifndef FS_H
#define FS_H

// Dependances standards:
#include "../Includes.h"

/* DEPENDANCES INTERNES */
#include "File.h"
#include "SuperBlock.h"
#include "INode.h"
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct {
	SuperBlock* ptrSuperblock;
	FILE* ptrFile;
	INode* ptrCurrentDirectory;
}
FileSystem;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

FileSystem* fs_AllocateEmpty ( void );
FileSystem* fs_Allocate      ( const char* diskName );
FileSystem* fs_AllocateNew   ( u_int nb_blocks, u_int size_blocks, u_int nb_inodes, const char* diskName );
FileSystem* fs_Free          ( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSORS                                          *** */
/* ***                                           FILE SYSTEM                                        *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperBlock ( FileSystem* this );
FILE*       fs_getFile       ( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSORS                                         *** */
/* ***                                              FILE                                            *** */
/* **************************************************************************************************** */

SuperBlock* fs_readSuperBlock ( FileSystem* this );
INode*      fs_readINodeAt    ( FileSystem* this, u_int index );
Block*      fs_readBlockAt    ( FileSystem* this, u_int index );

/* **************************************************************************************************** */
/* ***                                            ACCESSORS                                         *** */
/* ***                                           SUPER BLOCK                                        *** */
/* **************************************************************************************************** */

// Blocks :

u_int fs_getSizeBlocks     ( FileSystem* this );
u_int fs_getNbBlocks       ( FileSystem* this );
u_int fs_getNbBlocksUsed   ( FileSystem* this );
u_int fs_getNbBlocksFree   ( FileSystem* this );

u_int fs_getFirstFreeBlock ( FileSystem* this );

// I-Nodes

u_int fs_getNbInodes       ( FileSystem* this );
u_int fs_getNbInodesUsed   ( FileSystem* this );
u_int fs_getNbInodesFree   ( FileSystem* this );

u_int fs_getFirstFreeInode ( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void fs_printf( FileSystem* this );

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                          FILE  SYSTEM                                        *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperBlock ( FileSystem* this, SuperBlock* ptrSuperblok );
FileSystem* fs_setFile       ( FileSystem* this, FILE* ptrFile );

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                              FILE                                            *** */
/* **************************************************************************************************** */

FileSystem* fs_saveSuperblock ( FileSystem* this );
FileSystem* fs_saveINodeAt    ( FileSystem* this, u_int index, INode* ptrInode );
FileSystem* fs_saveBlockAt    ( FileSystem* this, u_int index, Block* ptrBlock );

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                           SUPER BLOCK                                        *** */
/* **************************************************************************************************** */

// Blocks :

FileSystem* fs_setSizeBlocks     ( FileSystem* this, u_int size_block );
FileSystem* fs_setNbBlocks       ( FileSystem* this, u_int nb_blocks );
FileSystem* fs_setNbBlocksUsed   ( FileSystem* this, u_int nb_blocks_used );

FileSystem* fs_setFirstFreeBlock ( FileSystem* this, u_int free_block );

// I-Nodes

FileSystem* fs_setNbInodes       ( FileSystem* this, u_int nb_inodes );
FileSystem* fs_setNbInodesUsed   ( FileSystem* this, u_int nb_inodes_used );

FileSystem* fs_setFirstFreeInode ( FileSystem* this, u_int free_inodes );

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

INode* fs_ReserveAndReturnFirstFreeINode( FileSystem* this, u_int* ptrIndexINode );
Block* fs_ReserveAndReturnFirstFreeBlock( FileSystem* this, u_int* ptrIndexBlock );
INode* fs_ReserveAndReturnNode( FileSystem* this, u_int* ptrIndexInode, bool useIndirectToo );

FileSystem* fs_InitRootFolder( FileSystem* this );

int fs_format( const char* path, u_int nb_blocks, u_int size_blocks, u_int nb_inodes );
int fs_mount ( FileSystem* this, const char* path, u_int size_cache );
int fs_umount( FileSystem* this );

#endif /* FILE SYSTEM */
/* #################################################################################################### */
