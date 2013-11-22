

/* #################################################################################################### */
/* ###                                          SUPERBLOCK                                          ### */
/* #################################################################################################### */
#ifndef SUPERBLOCK_C_
#define SUPERBLOCK_C_

// Dependances standards:
#include "superblock.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

fs_superblock_t* AllocateSuperblock ( size_t nb_blocks, size_t size_block,
		                              size_t nb_inodes, size_t size_inode ) {
	// Make the pointer:
	fs_superblock_t* this = (fs_superblock_t*) malloc( sizeof( struct FS_SUPERBLOCK_S ) );

	// Fill fealds about blocks:

	setSizeBlock    ( this, size_block );
	setNbBlocks     ( this, nb_blocks );
	setNbBlocksUsed ( this, 0 );

	setFirstFreeBlock ( this, 0 );

	// Fill fealds about inodes:

	setInodeSize    ( this, size_inode );
	setNbInodes     ( this, nb_inodes );
	setNbInodesUsed ( this, 0 );

	setFirstFreeInode ( this, 0 );

	// Return pionter:
	return this;
}

void FreeSuperblock ( fs_superblock_t* this ) {
	free ( this );
	this = NULL;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

// Blocks :

size_t getSizeBlock ( fs_superblock_t* this ) {
	return this->size_block;
}

size_t getNbBlocks ( fs_superblock_t* this ) {
	return this->nb_blocks;
}

size_t getNbBlocksUsed    ( fs_superblock_t* this ) {
	return this->nb_blocks_used;
}

size_t getNbBlocksFree    ( fs_superblock_t* this ) {
	return getNbBlocks( this ) - getNbBlocksUsed( this );
}

index_t getFirstFreeBlock ( fs_superblock_t* this ) {
	return this->free_block;
}

// I-Nodes

size_t getNbInodes ( fs_superblock_t* this ) {
	return this->nb_inodes;
}

size_t getNbInodesUsed ( fs_superblock_t* this ) {
	return this->nb_inodes_used;
}

size_t getNbInodesFree ( fs_superblock_t* this ) {
	return getNbInodes( this ) - getNbInodesUsed( this );
}

index_t getFirstFreeInode ( fs_superblock_t* this ) {
	return this->free_inodes;
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

// Blocks :

fs_superblock_t* setSizeBlock ( fs_superblock_t* this, size_t size_block ) {
	this->size_block = size_block;
	return this;
}

fs_superblock_t* setNbBlocks ( fs_superblock_t* this, size_t nb_blocks ) {
	this->nb_blocks = nb_blocks;
	return this;
}

fs_superblock_t* setNbBlocksUsed ( fs_superblock_t* this, size_t nb_blocks_used ) {
	this->nb_blocks_used = nb_blocks_used;
	return this;
}

fs_superblock_t* setFirstFreeBlock ( fs_superblock_t* this, index_t free_block ) {
	this->free_block = free_block;
	return this;
}

// I-Nodes

fs_superblock_t* setInodeSize ( fs_superblock_t* this, size_t size_inode ) {
	this->size_inode = size_inode;
	return this;
}

fs_superblock_t* setNbInodes ( fs_superblock_t* this, size_t nb_inodes ) {
	this->nb_inodes = nb_inodes;
	return this;
}

fs_superblock_t* setNbInodesUsed ( fs_superblock_t* this, size_t nb_inodes_used ) {
	this->nb_inodes_used = nb_inodes_used;
	return this;
}

fs_superblock_t* setFirstFreeInode ( fs_superblock_t* this, index_t free_inodes ) {
	this->free_inodes = free_inodes;
	return this;
}

#endif /* SUPERBLOCK_C_ */
/* #################################################################################################### */

