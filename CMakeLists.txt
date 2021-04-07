cmake_minimum_required(VERSION 3.16)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 20)

include_directories(includes)

add_executable(Abstract_VM
        srcs/main.cpp
        includes/IOperand.h
        includes/OperandCreator.h
        includes/Operand.h
        srcs/OperandCreator.cpp srcs/Vm.cpp includes/Vm.h srcs/Lexer.cpp includes/Lexer.h srcs/Parser.cpp includes/Parser.h includes/Error.h srcs/ErrorManager.cpp includes/ErrorManager.h srcs/CodeAnalyzer.cpp includes/CodeAnalyzer.h includes/utils.h srcs/utils.cpp)