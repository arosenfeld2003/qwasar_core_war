.name "Simple"
.comment "Let's get started"
l2: live:


sti r1,%:live,%1    ; stores val in reg r1 into mem loc spec by label :live plus offset %1
and r1,%0,r1        ; AND operation between val in reg r1 and 0, storing back into r1
live %1             ; player %1 is alive
zjmp %:live         ;jump to label :live if the carry flag is set