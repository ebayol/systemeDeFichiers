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
	fs_setSuperBlock( this, NULL );
	fs_setFile( this, NULL );
	return this;
}

FileSystem* fs_Allocate ( const char* diskName ) {

	// Create structure:
	FileSystem* ptrFileSystem = fs_AllocateEmpty();

	// Checking
	if ( ptrFileSystem == NULL )
		return NULL;

	// open file:
	FILE* ptrFile = fopen( diskName, "r+" );
	// Checking
	if ( ptrFile == NULL )
		return fs_Free( ptrFileSystem );
	fs_setFile( ptrFileSystem, ptrFile );

	// read superblock:
	SuperBlock* ptrSuperBlock = fs_readSuperBlock( ptrFileSystem );
	if ( ptrSuperBlock == NULL )
		return fs_Free( ptrFileSystem );
	fs_setSuperBlock( ptrFileSystem, ptrSuperBlock );

	return ptrFileSystem;

}

FileSystem* fs_AllocateNew ( u_int nb_blocks, u_int size_blocks, u_int nb_inodes, const char* diskName ) {

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

	// initiate 1rst free block and inode:
	sb_setFirstFreeInode( ptrSuperblock, sizeof( SuperBlock ) );
	sb_setFirstFreeBlock( ptrSuperblock, sizeof( SuperBlock ) + nb_inodes * sizeof( INode ) );

	// write superblock
	fs_setSuperBlock( ptrFileSystem, ptrSuperblock );

	// Open file:
	FILE* ptrFile = NULL;
	// Mode
	ptrFile = fopen( diskName, "w+" );

	// Checking
	if ( ptrFile == NULL )
		return fs_Free( ptrFileSystem );

	return fs_setFile( ptrFileSystem, ptrFile );
}

FileSystem* fs_Free ( FileSystem* this ) {
	if ( this == NULL )
		return NULL;
	sb_Free( fs_getSuperBlock( this ) );
	fclose ( fs_getFile( this ) );
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

SuperBlock* fs_readSuperBlock ( FileSystem* this ) {
	if ( this == NULL || fs_getFile(this) == NULL )
		return NULL;
	return f_readSuperBlock( fs_getFile( this ) );
}

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

FileSystem* fs_setSuperBlock ( FileSystem* this, SuperBlock* ptrSuperblock ) {
	// Assigne new one :
	this->ptrSuperblock = ptrSuperblock;
	// Return fs :
	return this;
}

FileSystem* fs_setFile ( FileSystem* this, FILE* ptrFile ) {
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
	f_writeSuperblock( fs_getSuperBlock( this ), fs_getFile( this ) );
	return this;
}

FileSystem* fs_saveINodeAt ( FileSystem* this, u_int indexINode, INode* ptrInode ) {
	if ( fs_getFile(this) == NULL )
		return this;

	// Write in file:
	f_writeINodeAt( ptrInode, fs_getFile( this ), indexINode );

	// Return fs:
	return this;
}

FileSystem* fs_saveBlockAt ( FileSystem* this, u_int indexBlock, Block* ptrBlock ) {
	if ( this == NULL || fs_getFile(this) == NULL )
		return this;

	// Write in file:
	f_writeBlockAt( ptrBlock, fs_getSizeBlocks( this ), fs_getFile( this ), indexBlock );

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


INode* fs_ReserveAndReturnFirstFreeINode( FileSystem* this, u_int* ptrIndexINode ) {
	// we read the 1rst free INode adress in the superblock
	u_int adressFirstFree = fs_getFirstFreeInode( this );

	// we read the 1rst free INode
	INode* ptrINode = fs_readINodeAt( this, adressFirstFree );

	// we read in it the adress of the next empty INode
	u_int adressNextFree = in_getAdressNextEmpty( ptrINode );

	// we save this adress in the superblock
	fs_setFirstFreeInode( this, adressNextFree );

	// we return the INode
	*ptrIndexINode = adressFirstFree;
	return ptrINode;
}

Block* fs_ReserveAndReturnFirstFreeBlock( FileSystem* this, u_int* ptrIndexBlock ) {
	// we read the 1rst free Block adress in the superblock
	u_int adressFirstFree = fs_getFirstFreeBlock( this );

	// we read the 1rst free Block
	Block* ptrBlock = fs_readBlockAt( this, adressFirstFree );

	// we read in it the adress of the next empty Block
	u_int adressNextFree = b_getAdressNextEmpty( ptrBlock );

	// we save this adress in the superblock
	fs_setFirstFreeBlock( this, adressNextFree );

	// we return the Block
	*ptrIndexBlock = adressFirstFree;
	return ptrBlock;
}

INode* fs_ReserveAndReturnNode( FileSystem* this, u_int* ptrIndexInode, bool useIndirectToo ) {
	// get INode
	u_int indexINode = 0;
	INode*ptrINode = fs_ReserveAndReturnFirstFreeINode( this, &indexINode );

	// fill direct Blocks:
	for ( u_int id_block ; id_block < NB_DIRECT_BLOCKS ; ++id_block ) {
		// Get the bock:
		u_int index_block = 0;
		b_Free( fs_ReserveAndReturnFirstFreeBlock( this, &index_block ) );

		// remember it's index in the INode:
		in_setDirectBlocksAdressAt( ptrINode, id_block, index_block );
	}

	// fill indirect Blocks:
	for ( u_int id_block ; useIndirectToo && id_block < NB_DIRECT_BLOCKS ; ++id_block ) {
		// Get the bock:
		u_int index_block;
		b_Free( fs_ReserveAndReturnFirstFreeBlock( this, &index_block ) );

		// remember it's index in the INode:
		in_setIndirectBlocksAdressAt( ptrINode, id_block, index_block );
	}

	return ptrINode;
}

INode* OpenRootINode( FileSystem* this, u_int* indexINode ) {
	*indexINode = sizeof( SuperBlock );
	return fs_readINodeAt( this, sizeof( SuperBlock ) );
}

Block* OpenRootBlock( FileSystem* this, u_int* indexBlock ) {

	// open root inode:
	u_int indexINodeRoot = 0;
	INode* ptrINodeRoot = OpenRootINode( this, &indexINodeRoot );

	// open it's block
	*indexBlock = in_getDirectBlockAdressAt( ptrINodeRoot, 0 );

	// close inode:
	in_Free( ptrINodeRoot );

	return fs_readBlockAt( this, *indexBlock );
}

INode* fs_GoToFile( FileSystem* this, const char* path, u_int* indexINode ) {

	//

}

FileSystem* fs_InitRootFolder( FileSystem* this ) {

	// Get root block
	u_int indexBlockRoot = 0;
	Block* ptrBlock = fs_ReserveAndReturnFirstFreeBlock( this, &indexBlockRoot );

	// Get root INode:
	u_int adressINodeRoot = 0;
	INode* ptrINode = fs_ReserveAndReturnFirstFreeINode( this, &adressINodeRoot );

	// set root INode properties and save it:
	in_setType     ( ptrINode, FS_INODE_DIRECTORY );
	in_setNbLinks  ( ptrINode, 2 );
	in_setFileSize ( ptrINode, 0);
	in_setDirectBlocksAdressAt   ( ptrINode, 0, indexBlockRoot );
	in_setIndirectBlocksAdressAt ( ptrINode, 0, 0 );
	fs_saveINodeAt( this, adressINodeRoot, ptrINode );

	// Set root block and save it:
	char* entry = (char*) calloc( sizeof(char), 256 );
	sprintf ( entry, "(\".\",%d)(\"..\",%d)", adressINodeRoot, adressINodeRoot );
	b_setDataBetween( ptrBlock, entry, 0, strlen( entry ) );
	free( entry );

	fs_saveBlockAt( this, indexBlockRoot, ptrBlock );
	fs_saveSuperblock( this );

	return this;
}

int fs_format( const char* discName, u_int nb_blocks, u_int size_blocks, u_int nb_inodes ) {

	// creation de l'obje FileSystem:
	FileSystem* prtFileSystem = fs_AllocateNew( nb_blocks, size_blocks, nb_inodes, discName );
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
		if ( id_inode < nb_inodes - 1 )
			in_setAdressNextEmpty( ptrInode, indiceInFile + sizeof( INode ) );
		else
			in_setAdressNextEmpty( ptrInode, 0 );
		fs_saveINodeAt( prtFileSystem, indiceInFile, ptrInode );
		indiceInFile += sizeof( INode );
	}
	in_Free( ptrInode );

	// Initialisation des Blocks:
	Block* ptrBlock = b_Allocate( size_blocks );
	for ( u_int id_block = 0 ; id_block < nb_blocks ; ++id_block ) {
		if ( id_block < nb_blocks - 1 )
			b_setAdressNextEmpty( ptrBlock, indiceInFile + size_blocks * sizeof( octet_t ) );
		else
			b_setAdressNextEmpty( ptrBlock, 0 );
		fs_saveBlockAt( prtFileSystem, indiceInFile, ptrBlock );
	}
	b_Free( ptrBlock );

	fs_InitRootFolder( prtFileSystem );

	return 0;
}

int fs_mount ( FileSystem* this, const char* path, u_int size_cache ) {
	this = fs_Allocate( path );
	if ( this == NULL )
		return -1;
	return 0;
}

int fs_umount( FileSystem* this ) {
	return ( fs_Free( this ) == NULL ) ? -1 : 0;
}



#endif /* FIN FILE SYSTEM */
/* #################################################################################################### */
