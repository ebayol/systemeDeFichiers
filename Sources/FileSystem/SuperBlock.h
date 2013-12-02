
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

	size size_blocks;
	size nb_blocks;
	size nb_blocks_used;

	size nb_inodes;
	size nb_inodes_used;

	u_int free_block;
	u_int free_inodes;
}
SuperBlock;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

SuperBlock* sb_Allocate_Default ( void );
SuperBlock* sb_Allocate         ( size nb_blocks, size size_blocks, size nb_inodes );
void        sb_Free             ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

size sb_getSizeBlocks      ( SuperBlock* this );
size sb_getNbBlocks        ( SuperBlock* this );
size sb_getNbBlocksUsed    ( SuperBlock* this );
size sb_getNbBlocksFree    ( SuperBlock* this );

u_int sb_getFirstFreeBlock ( SuperBlock* this );

// I-Nodes

size sb_getNbInodes        ( SuperBlock* this );
size sb_getNbInodesUsed    ( SuperBlock* this );
size sb_getNbInodesFree    ( SuperBlock* this );

u_int sb_getFirstFreeInode ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

SuperBlock* sb_setSizeBlocks      ( SuperBlock* this, size size_block );
SuperBlock* sb_setNbBlocks       ( SuperBlock* this, size nb_blocks );
SuperBlock* sb_setNbBlocksUsed   ( SuperBlock* this, size nb_blocks_used );

SuperBlock* sb_setFirstFreeBlock ( SuperBlock* this, u_int free_block );

// I-Nodes

SuperBlock* sb_setNbInodes       ( SuperBlock* this, size nb_inodes );
SuperBlock* sb_setNbInodesUsed   ( SuperBlock* this, size nb_inodes_used );

SuperBlock* sb_setFirstFreeInode ( SuperBlock* this, u_int free_inodes );

#endif /* FIN SUPERBLOCK_H_ */
/* #################################################################################################### */
