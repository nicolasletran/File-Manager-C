#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "file_ops.h"
#include <time.h> 
#ifdef _WIN32
#include <direct.h> // for _mkdir
#endif


/* Optional colors */
#define BLUE  "\033[1;34m"
#define RESET "\033[0m"

void list_files_long(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("ls -l");
        return;
    }

    struct dirent *entry;
    struct stat st;
    char perms[11];
    char timebuf[64];

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &st) == -1) {
            perror("stat");
            continue;
        }

        // File type
        perms[0] = S_ISDIR(st.st_mode) ? 'd' : '-';

        // Owner permissions
        perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
        perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
        perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';

        // Group permissions
        perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
        perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
        perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';

        // Others permissions
        perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
        perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
        perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
        perms[10] = '\0';

        // Format last modified time
        struct tm *tm_info = localtime(&st.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);

        // Print: permissions, size, time, name
        if (S_ISDIR(st.st_mode)) {
            printf("%s %6lld %s %s%s%s\n",
                perms,
                (long long)st.st_size,
                timebuf,
                BLUE,       // start color
                entry->d_name,
                RESET       // reset color
            );
        } else {
            printf("%s %6lld %s %s\n",
                perms,
                (long long)st.st_size,
                timebuf,
                entry->d_name
            );
        }
    }

    closedir(dir);
}

/* =========================
   List files and directories
   ========================= */
void list_files(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("ls");
        return;
    }

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &st) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            printf(BLUE "[DIR]  %s" RESET "\n", entry->d_name);
        } else {
            printf("       %s\n", entry->d_name);
        }
    }

    closedir(dir);
}

/* =========================
   Create / delete files
   ========================= */
void create_file(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("touch");
        return;
    }
    fclose(fp);
}

void delete_file(const char *filename) {
    if (remove(filename) != 0) {
        perror("rm");
    }
}

/* =========================
   Create / delete directories
   ========================= */
void create_dir(const char *dirname) {
#ifdef _WIN32
    if (_mkdir(dirname) != 0) {  // Windows version
        perror("mkdir");
    }
#else
    if (mkdir(dirname, 0755) != 0) { // Linux / POSIX
        perror("mkdir");
    }
#endif
}



/* =========================
   Copy file
   ========================= */
void copy_file(const char *src, const char *dest) {
    struct stat st;

    if (stat(src, &st) == -1) {
        perror("cp");
        return;
    }

    if (S_ISDIR(st.st_mode)) {
        fprintf(stderr, "cp: '%s' is a directory\n", src);
        return;
    }

    FILE *fs = fopen(src, "rb");
    if (!fs) {
        perror("cp source");
        return;
    }

    FILE *fd = fopen(dest, "wb");
    if (!fd) {
        perror("cp dest");
        fclose(fs);
        return;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), fs)) > 0) {
        fwrite(buffer, 1, bytes, fd);
    }

    fclose(fs);
    fclose(fd);
}

/* =========================
   Move file
   ========================= */
void move_file(const char *src, const char *dest) {
    if (rename(src, dest) != 0) {
        perror("mv");
    }
}

/* =========================
   Recursive file search
   ========================= */
void find_file(const char *start_dir, const char *pattern) {
    DIR *dir = opendir(start_dir);
    if (!dir)
        return;

    struct dirent *entry;
    struct stat st;
    char path[512];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", start_dir, entry->d_name);

        if (stat(path, &st) == -1)
            continue;

        if (strstr(entry->d_name, pattern)) {
            printf("%s\n", path);
        }

        if (S_ISDIR(st.st_mode)) {
            find_file(path, pattern);
        }
    }

    closedir(dir);
}
/* =========================
   cd implementation
   ========================= */
void change_dir(const char *path) {
    if (chdir(path) != 0) {
        perror("cd");
    }
}
/* =========================
   pwd implementation
   ========================= */
void print_working_dir(void) {
    char cwd[512];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}
/* =========================
   Delete directory
   ========================= */
void delete_dir(const char *dirname) {
#ifdef _WIN32
    if (_rmdir(dirname) != 0) {  // Windows version
        perror("rmdir");
    }
#else
    if (rmdir(dirname) != 0) {   // Linux / POSIX
        perror("rmdir");
    }
#endif
}

