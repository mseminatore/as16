# Test JALR sub-instructions: SMSR, GMSR, HALT, SYSCALL, RTI
# Expected encodings:
#   SMSR R3    -> 0xE00B  (func=1, Rc=3)
#   GMSR R5    -> 0xE015  (func=2, Rc=5)
#   HALT       -> 0xE018  (func=3, Rc=0)
#   SYSCALL    -> 0xE020  (func=4, Rc=0)
#   RTI        -> 0xE02E  (func=5, Rc=6/LR)

    SMSR R3
    GMSR R5
    HALT
    SYSCALL
    RTI
