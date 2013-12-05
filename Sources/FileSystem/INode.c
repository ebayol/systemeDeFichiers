

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

	// Adresses:
	in_setDirectBlocksAdressAt ( this, 0, 0 );
	in_setIndirectBlocksAdressAt ( this, 0, 0 );

	//Return pointer:
	return this;
}

INode* in_Allocate ( u_int type, u_int nb_links, u_int file_size, u_int* indexFreeBlocks ) {

	// Make the pointer:
	INode* this = (INode*) malloc( sizeof( INode ) );

	// Fill fields:
	in_setType     ( this, type );
	in_setNbLinks  ( this, nb_links );
	in_setFileSize ( this, file_size );

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

u_int in_getNbLinks ( INode* this ) {
	return this->nb_links;
}

u_int in_getFileSize ( INode* this ) {
	return this->file_size;
}

u_int in_getAdressNextEmpty( INode* this ) {
	return in_getDirectBlockAdressAt( this, 0 );
}

const u_int* in_getDirectBlocksAdresses ( INode* this ) {
	return this->directBlocksAdresses;
}

u_int in_getDirectBlockAdressAt ( INode* this, u_int index ) {
	return in_getDirectBlocksAdresses( this )[ index ];
}

const u_int* in_getIndirectBlocksAdresses ( INode* this ) {
	return this->IndirectBlocksAdresses;
}

u_int in_getIndirectBlocksAdressAt ( INode* this, u_int index ) {
	return in_getIndirectBlocksAdresses( this )[ index ];
}

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void in_printf( INode* this, u_int index ) {
	printf( "[ %3d  INode             %10d octets ]\n", index, sizeof( INode ) / sizeof( octet_t ) );
	printf( "[         Type:              %10d    ]\n", in_getType( this ) );
	printf( "[         Number of links:   %10d    ]\n", in_getNbLinks( this ) );
	printf( "[         File size:         %10d o  ]\n", in_getFileSize( this ) / sizeof( octet_t ) );
	printf( "[         Direct  Block At:  %10d    ]\n", in_getDirectBlockAdressAt( this, 0 ) );
	printf( "[         Inirect Block At:  %10d    ]\n", in_getIndirectBlocksAdressAt( this, 0 ) );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

INode* in_setType ( INode* this,u_int type ) {
	this->type = type;
	return this;
}

INode* in_setNbLinks ( INode* this,u_int nb_links ) {
	this->nb_links = nb_links;
	return this;
}

INode* in_setFileSize ( INode* this,u_int file_size ) {
	this->file_size = file_size;
	return this;
}

INode* in_setAdressNextEmpty( INode* this, u_int adress ) {
	return in_setDirectBlocksAdressAt( this, 0, adress );
}

INode* in_setDirectBlocksAdressAt ( INode* this, u_int index, u_int indexDirectBlock ) {
	this->directBlocksAdresses[ index ] = indexDirectBlock;
	return this;
}

INode* in_setDirectBlocksAdresses ( INode* this, u_int* indexDirectBlocks ) {
	for ( u_int index = 0 ; index < NB_DIRECT_BLOCKS ; ++index ) {
		in_setDirectBlocksAdressAt( this, index, indexDirectBlocks[ index ] );
	}
	return this;
}

INode* in_setIndirectBlocksAdressAt ( INode* this, u_int index, u_int indexIndirectBlock  ) {
	this->IndirectBlocksAdresses[ index ] = indexIndirectBlock;
	return this;
}

INode* in_setIndirectBlocksAdresses ( INode* this, u_int* indexIndirectBlocks ) {
	for ( u_int index = 0 ; index < NB_INDIRECT_BLOCKS ; ++index ) {
		in_setIndirectBlocksAdressAt( this, index, indexIndirectBlocks[ index ] );
	}
	return this;
}

#endif /* FIN INODE_C_ */
/* #################################################################################################### */
