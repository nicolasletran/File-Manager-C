#include <stdio.h>
#include <string.h>
#include "file_ops.h"
#include "utils.h"

int main() {
    char input[MAX_INPUT];
    char *tokens[MAX_TOKENS];

    while (1) {
        printf("cfm> ");
        if (!fgets(input, MAX_INPUT, stdin)) break;

        // Trim trailing newline
        input[strcspn(input, "\n")] = 0;

        int count = parse_input(input, tokens);
        if (count == 0) continue;

        if (strcmp(tokens[0], "exit") == 0) {
            break;
        } 
        else if (strcmp(tokens[0], "ls") == 0) {
            list_files();
        } 
        else if (strcmp(tokens[0], "touch") == 0) {
            if (!tokens[1]) printf("Usage: touch <filename>\n");
            else create_file(tokens[1]);
        } 
        else if (strcmp(tokens[0], "rm") == 0) {
            if (!tokens[1]) printf("Usage: rm <filename>\n");
            else delete_file(tokens[1]);
        } 
        else if (strcmp(tokens[0], "mkdir") == 0) {
            if (!tokens[1]) printf("Usage: mkdir <dirname>\n");
            else create_dir(tokens[1]);
        } 
        else if (strcmp(tokens[0], "rmdir") == 0) {
            if (!tokens[1]) printf("Usage: rmdir <dirname>\n");
            else delete_dir(tokens[1]);
        } 
        else if (strcmp(tokens[0], "cp") == 0) {
            if (!tokens[1] || !tokens[2]) printf("Usage: cp <source> <dest>\n");
            else copy_file(tokens[1], tokens[2]);
        } 
        else if (strcmp(tokens[0], "mv") == 0) {
            if (!tokens[1] || !tokens[2]) printf("Usage: mv <source> <dest>\n");
            else move_file(tokens[1], tokens[2]);
        } 
        else if (strcmp(tokens[0], "find") == 0) {
            if (!tokens[1]) printf("Usage: find <pattern>\n");
            else find_file(".", tokens[1]);
        } 
        else if (strcmp(tokens[0], "cd") == 0) {
            if (!tokens[1]) printf("Usage: cd <directory>\n");
            else change_dir(tokens[1]);
        } 
        else if (strcmp(tokens[0], "pwd") == 0) {
            print_working_dir();
        } 
        else if (strcmp(tokens[0], "ls") == 0) {
            if (tokens[1] != NULL && strcmp(tokens[1], "-l") == 0)
                list_files_long();
            else
                list_files();
        }

        else {
            printf("Unknown command: %s\n", tokens[0]);
        }
    }

    return 0;
}
