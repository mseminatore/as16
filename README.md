# as16 - an enhanced assembler for the RiSC-16 Processor

This is a simple assembler for the RiSC-16 processor developed by
Professor [Bruce Jacob](https://user.eng.umd.edu/~blj/RiSC/). This assembler is
fully source compatible with the original `a` assembler provided 
by Professor Jacob [here](https://user.eng.umd.edu/~blj/RiSC/a.c).

I recently implemented the RiSC-16 processor in Verilog on a Basys-3 FPGA. 
As part of the design validation phase I used the assembler quite a bit to 
write test code. In doing so, I found that there were several improvements 
that I wanted to make for productivity.

Rather than modify the original assembler code, I re-implemented the assembler 
as `as16` using Yacc/Bison. The original assembler used 2 passes over the 
source code to resolve forward references. In this implementation, I use a list 
of code fixups to track locations where back-patching of forward references is 
needed. The fixup pass takes place after a single pass through the source code
is completed.

The `as16` assembler also adds several extensions in the form of 
additional pseudo-instructions. I've found these extensions to be helpful when
writing non-trivial amounts of RiSC-16 assembly by hand.

Like the original assembler the default output format is machine code in 16b hex.
In future releases I may implement direct Verilog rom file generation as well as
`a.out` object file generation and linking.

Running `as16` without any other parameters will display usage information 
including the documented command line switches.

## Assembler Source Code

The source includes a Makefile which should work on any Unix-like operating 
system. The project requires `YACC` or `Bison` to compile. For expediencey on 
machines without these tools (ahem Windows) I've included the resulting 
y.tab.c and y.tab.h files.

## Original Instructions

Mnemonic | Assembly Format | Action
---------|-----------------|-------
add | add rA, rB, Rc | Add contents of regB with regC, store result in regA
addi | addi rA, rB, imm | Add contents of regB with imm, store result in regA
nand | nand rA, rB, rC | Nand contents of regB with regC, store results in regA
lui | lui rA, imm | load top 10 bits of imm in regA, bottom 6 bits are zero
sw | sw rA, rB, imm | Store value from regA to memory. Address is regB + imm
lw | lw rA, rB, imm | Load value from memory to regA. Addresss is regB + imm
beq | beq rA, rB, imm | If contents of regA equals regB branch to address PC + 1 + imm
jalr | jalr rA, rB | Branch to address in regB and store PC + 1 in regA.

## Original Pseudo-instructions

Professor Jacob's assembler included several useful pseudo-instructions which I carried
forward. These are listed below

Mnemonic | Assembly Format | Action
---------|-----------------|-------
nop | nop | No operation, equvalant to add r0, r0, r0
halt | halt | Halt the processor, equivalent to jalr r0, r0 with non-zero imm field
lli | lli rA, imm | Load lower 6 bits of imm in regA by ORing with regA
movi | movi rA, imm | Equivalent to lui + lli of imm to regA
.fill | .fill imm | Initialize data with value imm
.space | .space imm | Zero-fill an array of size imm

## Label Extensions

As an extension to the original assembler, labels can appear on a line by themselves 
in addition to being associated with an instruction.

## Equates

When writing assembly language I've always found it helpful to use named 
constants to factor magic numbers out of assembly code. In `as16` I added the EQU
keyword for this purpose.

Mnemonic | Assembly Format | Action
---------|-----------------|-------
EQU | label EQU value | Associate the label name with the numeric constant value

## Register aliases

In writing RiSC-16 code I found that I wanted to establish an ABI for myself. The
convention I chose was that I would use R7 as a stack pointer and that R6 would be
used as a link register. To make this usage clearer in assembly code I created the
register aliases `SP` (R7) and `LR` (R6) which can be used anywhere a register is accepted.

## Additional Pseudo-instructions

The as16 assembly adds the following new pseudo-instructions to those above.

Mnemonic | Assembly Format | Action
---------|-----------------|-------
ret | ret | Return to caller. Equivalent to jalr r0, lr
inc | inc rA | Increment regA. Equivalent to addi rA, rA, 1
dec | dec rA | Decrement regA. Equivalent to addi rA, rA, -1
call | call rA | Jump and link to address in regA. Equivalent to jalr lr, rA
j | j rA | Unconditional jump to address in regA. Equivalent to jalr r0, rA
push | push rA | Push regA onto stack. Equivalent to addi sp, sp, -1 and sw rA, sp, 0
pop | pop rA | Pop regA from stack. Equivalent to lw rA, sp, 0 and addi sp, sp, 1

## Future work

There are a few additional changes that I would still like to make to `as16`. These are,
in no particular order:

* Allow Verilog rom file output 
* Allow a.out object file generation (see my [bintools](https://github.com/mseminatore/bintools) project)
* Create a linker for RiSC-16 object files

