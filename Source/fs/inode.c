

/* #################################################################################################### */
/* ###                                          INODE                                               ### */
/* #################################################################################################### */

#ifndef INODE_C_
#define INODE_C_

// Dependances standards:
#include "inode.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

fs_inode_t * AllocateInode (index_t type,index_t nb_links, index_t file_size, index_t block[NB_DIRECT_BLOCKS], index_t block_indirect){
	fs_inode_t* this = (fs_inode_t*) malloc( sizeof( struct FS_INODE_S ) );

	setType(this, type);
	setNbLinks(this, nb_links);
	setFileSize(this, file_size);
	setBlock(this, block);
	setBlockIndirect(this, block_indirect);

	return this;
}


void freeInode(fs_inode_t * this){
	free ( this );
	this = NULL;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

index_t getType (fs_inode_t * this){
	return this->type;
}

index_t getNbLinks (fs_inode_t * this){
	return this->nb_links;
}

index_t getFileSize (fs_inode_t * this){
	return this->file_size;
}

const index_t* getBlock (fs_inode_t * this){
	return this->block;
}

index_t getBlockAt (fs_inode_t * this, index_t index){
	return getBlock(this)[index];
}

index_t getBlockIndirect(fs_inode_t * this){
	return this->block_indirect;
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

fs_inode_t* setType(fs_inode_t* this,index_t type){
	this->type=type;
	return this;
}

fs_inode_t* setNbLinks(fs_inode_t* this,index_t nb_links){
	this->nb_links=nb_links;
	return this;
}

fs_inode_t* setFileSize(fs_inode_t* this,index_t file_size){
	this->file_size=file_size;
	return this;
}

fs_inode_t* setBlock(fs_inode_t* this, index_t* block){
	for(index_t index=0 ; index<NB_DIRECT_BLOCKS ; index++)
		this->block=block[index];
	return this;
}

fs_inode_t* setBlockAt(fs_inode_t* this, index_t block, index_t index){
	this->block[index]=block;
	return this;
}

fs_inode_t* setBlockIndirect(fs_inode_t* this, index_t block_indirect) {
	this->block_indirect=block_indirect;
	return this;
}
 *
 *  Created on: 13 nov. 2013
 *      Author: Bayol
 */


