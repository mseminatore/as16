# as16 - an assembler for the RiSC-16 Processor

## Instructions

Mnemonic | Assembly Format | Action
---------|-----------------|-------
add | add rA, rB, Rc | Add contents of regB with regC, store result in regA
addi | addi rA, rB, imm | Add contents of regB with imm, store result in regA

## Pseudo-instructions

Mnemonic | Assembly Format | Action
---------|-----------------|-------
nop | nop | no operation, equvalant to add r0, r0, r0
