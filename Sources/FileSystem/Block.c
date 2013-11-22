

/* #################################################################################################### */
/* ###                                            BLOCKS                                            ### */
/* #################################################################################################### */
#ifndef BLOCK_C_
#define BLOCK_C_

// Dependances Internes:
#include "Block.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

Block* b_Allocate ( void ) {

	// Make the pointer:
	Block* this = (Block*) malloc( sizeof( Block ) );

	// Fill fields
	for ( adress index = 0 ; index < b_getLength( this ) ; ++index ) {
		b_setDataAt( this, index, 0 );
	}

	// Return this:
	return this;
}

void b_Free ( Block* this ) {
	free( this );
	this = NULL;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

size b_getLength ( Block* this ) {
	return BLOCK_LENGTH;
}

adress b_getAdressNextEmpty ( Block* this ) {
	return this->adressNextEmpty;
}

const uint32_t* b_getData ( Block* this ) {
	return this->data;
}

uint32_t  b_getDataAt ( Block* this, adress index ) {
	return b_getData( this )[index];
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

Block* b_setAdressNextEmpty ( Block* this, adress adressNextEmpty ) {
	this->adressNextEmpty = adressNextEmpty;
	return this;
}

Block* b_setData ( Block* this, const uint32_t* data ) {
	for ( adress index = 0 ; index < b_getLength( this ) ; ++index ) {
		b_setDataAt( this, index, data[ index ] );
	}
	return this;
}

Block* b_setDataAt ( Block* this, adress index, uint32_t data ) {
	this->data[index] = data;
	return this;
}

#endif /* FIN BLOCK_C_ */
/* #################################################################################################### */



