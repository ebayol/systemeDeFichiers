

/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */
#ifndef SUPERBLOCK_C_
#define SUPERBLOCK_C_

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

SuperBlock* sb_Allocate ( size nb_blocks, size size_block, size nb_inodes ) {
	// Make the pointer:
	SuperBlock* this = sb_AllocateEmpty();

	// Fill fields about blocks:
	sb_setSizeBlocks    ( this, size_block );
	sb_setNbBlocks     ( this, nb_blocks );
	sb_setNbBlocksUsed ( this, 0 );

	sb_setFirstFreeBlock ( this, 0 );

	// Fill fields about inodes:
	sb_setNbInodes     ( this, nb_inodes );
	sb_setNbInodesUsed ( this, 0 );

	sb_setFirstFreeInode ( this, 0 );

	// Return pointer:
	return this;
}

void sb_Free ( SuperBlock* this ) {
	free ( this );
	this = NULL;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

size sb_getSizeBlocks ( SuperBlock* this ) {
	return this->size_blocks;
}

size sb_getNbBlocks ( SuperBlock* this ) {
	return this->nb_blocks;
}

size sb_getNbBlocksUsed    ( SuperBlock* this ) {
	return this->nb_blocks_used;
}

size sb_getNbBlocksFree    ( SuperBlock* this ) {
	return sb_getNbBlocks( this ) - sb_getNbBlocksUsed( this );
}

u_int sb_getFirstFreeBlock ( SuperBlock* this ) {
	return this->free_block;
}

// I-Nodes

size sb_getNbInodes ( SuperBlock* this ) {
	return this->nb_inodes;
}

size sb_getNbInodesUsed ( SuperBlock* this ) {
	return this->nb_inodes_used;
}

size sb_getNbInodesFree ( SuperBlock* this ) {
	return sb_getNbInodes( this ) - sb_getNbInodesUsed( this );
}

u_int sb_getFirstFreeInode ( SuperBlock* this ) {
	return this->free_inodes;
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

SuperBlock* sb_setSizeBlocks ( SuperBlock* this, size size_blocks ) {
	this->size_blocks = size_blocks;
	return this;
}

SuperBlock* sb_setNbBlocks ( SuperBlock* this, size nb_blocks ) {
	this->nb_blocks = nb_blocks;
	return this;
}

SuperBlock* sb_setNbBlocksUsed ( SuperBlock* this, size nb_blocks_used ) {
	this->nb_blocks_used = nb_blocks_used;
	return this;
}

SuperBlock* sb_setFirstFreeBlock ( SuperBlock* this, u_int free_block ) {
	this->free_block = free_block;
	return this;
}

// I-Nodes

SuperBlock* sb_setNbInodes ( SuperBlock* this, size nb_inodes ) {
	this->nb_inodes = nb_inodes;
	return this;
}

SuperBlock* sb_setNbInodesUsed ( SuperBlock* this, size nb_inodes_used ) {
	this->nb_inodes_used = nb_inodes_used;
	return this;
}

SuperBlock* sb_setFirstFreeInode ( SuperBlock* this, u_int free_inodes ) {
	this->free_inodes = free_inodes;
	return this;
}

#endif /* FIN SUPERBLOCK_C_ */
/* #################################################################################################### */

