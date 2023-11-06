cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(as16 VERSION 1.0 LANGUAGES C)

# testing
enable_testing()
add_test(NAME as16_test COMMAND as16 "${CMAKE_SOURCE_DIR}/test.asm")

# add the includes
include_directories(${PROJECT_SOURCE_DIR})

find_program(YACC_EXECUTABLE yacc)
if(YACC_EXECUTABLE)
    message("yacc found at ${YACC_EXECUTABLE}")
else()
    message("yacc not found")
endif()

#
# add the executables
#
add_executable(as16 y.tab.c)
add_executable(dasm16 disasm.c)
