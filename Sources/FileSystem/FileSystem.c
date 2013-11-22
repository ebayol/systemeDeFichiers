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

FileSystem* fs_Allocate ( size nb_blocks, size size_blocks,
                          size nb_inodes, size size_inode ) {

	FileSystem* ptrFileSystem = fs_AllocateEmpty();
	fs_setSuperblock( ptrFileSystem, sb_Allocate( nb_blocks, size_blocks, nb_inodes, size_inode ) );

	return ptrFileSystem;
}

void fs_Free     ( FileSystem* this ) {
	sb_Free( fs_getSuperblock( this ) );
	fs_Free( this );
	this = NULL;
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

INode* fs_getInodeAt ( FileSystem* this, adress index ) {
	return f_readINodeAt( fs_getFile(this), index );
}

Block* fs_getBlockAt ( FileSystem* this, adress index ) {
	return f_readBlockAt( fs_getFile(this), index );
}

/* **************************************************************************************************** */
/* ***                                            MUTATOR                                           *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* superblok ) {
	return this;
}

FileSystem* fs_setFile       ( FileSystem* this, FILE* ptrFile ) {
	return this;
}

FileSystem* fs_setInodeAt    ( FileSystem* this, INode* ptrInode ) {
	return this;
}

FileSystem* fs_setBlockAt    ( FileSystem* this, Block* ptrBlock ) {
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
