#
# test.asm - an example of enhanced RiSC-16 assembly
#

RAM_END EQU 0x3ff           # 1K of RAM
SSEG EQU 0x400              # MMIO address for SSEG display

start:  
        movi sp, RAM_END    # setup SP to point to top of RAM
        movi r5, SSEG       # point R5 to SSEG display
        add r1, r0, r0      # zero R1
        movi r2, disp       # get address of disp routine

loop:   inc r1              # increment counter in R1
        call r2             # call subroutine to update display
        beq r0, r0, loop    # do it again

disp:   sw r1, r5, 0        # output to SSEG
        ret                 # return

        
