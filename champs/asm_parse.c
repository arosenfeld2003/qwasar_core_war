#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMPIONS 4
#define MAX_FILENAME_LENGTH 256

typedef struct {
    char champions[MAX_CHAMPIONS][MAX_FILENAME_LENGTH];
    int champion_count;
} assembler_state_t;

void parse_arguments(int argc, char** argv, assembler_state_t *asm_state) {
    // Initialize champ count to 0
    asm_state->champion_count = 0;

    for (int i = 1; i < argc; i++) {
        // Check if the argument ends with ".s"
        int len = strlen(argv[i]);
        if (len >= 2 && strcmp(&argv[i][len-2], ".s") == 0) {
            // Arg already has ".s" ext
            strncpy(asm_state->champions[asm_state->champion_count++], argv[i], MAX_FILENAME_LENGTH - 1);
        } else {
            // Append ".s"
            snprintf(asm_state->champions[asm_state->champion_count++], MAX_FILENAME_LENGTH, "%s.s", argv[i]);
        }
        if (asm_state->champion_count >= MAX_CHAMPIONS) {
            printf("Error: Too many champion files\n");
            exit(1);
        }
    }
}

void process_champions(assembler_state_t *asm_state) {
    // process each champion file
    for (int i = 0; i < asm_state->champion_count; i++) {
        printf("Processing champion file: %s\n", asm_state->champions[i]);
        // Add in the logic to convert to binary
    }
}

int main(int argc, char** argv) {
    // Check if at least one filename is provided
    if (argc < 2) {
        printf("Usage: ./asm file_name[.s]");
        return 1;
    }

    assembler_state_t asm_state;
    parse_arguments(argc, argv, &asm_state);
    process_champions(&asm_state);
    return 0;
}