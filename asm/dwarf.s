; dwarf.s

ADD #4, 3   ; execution begins; add 4 to the val in reg 3
MOVE 2, @2  ; Move the val in reg 2 to the mem location spec @2
JMP -2      ; Jump back 2 instructions
DAT #0, #0  ; No operation