#include "FileSystem.h"

/* #################################################################################################### */
/* ###                                          FILE SYSTEM                                         ### */
/* #################################################################################################### */
#ifndef FS_C
#define FS_C

/* DEPENDANCES INTERNES */
#include "FileSystem.h"

/* **************************************************************************************************** */
/* ***                                   CONSTRUCTOR / DESTRUCTOR                                   *** */
/* **************************************************************************************************** */

FileSystem* fs_AllocateEmpty ( void ) {
	return (FileSystem*) malloc( sizeof( FileSystem ) );
}

FileSystem* fs_Allocate ( size nb_blocks, size size_blocks, size nb_inodes, const char* diskName, bool format ) {

	// Create structure:
	FileSystem* ptrFileSystem = fs_AllocateEmpty();
	// Checking
	if ( ptrFileSystem == NULL )
		return NULL;

	// Create and set superblock:
	SuperBlock* ptrSuperblock = sb_Allocate( nb_blocks, size_blocks, nb_inodes );
	// Checking
	if ( ptrSuperblock == NULL )
		return fs_Free( ptrFileSystem );

	fs_setSuperblock( ptrFileSystem, ptrSuperblock );

	// Open file:
	FILE* ptrFile = NULL;
	// Mode
	if ( format )
		ptrFile = fopen( diskName, "w+" );
	else
		ptrFile = fopen( diskName, "r+" );
	// Checking
	if ( ptrFile == NULL )
		return fs_Free( ptrFileSystem );
	// Setting:
	return fs_setFile( ptrFileSystem, ptrFile );
}

FileSystem* fs_Free ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	sb_Free( fs_getSuperblock( this ) );
	fs_Free( this );
	this = NULL;
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperblock ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	return this->ptrSuperblock;
}

FILE* fs_getFile ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	return this->ptrFile;
}

INode* fs_getInodeAt ( FileSystem* this, adress index ) {
	if ( this == NULL )
		return NULL;
	return f_readINodeAt( fs_getFile(this), index );
}

Block* fs_getBlockAt ( FileSystem* this, adress index ) {
	if ( this == NULL )
		return NULL;
	return f_readBlockAt( fs_getFile(this), index );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* ptrSuperblock ) {
	if ( this == NULL )
		return NULL;
	this->ptrSuperblock = ptrSuperblock;
	return this;
}

FileSystem* fs_setFile ( FileSystem* this, FILE* ptrFile ) {
	if ( this == NULL )
		return NULL;
	this->ptrFile = ptrFile;
	return this;
}

FileSystem* fs_setInodeAt ( FileSystem* this, adress index, INode* ptrINode ) {
	if ( this == NULL )
		return NULL;
	f_writeINodeAt( fs_getFile( this ), index, ptrINode );
	return this;
}

FileSystem* fs_setBlockAt ( FileSystem* this, adress index, Block* ptrBlock ) {
	if ( this == NULL )
		return NULL;
	f_writeBlockAt( fs_getFile( this ), index, ptrBlock );
	return this;
}

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

int fs_format( const char *path, adress nb_blocks, adress size_block, adress nb_inodes ) {
	return 0;
}

int fs_mount ( FileSystem* fs, const char *path, size size_cache ) {
	return 0;
}

int fs_umount( FileSystem* fs ) {
	return 0;
}

#endif /* FIN FILE SYSTEM */
/* #################################################################################################### */
