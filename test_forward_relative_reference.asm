#
# Test case to check handling of forward relative symbols
#

start:
    beq r0, r0, foo
    movi r2, start

foo:
    j r2
