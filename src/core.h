#ifndef CORE_H
#define CORE_H

#define CORE_SIZE 8000 // Default

typedef enum {
    MOV, ADD, SUB, JMP, JMZ, JMN, DJN, SPL, DAT // add more?
} OpCode;

typedef struct {
    OpCode opcode;
    int operandA;
    int operandB;
    // more to be added
} Instruction;

// Define 'Core' datatype containing an array of size 'memory' with instructions
typedef struct {
    Instruction memory[CORE_SIZE];
} Core;

#endif //CORE_H