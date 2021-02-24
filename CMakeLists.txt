cmake_minimum_required(VERSION 3.17)
project(Abstract_VM)

set(CMAKE_CXX_STANDARD 20)

add_executable(Abstract_VM
    main.cpp
    IOperand.h
    OperandCreator.h
    Operand.h
    OperandCreator.cpp Vm.cpp Vm.h Lexer.cpp Lexer.h Parser.cpp Parser.h Error.h ErrorManager.cpp ErrorManager.h)