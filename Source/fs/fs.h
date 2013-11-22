/* #################################################################################################### */
/* ###                                          FILE SYSTEM                                         ### */
/* #################################################################################################### */
#ifndef FS_H
#define FS_H

// Dependances standards:
#include "../includes.h"

/* DEPENDANCES INTERNES */
#include "superblock.h"
#include "inode.h"

typedef struct {
	fs_superblock_t* ptrSuperblock;
	fs_inode_t* inodes;
	uint32_t* blocks; // TODO CHANGE
}
fs_t;

int fs_format( const char *path, index_t nb_blocks, index_t size_block, index_t nb_inodes );
int fs_mount ( fs_t * fs, const char *path, size_t size_cache );
int fs_umount( fs_t * fs );

#endif /* FILE SYSTEM */
/* #################################################################################################### */
