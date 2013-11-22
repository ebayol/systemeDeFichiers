#ifndef COMMANDS_H
#define COMMANDS_H

#include "./FileSystem/FileSystem.h"
#include "Includes.h"

int do_help (FileSystem * fs, int argc, char *argv[]);
int do_open (FileSystem * fs, int argc, char *argv[]);
int do_close (FileSystem * fs, int argc, char *argv[]);

int do_read (FileSystem * fs, int argc, char *argv[]);
int do_write (FileSystem * fs, int argc, char *argv[]);
int do_lseek (FileSystem * fs, int argc, char *argv[]);
int do_flush (FileSystem * fs, int argc, char *argv[]);

int do_stat (FileSystem * fs, int argc, char *argv[]);

int do_creat (FileSystem * fs, int argc, char *argv[]);
int do_link (FileSystem * fs, int argc, char *argv[]);
int do_unlink (FileSystem * fs, int argc, char *argv[]);

int do_move (FileSystem * fs, int argc, char *argv[]);

int do_mkdir (FileSystem * fs, int argc, char *argv[]);
int do_rmdir (FileSystem * fs, int argc, char *argv[]);

int do_cd (FileSystem * fs, int argc, char *argv[]);
int do_pwd (FileSystem * fs, int argc, char *argv[]);
int do_ls (FileSystem * fs, int argc, char *argv[]);

int do_copy (FileSystem * fs, int argc, char *argv[]);

int do_cat (FileSystem * fs, int argc, char *argv[]);

int do_flush_cache (FileSystem * fs, int argc, char *argv[]);

int do_info_openfiles (FileSystem * fs, int argc, char *argv[]);
int do_info_inodes (FileSystem * fs, int argc, char *argv[]);
int do_info_freeblocks (FileSystem * fs, int argc, char *argv[]);
int do_info_cache (FileSystem * fs, int argc, char *argv[]);

#endif
