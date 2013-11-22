
/* #################################################################################################### */
/* ###                                             INODE                                            ### */
/* #################################################################################################### */
#ifndef INODE_H_
#define INODE_H_

// Dependances standards:
#include "../includes.h"

#define FS_INODE_UNUSED    0
#define FS_INODE_FILE      1
#define FS_INODE_DIRECTORY 2
#define FS_INODE_SYMLINK   3

#define NB_DIRECT_BLOCKS   1

typedef struct FS_INODE_S{
	index_t type;

	index_t nb_links;
	index_t file_size;

	index_t block[NB_DIRECT_BLOCKS];
	index_t block_indirect;
}
fs_inode_t;

#endif /* FIN INODE_H_ */
/* #################################################################################################### */
