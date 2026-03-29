#
# Test case to check handling of missing symbols
#

start:
    movi r1, foo    # forward reference to missing symbol foo
    movi r2, start
    j r2
    