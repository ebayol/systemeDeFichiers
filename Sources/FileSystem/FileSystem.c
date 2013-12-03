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


FileSystem* fs_Allocate ( u_int nb_blocks, u_int size_blocks, u_int nb_inodes, const char* diskName, bool format ) {

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

	return fs_setFile( ptrFileSystem, ptrFile );
}

FileSystem* fs_Free ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	sb_Free( fs_getSuperBlock( this ) );
	fs_Free( this );
	this = NULL;
	return this;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* ***                                          FILE  SYSTEM                                        *** */
/* **************************************************************************************************** */

SuperBlock* fs_getSuperBlock ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	return this->ptrSuperblock;
}

FILE* fs_getFile ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	return this->ptrFile;
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* ***                                              FILE                                            *** */
/* **************************************************************************************************** */

INode* fs_readINodeAt ( FileSystem* this, u_int index ) {
	if ( this == NULL || fs_getFile(this) == NULL )
		return NULL;
	return f_readINodeAt( fs_getFile(this), index );
}


Block* fs_readBlockAt ( FileSystem* this, u_int index ) {
	if ( this == NULL || fs_getFile( this ) == NULL )
		return NULL;
	return f_readBlockAt( fs_getFile( this ), index, fs_getSizeBlocks( this ) );
}

/* **************************************************************************************************** */
/* ***                                            ACCESSOR                                          *** */
/* ***                                          SUPER  BLOCK                                        *** */
/* **************************************************************************************************** */

// Blocks :

u_int fs_getSizeBlocks ( FileSystem* this ) {
	return sb_getSizeBlocks( fs_getSuperBlock( this) );
}

u_int fs_getNbBlocks ( FileSystem* this ) {
	return sb_getNbBlocks( fs_getSuperBlock( this) );
}

u_int fs_getNbBlocksUsed ( FileSystem* this ) {
	return sb_getNbBlocksUsed( fs_getSuperBlock( this) );
}

u_int fs_getNbBlocksFree ( FileSystem* this ) {
	return sb_getNbBlocksFree( fs_getSuperBlock( this) );
}


u_int fs_getFirstFreeBlock ( FileSystem* this ) {
	return sb_getFirstFreeBlock( fs_getSuperBlock( this) );
}


// I-Nodes

u_int fs_getNbInodes ( FileSystem* this ) {
	return sb_getNbInodes( fs_getSuperBlock( this) );
}

u_int fs_getNbInodesUsed ( FileSystem* this ) {
	return sb_getNbInodesUsed( fs_getSuperBlock( this) );
}

u_int fs_getNbInodesFree ( FileSystem* this ) {
	return sb_getNbInodesFree( fs_getSuperBlock( this) );
}


u_int fs_getFirstFreeInode ( FileSystem* this ) {
	return sb_getSizeBlocks( fs_getSuperBlock( this) );
}


/* **************************************************************************************************** */
/* ***                                           DEBBUGAGE                                          *** */
/* **************************************************************************************************** */

void fs_printf( FileSystem* this ) {

	// Checkin args
	if ( this == NULL )
		return;

	u_int indiceInFile = 0;

	// Affichage du superblock:
	sb_printf( fs_getSuperBlock( this ) );
	indiceInFile += sizeof( SuperBlock );

	// Affichage des INodes:
	INode* ptrINode = NULL;
	u_int id_inode = 0;
	while ( id_inode < fs_getNbInodes( this ) ) {
		ptrINode = fs_readINodeAt( this, indiceInFile );
		in_printf( ptrINode, indiceInFile );
		indiceInFile += sizeof( INode );
		in_Free( ptrINode );
	}

	// Affichage des Blocks:
	Block* ptrBlock = NULL;
	u_int id_block = 0;
	while ( id_block < fs_getNbBlocks( this ) ) {
		ptrBlock = fs_readBlockAt( this, indiceInFile );
		b_printf( ptrBlock, indiceInFile );
		indiceInFile += sizeof( Block ) + ( sizeof( octet_t ) * fs_getSizeBlocks( this ) );
		b_Free( ptrBlock );
	}
}

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                          FILE  SYSTEM                                        *** */
/* **************************************************************************************************** */

FileSystem* fs_setSuperblock ( FileSystem* this, SuperBlock* ptrSuperblok ) {
	// If not NULL and one different exist, free old one :
	if ( fs_getSuperBlock( this ) != NULL && fs_getSuperBlock( this ) != ptrSuperblok ) {
		// Free
		sb_Free( fs_getSuperBlock( this ) );
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

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                              FILE                                            *** */
/* **************************************************************************************************** */

FileSystem* fs_saveSuperblock( FileSystem* this ) {
	if ( fs_getFile(this) == NULL )
		return this;
	f_writeSuperblock( fs_getFile( this ), fs_getSuperBlock( this ) );
	return this;
}

FileSystem* fs_saveINodeAt ( FileSystem* this, u_int indexINode, INode* ptrInode ) {
	if ( fs_getFile(this) == NULL )
		return this;

	// Write in file:
	f_writeINodeAt( fs_getFile( this ), ptrInode, indexINode );

	// Return fs:
	return this;
}

FileSystem* fs_saveBlockAt ( FileSystem* this, u_int indexBlock, Block* ptrBlock ) {
	if ( this == NULL || fs_getFile(this) == NULL )
		return this;

	// Write in file:
	f_writeBlockAt( fs_getFile( this ), ptrBlock, fs_getSizeBlocks( this ), indexBlock );

	// Return fs:
	return this;
}

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                           SUPER BLOCK                                        *** */
/* **************************************************************************************************** */

// Blocks :

FileSystem* fs_setSizeBlocks ( FileSystem* this, u_int size_block ) {
	sb_setSizeBlocks( fs_getSuperBlock( this ), size_block );
	return this;
}

FileSystem* fs_setNbBlocks ( FileSystem* this, u_int nb_blocks ) {
	sb_setNbBlocks( fs_getSuperBlock( this ), nb_blocks );
	return this;
}

FileSystem* fs_setNbBlocksUsed ( FileSystem* this, u_int nb_blocks_used ) {
	sb_setNbBlocksUsed( fs_getSuperBlock( this ), nb_blocks_used );
	return this;
}


FileSystem* fs_setFirstFreeBlock ( FileSystem* this, u_int free_block ) {
	sb_setFirstFreeBlock( fs_getSuperBlock( this ), free_block );
	return this;
}

// I-Nodes

FileSystem* fs_setNbInodes ( FileSystem* this, u_int nb_inodes ) {
	sb_setNbInodes( fs_getSuperBlock( this ), nb_inodes );
	return this;
}

FileSystem* fs_setNbInodesUsed ( FileSystem* this, u_int nb_inodes_used ) {
	sb_setNbInodesUsed( fs_getSuperBlock( this ), nb_inodes_used );
	return this;
}

FileSystem* fs_setFirstFreeInode ( FileSystem* this, u_int free_inodes ) {
	sb_setFirstFreeInode( fs_getSuperBlock( this ), free_inodes );
	return this;
}


/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* **************************************************************************************************** */

int fs_format( const char* discName, u_int nb_blocks, u_int size_blocks, u_int nb_inodes ) {

	// creation de l'obje FileSystem:
	FileSystem* prtFileSystem = fs_Allocate( nb_blocks, size_blocks, nb_inodes, discName, true );
	// Verification:
	if ( prtFileSystem == NULL )
		return -1;

	u_int indiceInFile = 0;

	// Sauvergare du superblock:
	fs_saveSuperblock( prtFileSystem );
	indiceInFile += sizeof( SuperBlock );

	// Initialisation des INodes:
	INode* ptrInode = in_AllocateEmpty();
	for ( u_int id_inode = 0 ; id_inode < nb_inodes ; ++id_inode ) {
		fs_saveINodeAt( prtFileSystem, indiceInFile, ptrInode );
		indiceInFile += sizeof( INode );
	}
	in_Free( ptrInode );

	// Initialisation des Blocks:
	Block* ptrBlock = b_Allocate( size_blocks );
	for ( u_int id_block = 0 ; id_block < nb_blocks ; ++id_block ) {
		if ( id_block < nb_blocks - 1 )
			b_setAdressNextEmpty( ptrBlock, indiceInFile + sizeof( Block ) + size_blocks * sizeof( octet_t ) );
		else
			b_setAdressNextEmpty( ptrBlock, 0 );
		fs_saveBlockAt( prtFileSystem, indiceInFile, ptrBlock );
	}
	b_Free( ptrBlock );

	return 0;
}

int fs_mount ( FileSystem* this, const char* path, u_int size_cache ) {
	return 0;
}

int fs_umount( FileSystem* this ) {
	return fclose( fs_getFile( this ) );
}



#endif /* FIN FILE SYSTEM */
/* #################################################################################################### */
