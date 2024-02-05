.name "Complex"
.comment "Let's do it!"

sti r1, %:live, %1      ;store val in reg r1 in mem locn spec :live plus offset %1
sti r1, %:live2, %1     ;store val in reg r1 in mem locn spec :live2 plus offset %1
ld  %1, r3              ;loads val from mem locn spec by %1 into reg r3
ld  %33, r6             ;loads val from mem locn spec by %22 into reg r6

#While (r2 < r6)        ; comment indicaes beginning of loop while reg r2 < r6 val
forks:                  ; beginning of loop
add     r2, r3, r2  #increment  ; incre val in reg r2 by val in r3
xor     r2, %15, r4 #if (r4) {carry = 0}    ;bitwise XOR op betw val in reg r2 and %15, storing result in reg r4

live2:
        live %4         ; player %4 alive
zjmp    %:endwhile  #if (carry)     ;jumps to label :endwhile if the carry flag set
forks   %:forks         ;fork op; create new program with a counter val spec by label :forks
ld      %0, r4      #carry = 1      ; loads val from mem loc %0 into reg r4
zjmp    %:forks         ; jumps to label :forks unconditionally
#endwhile
endwhile:               ; endwhile
ld      %0, r4      #carry = 1      ; loads val from mem locn spec %0 into reg r4

live:
live %4                 ; player with the player num %4 is alive
zjmp %:live             ; jumps to label :live unconditionally