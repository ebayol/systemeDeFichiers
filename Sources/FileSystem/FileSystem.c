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
	FileSystem* this = (FileSystem*) malloc( sizeof( FileSystem ) );
	fs_setSuperblock( this, NULL );
	fs_setFile( this, NULL );
	return this;
}

FileSystem* fs_Allocate ( char* discName, bool clearDisc,
						  size nb_blocks, size size_blocks,
                          size nb_inodes, size size_inodes ) {

	// Creation du pointeur:
	FileSystem* this = fs_AllocateEmpty();
	// Verification
	if ( this == NULL )
		return NULL;

	// Creation de son superblock
	SuperBlock* ptrSuperBlock = sb_Allocate( nb_blocks, size_blocks, nb_inodes, size_inodes );
	// Verification
	if ( ptrSuperBlock == NULL )
		return fs_Free( this );
	// Assignation
	fs_setSuperblock( this, ptrSuperBlock );

	// Ouveture du fichier:
	FILE* ptrDisc;
	if ( clearDisc )
		ptrDisc = fopen( discName, "w+" );
	else
		ptrDisc = fopen( discName, "r+" );
	// Verification
	if ( ptrDisc == NULL )
		return fs_Free( this );
	// Assignation
	fs_setFile( this, ptrDisc );

	// Retour:
	return this;
}

FileSystem* fs_Free ( FileSystem* this ) {
	if ( this != NULL ) {
		if ( fs_getSuperblock( this ) != NULL )
			sb_Free( fs_getSuperblock( this ) );
		if ( fs_getFile( this ) != NULL )
			fclose( fs_getFile( this ) );
		free( this );
		this = NULL;
	}
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperblock ( FileSystem* this ) {
	return this->ptrSuperblock;
}

FILE* fs_getFile ( FileSystem* this ) {
	return this->ptrFile;
}

INode* fs_getInodeAt ( FileSystem* this, u_int index ) {
	if ( fs_getFile(this) == NULL )
		return NULL;
	return f_readINodeAt( fs_getFile(this), index );
}

Block* fs_getBlockAt ( FileSystem* this, u_int index ) {
	if ( fs_getFile(this) == NULL )
		return NULL;
	return f_readBlockAt( fs_getFile(this), index );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* ptrSuperblok ) {
	// If not NULL and one different exist, free old one :
	if ( fs_getSuperblock( this ) != NULL && fs_getSuperblock( this ) != ptrSuperblok ) {
		// Free
		sb_Free( fs_getSuperblock( this ) );
		// Assigne new one :
		this->ptrSuperblock = ptrSuperblok;
		// write in file:
		f_writeSuperblock( fs_getFile( this ), ptrSuperblok );
	}
	// Return fs :
	return this;
}

FileSystem* fs_setFile ( FileSystem* this, FILE* ptrFile ) {
	// If one different is already open, close it :
	if ( fs_getFile( this ) != NULL && fs_getFile( this ) != ptrFile )
		fclose( fs_getFile( this ) );
	// Assigne new one:
	this->ptrFile = ptrFile;
	// Return fs :
	return this;
}

FileSystem* fs_setInodeAt ( FileSystem* this, u_int indexINode, INode* ptrInode ) {
	if ( fs_getFile(this) == NULL )
		return this;
	// Write in file:
	f_writeINodeAt( fs_getFile( this ), indexINode, ptrInode );
	// Return fs:
	return this;
}

FileSystem* fs_setBlockAt ( FileSystem* this, u_int indexBlock, Block* ptrBlock ) {
	if ( fs_getFile(this) == NULL )
		return this;
	// Write in file:
	f_writeBlockAt( fs_getFile( this ), indexBlock, ptrBlock );
	// Return fs:
	return this;
}

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

int fs_format( const char* discName, u_int nb_blocks, u_int size_blocks, u_int nb_inodes ) {

	FileSystem ptrFileSystem = fs_Allocate( discName, true, nb_blocks, size_blocks, nb_inodes, 32 );
	if ( ptrFileSystem == NULL )
		return -1;


	return 0;
}

int fs_mount ( FileSystem* this, const char* path, size size_cache ) {
	return 0;
}

int fs_umount( FileSystem* this ) {
	return fclose( fs_getFile( this ) );
}

#endif /* FIN FILE SYSTEM */
/* #################################################################################################### */
