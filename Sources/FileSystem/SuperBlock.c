

/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */
#ifndef SUPERBLOCK_C
#define SUPERBLOCK_C

// Dependances Internes:
#include "SuperBlock.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

SuperBlock* sb_AllocateEmpty ( void ) {

	// Make the pointer:
	SuperBlock* this = (SuperBlock*) malloc( sizeof( SuperBlock ) );

	// Fill fields about blocks:
	sb_setSizeBlocks    ( this, 0 );
	sb_setNbBlocks     ( this, 0 );
	sb_setNbBlocksUsed ( this, 0 );

	sb_setFirstFreeBlock ( this, 0 );

	// Fill fields about inodes:
	sb_setNbInodes     ( this, 0 );
	sb_setNbInodesUsed ( this, 0 );

	sb_setFirstFreeInode ( this, 0 );

	// Return this fucking pointer:
	return this;
}

SuperBlock* sb_Allocate ( u_int nb_blocks, u_int size_block, u_int nb_inodes ) {
	// Make the pointer:
	SuperBlock* this = sb_AllocateEmpty();

	// Fill fields about blocks:
	sb_setSizeBlocks    ( this, size_block );
	sb_setNbBlocks     ( this, nb_blocks );

	// Fill fields about inodes:
	sb_setNbInodes     ( this, nb_inodes );
	sb_setNbInodesUsed ( this, 0 );

	// Return pointer:
	return this;
}

SuperBlock* sb_Free ( SuperBlock* this ) {
	free ( this );
	this = NULL;
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

u_int sb_getSizeBlocks ( SuperBlock* this ) {
	return this->size_blocks;
}

u_int sb_getNbBlocks ( SuperBlock* this ) {
	return this->nb_blocks;
}

u_int sb_getNbBlocksUsed    ( SuperBlock* this ) {
	return this->nb_blocks_used;
}

u_int sb_getNbBlocksFree    ( SuperBlock* this ) {
	return sb_getNbBlocks( this ) - sb_getNbBlocksUsed( this );
}

u_int sb_getFirstFreeBlock ( SuperBlock* this ) {
	return this->free_block;
}

// I-Nodes

u_int sb_getNbInodes ( SuperBlock* this ) {
	return this->nb_inodes;
}

u_int sb_getNbInodesUsed ( SuperBlock* this ) {
	return this->nb_inodes_used;
}

u_int sb_getNbInodesFree ( SuperBlock* this ) {
	return sb_getNbInodes( this ) - sb_getNbInodesUsed( this );
}

u_int sb_getFirstFreeInode ( SuperBlock* this ) {
	return this->free_inodes;
}

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void sb_printf( SuperBlock* this ) {
	printf( "[ %2d  SuperBlock         %10d octets ]\n", 0, sizeof( SuperBlock ) / sizeof( octet_t ) );
	printf( "[         Size Blocks:    %10d o     ]\n", sb_getSizeBlocks( this ) / sizeof( octet_t ) );
	printf( "[         Nb Blocks:      %10d       ]\n", sb_getNbBlocks( this ) );
	printf( "[         Nb Blocks used: %10d       ]\n", sb_getNbBlocksUsed( this ) );
	printf( "[         Nb Blocks free: %10d       ]\n", sb_getNbBlocksFree( this ) );
	printf( "[         Nb Inodes:      %10d       ]\n", sb_getNbInodes( this ) );
	printf( "[         Nb Inodes used: %10d       ]\n", sb_getNbInodesUsed( this ) );
	printf( "[         Nb Inodes free: %10d       ]\n", sb_getNbInodesFree( this ) );
	printf( "[         Free Block at:  %10d       ]\n", sb_getFirstFreeBlock( this ) );
	printf( "[         Free INode at:  %10d       ]\n", sb_getFirstFreeInode( this ) );

}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

SuperBlock* sb_setSizeBlocks ( SuperBlock* this, u_int size_blocks ) {
	this->size_blocks = size_blocks;
	return this;
}

SuperBlock* sb_setNbBlocks ( SuperBlock* this, u_int nb_blocks ) {
	this->nb_blocks = nb_blocks;
	return this;
}

SuperBlock* sb_setNbBlocksUsed ( SuperBlock* this, u_int nb_blocks_used ) {
	this->nb_blocks_used = nb_blocks_used;
	return this;
}

SuperBlock* sb_setFirstFreeBlock ( SuperBlock* this, u_int free_block ) {
	this->free_block = free_block;
	return this;
}

// I-Nodes

SuperBlock* sb_setNbInodes ( SuperBlock* this, u_int nb_inodes ) {
	this->nb_inodes = nb_inodes;
	return this;
}

SuperBlock* sb_setNbInodesUsed ( SuperBlock* this, u_int nb_inodes_used ) {
	this->nb_inodes_used = nb_inodes_used;
	return this;
}

SuperBlock* sb_setFirstFreeInode ( SuperBlock* this, u_int free_inodes ) {
	this->free_inodes = free_inodes;
	return this;
}

#endif /* FIN SUPERBLOCK_C */
/* #################################################################################################### */

