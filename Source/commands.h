#ifndef COMMANDS_H
#define COMMANDS_H

#include "./fs/fs.h"
#include "includes.h"

int do_help (fs_t * fs, int argc, char *argv[]);
int do_open (fs_t * fs, int argc, char *argv[]);
int do_close (fs_t * fs, int argc, char *argv[]);

int do_read (fs_t * fs, int argc, char *argv[]);
int do_write (fs_t * fs, int argc, char *argv[]);
int do_lseek (fs_t * fs, int argc, char *argv[]);
int do_flush (fs_t * fs, int argc, char *argv[]);

int do_stat (fs_t * fs, int argc, char *argv[]);

int do_creat (fs_t * fs, int argc, char *argv[]);
int do_link (fs_t * fs, int argc, char *argv[]);
int do_unlink (fs_t * fs, int argc, char *argv[]);

int do_move (fs_t * fs, int argc, char *argv[]);

int do_mkdir (fs_t * fs, int argc, char *argv[]);
int do_rmdir (fs_t * fs, int argc, char *argv[]);

int do_cd (fs_t * fs, int argc, char *argv[]);
int do_pwd (fs_t * fs, int argc, char *argv[]);
int do_ls (fs_t * fs, int argc, char *argv[]);

int do_copy (fs_t * fs, int argc, char *argv[]);

int do_cat (fs_t * fs, int argc, char *argv[]);

int do_flush_cache (fs_t * fs, int argc, char *argv[]);

int do_info_openfiles (fs_t * fs, int argc, char *argv[]);
int do_info_inodes (fs_t * fs, int argc, char *argv[]);
int do_info_freeblocks (fs_t * fs, int argc, char *argv[]);
int do_info_cache (fs_t * fs, int argc, char *argv[]);

#endif
