## qwasar_core_war
# Core War!
Core War is a 1984 programming game in which two or more battle programs (called "warriors" or "champions") compete for control of a virtual computer. These programs are typically written in assembly language Redcode. The game was introduced in a Scientific American article by A.K. Dewdney.

Our version consists of programs that run in a virtual machine. Each program's objective is to execute a special instruction ("live"), given each program's task orientation. These programs simultaneously execute in the virtual machine in the same memory zone, which enables them to write on one another. It's coded in C-language and consists of three parts:

## Virtual Machine</br>
The sandbox environment where the programs will run.

## Assembler</br>
It's the core of syntax and rules in order to make a valid program. It takes in the champion code and converts to binary code executable by the Virtual Machine

## Programs</br>
The programs are the code representing the actions of the champions. They are written in a simplified assembly language specific to the virtual machine

### Virtual Machine Solution
The Virtual Machine (VM) contains multiple programs. The role is to execute programs passed as parameters, generating processes. It checks that each process calls the "live" instruction every CYCLE_TO_DIE cycle. If after NBR_LIVE executions of the instuction live, several processes are still alive, CYCLE_TO_DIE is decreased by the CYCLE_DELTA units. This starts over until there are no live processes left.

#### REG_NUMBER registers of REG_SIZE byte search</br>
REG_NUMBER and REG_SIZE are defined in the op.h. A register is a memory zone that contains one value. In a real machine, it is embedded within the processor.

#### A C(Counter) </br>
This register contains the memory address in the VM of the next instruction to be coded and executed. 

#### Carry Flag</br>
It's value is '1' only if the last operation returned zero

#### Output </br>
