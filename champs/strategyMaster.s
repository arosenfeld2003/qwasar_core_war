.name "StrategyMaster"
.comment "Basic champion"

live %1         ; Declare pl1 is alive
ld 34, r2       ; Load the val at address 34 into reg r2
add r1, r2, r3  ; Add the contents of reg r1, r2 and store in r3
sti r3, %:label, %2     ; Store the val in reg r3 at the addr labeled "label"

label:          ; A labeled position in the code
zjmp %;endwhile ; Jump to the 'end' label if the carry flag set
fork %:loop     ; Create a new process that starts at the 'loop' label

loop:           ; Another labeled position in the code
sub r2, r3, r4  ; Subtract the contents of reg r2 and r3 and store r4
lldi %3, %2, r5 ; Load the val at addre (PC + 3 + 2) into reg r5
aff r5          ; Output the character corresponding to the ASCII val in r5

end:            ; End of the program