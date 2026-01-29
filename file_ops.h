#ifndef FILE_OPS_H
#define FILE_OPS_H

void list_files(void);
void list_files_long(void);

void create_file(const char *filename);
void delete_file(const char *filename);

void create_dir(const char *dirname);
void delete_dir(const char *dirname);

void copy_file(const char *src, const char *dest);
void move_file(const char *src, const char *dest);
void find_file(const char *start_dir, const char *pattern);

void change_dir(const char *path);
void print_working_dir(void);

#endif
