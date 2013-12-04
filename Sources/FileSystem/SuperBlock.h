
/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */

#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

// Dependances standards:
#include "../Includes.h"

/* **************************************************************************************************** */
/* ***                                        TYPE DEFINITION                                       *** */
/* **************************************************************************************************** */

typedef struct {

	u_int size_blocks;
	u_int nb_blocks;
	u_int nb_blocks_used;

	u_int nb_inodes;
	u_int nb_inodes_used;

	u_int free_block;
	u_int free_inodes;
}
SuperBlock;

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

SuperBlock* sb_AllocateEmpty ( void );
SuperBlock* sb_Allocate      ( u_int nb_blocks, u_int size_blocks, u_int nb_inodes );
SuperBlock* sb_Free          ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

u_int sb_getSizeBlocks      ( SuperBlock* this );
u_int sb_getNbBlocks        ( SuperBlock* this );
u_int sb_getNbBlocksUsed    ( SuperBlock* this );
u_int sb_getNbBlocksFree    ( SuperBlock* this );

u_int sb_getFirstFreeBlock ( SuperBlock* this );

// I-Nodes

u_int sb_getNbInodes        ( SuperBlock* this );
u_int sb_getNbInodesUsed    ( SuperBlock* this );
u_int sb_getNbInodesFree    ( SuperBlock* this );

u_int sb_getFirstFreeInode ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void sb_printf ( SuperBlock* this );

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

SuperBlock* sb_setSizeBlocks     ( SuperBlock* this, u_int size_block );
SuperBlock* sb_setNbBlocks       ( SuperBlock* this, u_int nb_blocks );
SuperBlock* sb_setNbBlocksUsed   ( SuperBlock* this, u_int nb_blocks_used );

SuperBlock* sb_setFirstFreeBlock ( SuperBlock* this, u_int free_block );

// I-Nodes

SuperBlock* sb_setNbInodes       ( SuperBlock* this, u_int nb_inodes );
SuperBlock* sb_setNbInodesUsed   ( SuperBlock* this, u_int nb_inodes_used );

SuperBlock* sb_setFirstFreeInode ( SuperBlock* this, u_int free_inodes );

#endif /* FIN SUPERBLOCK_H */
/* #################################################################################################### */
