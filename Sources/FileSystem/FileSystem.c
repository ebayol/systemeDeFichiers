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
	fs_setCurrentDirectory( this, INDEX_INODE_ROOT );
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
	sb_setFirstFreeInode( ptrSuperblock, INDEX_INODE_ROOT );
	sb_setFirstFreeBlock( ptrSuperblock, INDEX_INODE_ROOT + nb_inodes * sizeof( INode ) );

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

u_int fs_getCurrentDirectory ( FileSystem* this ) {
	if ( this == NULL )
		return 0;
	return this->indexCurrentDirectory;
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
	return f_readBlockAt( fs_getFile( this ), fs_getSizeBlocks( this ), index );
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
	indiceInFile += INDEX_INODE_ROOT;

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

FileSystem* fs_setCurrentDirectory ( FileSystem* this, u_int indexINode ) {
	if ( this != NULL ) {
		this->indexCurrentDirectory = indexINode;
	}
	return this;
}

/* **************************************************************************************************** */
/* ***                                            MUTATORS                                          *** */
/* ***                                              FILE                                            *** */
/* **************************************************************************************************** */

FileSystem* fs_saveSuperBlock( FileSystem* this ) {
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
/* ***                                   RESERVE INODES AND BLOCKS                                  *** */
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

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* ***                                    FREE INODES AND BLOCKS                                    *** */
/* **************************************************************************************************** */

void fs_FreeInode ( FileSystem* this, INode* ptrINode, u_int indexINode ) {

	// Free direct blocks:
	for ( u_int id_block ; id_block < NB_DIRECT_BLOCKS ; ++id_block ) {
		u_int index_block = in_getDirectBlockAdressAt( ptrINode, id_block );
		if (index_block != 0)
			fs_FreeBlock ( this, fs_readBlockAt( this, index_block ), index_block );
	}
	// Free indirect Blocks:
	for ( u_int id_block ; id_block < NB_DIRECT_BLOCKS ; ++id_block ) {
		u_int index_block = in_getIndirectBlocksAdressAt( ptrINode, id_block );
		if (index_block != 0)
			fs_FreeBlock ( this, fs_readBlockAt( this, index_block ), index_block );
	}
	// Insert inode in free inodes list
	u_int adressFirstFree = fs_getFirstFreeInode( this );
	in_setAdressNextEmpty( ptrINode, adressFirstFree );
	// Save inode modifications
	fs_saveINodeAt ( this, indexINode, ptrINode );
	in_Free(ptrINode);
	// Modify superblock
	fs_setFirstFreeInode( this, indexINode );
	// Save SuperBlock
	fs_saveSuperBlock(this);
}

void fs_FreeBlock ( FileSystem* this, Block* ptrBlock, u_int indexBlock ) {
	u_int adressFirstFree = fs_getFirstFreeBlock( this );
	b_setAdressNextEmpty( ptrBlock, fs_getSizeBlocks( this ), adressFirstFree );
	fs_saveBlockAt ( this, indexBlock, ptrBlock );
	b_Free(ptrBlock);
	fs_setFirstFreeInode( this, indexBlock );
	fs_saveSuperBlock(this);
}

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* ***                                         ROOT MANAGEMENT                                      *** */
/* **************************************************************************************************** */

INode* fs_OpenRootINode( FileSystem* this, u_int* indexINode ) {
	*indexINode = INDEX_INODE_ROOT;
	return fs_readINodeAt( this, *indexINode );
}

Block* fs_OpenRootBlock( FileSystem* this, u_int* indexBlock ) {

	// open root inode:
	u_int indexINodeRoot = 0;
	INode* ptrINodeRoot = fs_OpenRootINode( this, &indexINodeRoot );

	// open it's block
	*indexBlock = in_getDirectBlockAdressAt( ptrINodeRoot, 0 );

	// close inode:
	in_Free( ptrINodeRoot );

	return fs_readBlockAt( this, *indexBlock );
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

	b_appendSubNode( ptrBlock, fs_getSizeBlocks( this ), ".", adressINodeRoot );
	b_appendSubNode( ptrBlock, fs_getSizeBlocks( this ), "..", adressINodeRoot );
	fs_saveBlockAt( this, indexBlockRoot, ptrBlock );
	fs_saveSuperBlock( this );

	return this;
}

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* ***                                        CONTENT MANAGEMENT                                      *** */
/* **************************************************************************************************** */

int fs_isContentInINode( FileSystem* this, INode* ptrINode, const char* content, Block* ptrBlockFound ) {

	char* occurence = NULL;
	Block* ptrBlock = NULL;
	int res = -1;
	ptrBlockFound = NULL;

	for ( u_int id_block = 0 ; res == -1 && id_block < NB_DIRECT_BLOCKS ; ++id_block ) {
		ptrBlock = fs_readBlockAt( this, in_getDirectBlockAdressAt( ptrINode, id_block ) );
		occurence = strstr( b_getData( ptrBlock ), content );
		b_Free( ptrBlock );
		if( occurence != NULL ) {
			res = occurence - b_getData( ptrBlock );
			ptrBlockFound = ptrBlock;
		}
		else
			b_Free( ptrBlock );
	}
	for ( u_int id_block = 0 ; res == -1 && id_block < NB_INDIRECT_BLOCKS ; ++id_block ) {
		ptrBlock = fs_readBlockAt( this, in_getIndirectBlocksAdressAt( ptrINode, id_block ) );
		occurence = strstr( b_getData( ptrBlock ), content );
		if( occurence != NULL ) {
			res = occurence - b_getData( ptrBlock );
			ptrBlockFound = ptrBlock;
		}
		else
			b_Free( ptrBlock );
	}
	return res;
}

int getIndexOfNamedContent( FileSystem* this, INode* ptrINode, const char* contentName ) {

	if ( this == NULL || ptrINode == NULL )
		return -1;

	// check if current
	Block* ptrBlock = NULL;
	int indexInBlock = fs_isContentInINode( this, ptrINode, contentName, ptrBlock );

	if ( ptrBlock != NULL ) {
		u_int indexDebut = indexInBlock + strlen( contentName ) + 2;
		const char* debutChiffre = b_getData( ptrBlock ) + indexDebut;
		char* finChiffre   = strstr( b_getData( ptrBlock ) + indexInBlock + 2, ")" ) - 1;
		u_int lenChiffre = finChiffre - debutChiffre;

		char* strChiffre = (char*) malloc( sizeof(char)*lenChiffre + 1 );
		strncpy( strChiffre, debutChiffre, lenChiffre );
		int chiffre = atoi( strChiffre );
		free( strChiffre );
		return chiffre;
	}
	return -1;
}

int getNameOfIndexedContent( FileSystem* this, INode* ptrINode, u_int indexRef, char* destName ) {

	// get index string representation:
	destName = itoa( indexRef, destName, 10 );
	// find corresponding block and index in block, in the inode
	Block* ptrBlock = NULL;
	int indexInBlock = fs_isContentInINode( this, ptrINode, destName, ptrBlock );
	// if not found:
	if ( ptrBlock == NULL ) {
		destName[0] = '\0';
		return -1;
	}

	int indexNameEnd = indexInBlock - 2;
	int indexNameBegin = indexNameEnd;
	while ( ptrBlock[indexNameBegin] != '"' ) --indexNameBegin;

	strncpy( destName, ptrBlock + indexNameBegin, indexNameEnd-indexNameBegin );
	return indexNameBegin;
}

INode* fs_FindINode( FileSystem* this, char* path, u_int* indexINode ) {

	// if path start with '/' go to root:
	if ( path[0] == '/' ) {
		*indexINode = sizeof( SuperBlock );
		return fs_FindINode( this, path+1, indexINode );
	}

	// Open current inode
	INode* ptrINodeCurrent = fs_readINodeAt( this, *indexINode );

	// check for final path
	const char* indexSlash = strstr( path, "/" );
	char* restOfPath = NULL;

	// trunc
	if ( indexSlash != NULL ) { // last iteration
		restOfPath = (char*) malloc( sizeof(char) * ( strlen( path ) - strlen( indexSlash ) ) );
		strncpy( restOfPath, indexSlash + 1, strlen( indexSlash ) - 1 );
		path[ indexSlash - path ] = '\0';
	}

	// check if current
	Block* ptrBlock = NULL;
	int indexInBlock = fs_isContentInINode( this, ptrINodeCurrent, path, ptrBlock );

	if ( ptrBlock != NULL ) {

		u_int indexDebut = indexInBlock + strlen( path ) + 2;
		const char* debutChiffre = b_getData( ptrBlock ) + indexDebut;
		char* finChiffre   = strstr( b_getData( ptrBlock ) + indexInBlock + 2, ")" ) - 1;
		u_int lenChiffre = finChiffre - debutChiffre;

		char* strChiffre = (char*) malloc( sizeof(char)*lenChiffre + 1 );
		strncpy( strChiffre, debutChiffre, lenChiffre );
		int chiffre = atoi( strChiffre );
		free( strChiffre );

		*indexINode = chiffre;
		if ( indexSlash == NULL )
			return fs_readINodeAt( this, *indexINode );
		else {
			INode* ptrINodeRes = fs_FindINode( this, restOfPath, indexINode );
			free( restOfPath );
			return ptrINodeRes;
		}
	}
	return NULL;
}

/* **************************************************************************************************** */
/* ***                                          UTILISTATION                                        *** */
/* ***                                            USER SIDE                                         *** */
/* **************************************************************************************************** */

int fs_format( const char* discName, u_int nb_blocks, u_int size_blocks, u_int nb_inodes ) {

	// creation de l'obje FileSystem:
	FileSystem* prtFileSystem = fs_AllocateNew( nb_blocks, size_blocks, nb_inodes, discName );
	// Verification:
	if ( prtFileSystem == NULL )
		return -1;

	u_int indiceInFile = 0;

	// Sauvergare du superblock:
	fs_saveSuperBlock( prtFileSystem );
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
			b_setAdressNextEmpty( ptrBlock, size_blocks, indiceInFile + size_blocks * sizeof( octet_t ) );
		else
			b_setAdressNextEmpty( ptrBlock, size_blocks, 0 );
		fs_saveBlockAt( prtFileSystem, indiceInFile, ptrBlock );
	}
	b_Free( ptrBlock );

	fs_InitRootFolder( prtFileSystem );

	return 0;
}

int fs_mount ( FileSystem* this, const char* path, u_int size_cache ) {
	this = fs_Allocate( path );
	fs_setCurrentDirectory( this, INDEX_INODE_ROOT );
	if ( this == NULL )
		return -1;
	return 0;
}

int fs_umount( FileSystem* this ) {
	return ( fs_Free( this ) == NULL ) ? -1 : 0;
}

#endif /* FIN FILE SYSTEM */
/* #################################################################################################### */
