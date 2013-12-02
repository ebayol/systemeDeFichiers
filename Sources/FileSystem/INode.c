

/* #################################################################################################### */
/* ###                                          INODE                                               ### */
/* #################################################################################################### */
#ifndef INODE_C_
#define INODE_C_

// Dependances standards:
#include "INode.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

INode* in_AllocateEmpty ( void ) {

	// Make the pointer:
	INode* this = (INode*) malloc( sizeof( INode ) );

	// Fill fields:
	in_setType     ( this, FS_INODE_UNUSED );
	in_setNbLinks  ( this, 0 );
	in_setFileSize ( this, 0 );

	//Return pointer:
	return this;
}

INode* in_Allocate ( adress type, adress nb_links, adress file_size, adress* indexFreeBlocks ) {

	// Make the pointer:
	INode* this = (INode*) malloc( sizeof( INode ) );

	// Fill fields:
	in_setType     ( this, type );
	in_setNbLinks  ( this, nb_links );
	in_setFileSize ( this, file_size );

	/*unsigned int id = 0;
	for ( adress index = 0 ; index < NB_DIRECT_BLOCKS ; ++index ) {
		in_setDirectBlockAdressAt( this, id, indexFreeBlocks[id] );
		id += index;
	}
	for ( adress index = 0 ; index < NB_INDIRECT_BLOCKS ; ++index ) {
		in_setIndirectBlockAdressAt( this, id, indexFreeBlocks[id] );
		// TODO - initialise inside the block
		id += index;
	}*/

	//Return pointer:
	return this;
}


INode* in_Free ( INode* this ) {
	if ( this == NULL )
		return NULL;
	free ( this );
	this = NULL;
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

int in_getType ( INode* this ) {
	return this->type;
}

adress in_getNbLinks ( INode* this ) {
	return this->nb_links;
}

adress in_getFileSize ( INode* this ) {
	return this->file_size;
}

const adress* in_getDirectBlocksAdresses ( INode* this ) {
	return this->directBlocksAdresses;
}

adress in_getDirectBlockAdressAt ( INode* this, adress index ) {
	return in_getDirectBlocksAdresses( this )[ index ];
}

const adress* in_getIndirectBlocksAdresses ( INode* this ) {
	return this->IndirectBlocksAdresses;
}

adress in_getIndirectBlocksAdressAt ( INode* this, adress index ) {
	return in_getIndirectBlocksAdresses( this )[ index ];
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

INode* in_setType ( INode* this,adress type ) {
	this->type = type;
	return this;
}

INode* in_setNbLinks ( INode* this,adress nb_links ) {
	this->nb_links = nb_links;
	return this;
}

INode* in_setFileSize ( INode* this,adress file_size ) {
	this->file_size = file_size;
	return this;
}

INode* in_setDirectBlockAdressAt ( INode* this, adress index, adress indexDirectBlock ) {
	this->directBlocksAdresses[ index ] = indexDirectBlock;
	return this;
}

INode* in_setDirectBlocksAdresses ( INode* this, adress* indexDirectBlocks ) {
	for ( adress index = 0 ; index < NB_DIRECT_BLOCKS ; ++index ) {
		in_setDirectBlockAdressAt( this, index, indexDirectBlocks[ index ] );
	}
	return this;
}

INode* in_setIndirectBlockAdressAt ( INode* this, adress index, adress indexIndirectBlock  ) {
	this->IndirectBlocksAdresses[ index ] = indexIndirectBlock;
	return this;
}

INode* in_setIndirectBlocksAdresses ( INode* this, adress* indexIndirectBlocks ) {
	for ( adress index = 0 ; index < NB_INDIRECT_BLOCKS ; ++index ) {
		in_setIndirectBlockAdressAt( this, index, indexIndirectBlocks[ index ] );
	}
	return this;
}

#endif /* FIN INODE_C_ */
/* #################################################################################################### */
