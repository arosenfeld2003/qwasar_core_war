//#include "../../include/header.h"
//
//int main() {
//    unsigned char *vm = initialize_vm();
//
//    // CORE VM LOGIC HERE
//    for (int i = 0; i < MEM_SIZE; i++) {
//        unsigned char mnem = vm[i];
//        if (mnem == 0) continue; // skip empty cells
//        handle_mnemonic(mnem);
//    }
//
//    // free the VM
//    free_vm(vm);
//
//    return 0;
//}