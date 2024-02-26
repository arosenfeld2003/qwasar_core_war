#include <stdio.h>
#include <stdint.h>

uint8_t live[] = {0x01, 0x00, 0x00, 0x00, 0x01}; // Example: live instruction with ID 1
uint8_t ld[] = {};

int create_mock_champion(uint8_t instruction) {
    FILE *fp = fopen("mock_champion.cor", "wb");
    if (!fp) {
        perror("Cannot open file");
        return 1;
    }

    fwrite(instruction, sizeof(instruction), 1, fp);
    fclose(fp);

    printf("Mock champion file created.\n");
    return 0;
}
