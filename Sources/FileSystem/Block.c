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

Block* b_Allocate ( u_int block_size ) {
	return (Block*) malloc( sizeof(octet_t) * block_size );
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
	if ( this == NULL )
		return -1;
	return b_getDataAt( this, 0 );
}

const octet_t* b_getData ( Block* this ) {
	if ( this == NULL )
		return NULL;
	return this;
}

octet_t b_getDataAt ( Block* this, u_int index ) {
	return this[ index ];
}

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void b_printf( Block* this, u_int index ) {
	printf( "[ %2d  Block             %10d octets ]\n", index, sizeof(this)/sizeof(octet_t) );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

Block* b_setAdressNextEmpty ( Block* this, u_int adressNextEmpty ) {
	if ( this == NULL )
		return NULL;
	b_setDataAt( this, 0, adressNextEmpty );
	return this;
}

Block* b_setDataAt ( Block* this, u_int index, octet_t value ) {
	if ( this == NULL )
		return NULL;
	this[ index ] = value;
	return this;
}

Block* b_setData ( Block* this, const octet_t* data, u_int size_block ) {
	if ( this == NULL )
		return NULL;
	// filling
	memcpy( this, data, size_block );
	return this;
}

Block* b_setDataBetween( Block* this, const octet_t* data, u_int id_begin_in_block, u_int offset ) {
	for ( u_int id = 0 ; id < offset ; ++id, ++id_begin_in_block )
		b_setDataAt( this, id_begin_in_block, data[ id ] );
	return this;
}

#endif /* FIN BLOCK_C */
/* #################################################################################################### */



