#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdlib.h>
#include "op.h"
#include "vm_state.h"

int handle_cmd (vm_state_t *vm, unsigned char cmd);
void parse_arguments(int argc, char **argv, vm_state_t *vm_state);
// more shared function prototypes

#endif /* HEADER_H */
