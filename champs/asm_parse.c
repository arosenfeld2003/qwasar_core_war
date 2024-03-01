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
}