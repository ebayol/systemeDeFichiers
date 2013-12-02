/* #################################################################################################### */
/* ###                                            BLOCKS                                            ### */
/* #################################################################################################### */
#ifndef BLOCK_C
#define BLOCK_C

// Dependances Internes:
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

Block* b_Allocate ( size block_size ) {
	// Checking argument:
	block_size = block_size / sizeof(octet_t);

	// Make the pointer:
	Block* this = (Block*) malloc( block_size * sizeof(octet_t) );

	// Return this:
	return this;
}

Block* b_Free ( Block* this ) {
	if ( this == NULL )
		return NULL;
	free( this );
	this = NULL;
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

u_int b_getAdressNextEmpty ( Block* this ) {
	return this->adressNextEmpty;
}

const octet_t* b_getData ( Block* this ) {
	return this->data;
}

uint32_t b_getDataAt ( Block* this, u_int index ) {
	return b_getData( this )[index];
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

Block* b_setAdressNextEmpty ( Block* this, u_int adressNextEmpty ) {
	if ( this == NULL )
		return NULL;
	if ( b_getData(this) != NULL )
		free( this->data );
	this->adressNextEmpty = adressNextEmpty;
	return this;
}

Block* b_setData ( Block* this, const octet_t* data, size offset ) {
	// Ckecking
	if ( this == NULL )
		return NULL;
	// Allocate data:
	if ( this->data == NULL )
		this->data = (octet_t*)malloc( offset );
	// filling
	memcpy( this->data, data, offset );
	return this;
}

#endif /* FIN BLOCK_C */
/* #################################################################################################### */



