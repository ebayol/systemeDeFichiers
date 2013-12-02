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

Block* b_Allocate ( uint32_t block_size ) {
	// Checking argument:
	block_size = block_size / sizeof(uint32_t);

	// Make the pointer:
	Block* this = (Block*) malloc( sizeof( Block ) );

	// Allocate date:
	this->data = (uint32_t*) calloc( sizeof(uint32_t), block_size );

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

const uint32_t* b_getData ( Block* this ) {
	return this->data;
}

uint32_t  b_getDataAt ( Block* this, u_int index ) {
	return b_getData( this )[index];
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

Block* b_setAdressNextEmpty ( Block* this, u_int adressNextEmpty ) {
	this->adressNextEmpty = adressNextEmpty;
	return this;
}

Block* b_setData ( Block* this, const uint32_t* data ) {
	for ( u_int index = 0 ; index < ( sizeof( data ) / sizeof(uint32_t) ) ; ++index )
		b_setDataAt( this, index, data[ index ] );
	return this;
}

Block* b_setDataAt ( Block* this, u_int index, uint32_t data ) {
	this->data[index] = data;
	return this;
}

#endif /* FIN BLOCK_C */
/* #################################################################################################### */



