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
	return b_clear( (Block*) malloc( sizeof(octet_t) * block_size ), block_size );
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
	return atoi( b_getData( this ) );
}

const octet_t* b_getData ( Block* this ) {
	return this;
}

/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void b_printf( Block* this, u_int index ) {
	printf( "[ %2d  Block             %10d octets ]\n", index, sizeof(this)/sizeof(octet_t) );
	int id = 0;
	int nb = 0;
	while ( this[ id ] != '\0' ) {
		if ( nb == 0 )
			printf( "[ " );
		else if ( nb == 40 ) {
			printf( " ]\n" );
			nb = 0;
		}
		else {
			printf( "%c", this[ id ] );
			++id;
			++nb;
		}
	}
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

Block* b_clear( Block* this, u_int sizeBlock ) {
	memset( this, '\0', sizeBlock );
	return this;
}

Block* b_setAdressNextEmpty ( Block* this, u_int sizeBlock, u_int adressNextEmpty ) {
	if ( this == NULL )
		return NULL;
	b_clear( this, sizeBlock );
	itoa( this[0], adressNextEmpty, 10 );
	return this;
}

u_int b_append ( Block* this, u_int sizeBlock, const octet_t* data ) {
	// interators:
	int indiceInBlock = -1;
	char carInBlock;
	// place iterator on block end:
	do {
		++indiceInBlock;
		carInBlock = this[ indiceInBlock ];
	}
	while( carInBlock!= '\0' );
	// copie:
	int indiceInStr = 0;
	u_int nbCopy = 0;
	while ( indiceInBlock < ( (int)sizeBlock - 1 ) || data[ indiceInStr ] != '\0' ) {
		this[ indiceInBlock ] = data[ indiceInStr ];
		++indiceInBlock;
		++indiceInStr;
		++nbCopy;
	}
	// add '\0':
	this[ indiceInBlock ] = '\0';
	// return
	return nbCopy+1;
}

int b_appendSubNode( Block* this, u_int sizeBlock, const char* name, u_int indexINode ) {
	char* node = (char*) malloc( sizeof( char ) * 256 );
	sprintf( node, "(\"%s\",%d)", name, indexINode );
	int ret = -1;
	if( b_append( this, sizeBlock, node ) == strlen( node ) )
		ret = 0;
	free( node );
	return ret;
}

#endif /* FIN BLOCK_C */
/* #################################################################################################### */



