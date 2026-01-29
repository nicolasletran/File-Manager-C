#include <string.h>
#include "utils.h"

int parse_input(char *input, char *tokens[]) {
    int count = 0;

    char *token = strtok(input, " \n");
    while (token != NULL && count < MAX_TOKENS) {
        tokens[count++] = token;
        token = strtok(NULL, " \n");
    }

    tokens[count] = NULL;
    return count;
}
