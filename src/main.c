#include "core.h"
#include <stdlib.h>

int main() {
    Core* core = initializeCore();

    // Game functionality: Load Warriors, Start Game, etc...

    // Free up resources
    free(core);

    return 0;
}