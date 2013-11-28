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

	// Make the pointer:
	Block* this = (Block*) malloc( sizeof( Block ) );

	// Allocate date:
	this->data = (uint32_t*) calloc( sizeof(uint32_t), block_size );

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
	for ( u_int index = 0 ; index < b_getLength( this ) ; ++index )
		b_setDataAt( this, index, data[ index ] );
	return this;
}

Block* b_setDataAt ( Block* this, u_int index, uint32_t data ) {
	this->data[index] = data;
	return this;
}

#endif /* FIN BLOCK_C */
/* #################################################################################################### */



