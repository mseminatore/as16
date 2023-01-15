# as16 - an assembler for the RiSC-16 Processor

This is a simple assembler for the RiSC-16 processore developed by
[Bruce Jacob](https://user.eng.umd.edu/~blj/RiSC/). This assembler is
source compatible with the original `a` assembler provided 
by Professor Jacob [here](https://user.eng.umd.edu/~blj/RiSC/a.c).

This assembler also adds several extensions in the form of 
additional pseudo-instructions. I've found these extensions to be
helpful when writing RiSC-16 assembly by hand.

## Instructions

Mnemonic | Assembly Format | Action
---------|-----------------|-------
add | add rA, rB, Rc | Add contents of regB with regC, store result in regA
addi | addi rA, rB, imm | Add contents of regB with imm, store result in regA
nand | nand rA, rB, rC | Nand contents of regB with regC, store results in regA
lui | lui rA, imm | load top 10 bits of imm in regA, bottom 6 bits are zero
sw | sw rA, rB, imm | Store 

## Pseudo-instructions

Mnemonic | Assembly Format | Action
---------|-----------------|-------
nop | nop | no operation, equvalant to add r0, r0, r0
