
/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */

#ifndef SUPERBLOCK_H_
#define SUPERBLOCK_H_

// Dependances standards:
#include "../Includes.h"

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct {

	size size_block;
	size nb_blocks;
	size nb_blocks_used;

	size size_inode;
	size nb_inodes;
	size nb_inodes_used;

	adress free_block;
	adress free_inodes;
}
SuperBlock;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

SuperBlock* sb_Allocate_Default ( void );
SuperBlock* sb_Allocate         ( size nb_blocks, size size_blocks,
		                          size nb_inodes, size size_inode );
void        sb_Free             ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

size sb_getSizeBlock       ( SuperBlock* this );
size sb_getNbBlocks        ( SuperBlock* this );
size sb_getNbBlocksUsed    ( SuperBlock* this );
size sb_getNbBlocksFree    ( SuperBlock* this );

adress sb_getFirstFreeBlock ( SuperBlock* this );

// I-Nodes

size sb_getInodeSize       ( SuperBlock* this );
size sb_getNbInodes        ( SuperBlock* this );
size sb_getNbInodesUsed    ( SuperBlock* this );
size sb_getNbInodesFree    ( SuperBlock* this );

adress sb_getFirstFreeInode ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

SuperBlock* sb_setSizeBlock      ( SuperBlock* this, size size_block );
SuperBlock* sb_setNbBlocks       ( SuperBlock* this, size nb_blocks );
SuperBlock* sb_setNbBlocksUsed   ( SuperBlock* this, size nb_blocks_used );

SuperBlock* sb_setFirstFreeBlock ( SuperBlock* this, adress free_block );

// I-Nodes

SuperBlock* sb_setInodeSize      ( SuperBlock* this, size size_inode );
SuperBlock* sb_setNbInodes       ( SuperBlock* this, size nb_inodes );
SuperBlock* sb_setNbInodesUsed   ( SuperBlock* this, size nb_inodes_used );

SuperBlock* sb_setFirstFreeInode ( SuperBlock* this, adress free_inodes );

#endif /* FIN SUPERBLOCK_H_ */
/* #################################################################################################### */
