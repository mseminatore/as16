RAM_END EQU 0x3ff           # 1K of RAM
SSEG EQU 0x400

start:  
        movi sp, RAM_END    # setup SP to point to top of RAM
        movi r5, SSEG       # point R5 to SSEG display
        add r1, r0, r0      # zero R1
        movi r2, disp       # get address of disp routine

loop:   addi r1, r1, 1      # inc counter
        jalr lr, r2         # call subroutine
        beq r0, r0, loop    # do it again

disp:   sw r1, r5, 0        # output to SSEG
        jalr r0, lr         # return
        