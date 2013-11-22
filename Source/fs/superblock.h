
/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */

#ifndef SUPERBLOCK_H_
#define SUPERBLOCK_H_

// Dependances standards:
#include "../includes.h"

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct FS_SUPERBLOCK_S {

	size_t size_block;
	size_t nb_blocks;
	size_t nb_blocks_used;

	size_t size_inode;
	size_t nb_inodes;
	size_t nb_inodes_used;

	index_t free_block;
	index_t free_inodes;
}
fs_superblock_t;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

fs_superblock_t* AllocateSuperblock ( size_t nb_blocks, size_t size_blocks,
		                             size_t nb_inodes, size_t size_inode );
void             FreeSuperblock     ( fs_superblock_t* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

size_t getSizeBlock       ( fs_superblock_t* this );
size_t getNbBlocks        ( fs_superblock_t* this );
size_t getNbBlocksUsed    ( fs_superblock_t* this );
size_t getNbBlocksFree    ( fs_superblock_t* this );

index_t getFirstFreeBlock ( fs_superblock_t* this );

// I-Nodes

size_t getInodeSize       ( fs_superblock_t* this );
size_t getNbInodes        ( fs_superblock_t* this );
size_t getNbInodesUsed    ( fs_superblock_t* this );
size_t getNbInodesFree    ( fs_superblock_t* this );

index_t getFirstFreeInode ( fs_superblock_t* this );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

fs_superblock_t* setSizeBlock      ( fs_superblock_t* this, size_t size_block );
fs_superblock_t* setNbBlocks       ( fs_superblock_t* this, size_t nb_blocks );
fs_superblock_t* setNbBlocksUsed   ( fs_superblock_t* this, size_t nb_blocks_used );

fs_superblock_t* setFirstFreeBlock ( fs_superblock_t* this, index_t free_block );

// I-Nodes

fs_superblock_t* setInodeSize      ( fs_superblock_t* this, size_t size_inode );
fs_superblock_t* setNbInodes       ( fs_superblock_t* this, size_t nb_inodes );
fs_superblock_t* setNbInodesUsed   ( fs_superblock_t* this, size_t nb_inodes_used );

fs_superblock_t* setFirstFreeInode ( fs_superblock_t* this, index_t free_inodes );

#endif /* SUPERBLOCK_H_ */
/* #################################################################################################### */
