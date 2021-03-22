cmake_minimum_required(VERSION 3.17)
project(ProiectPOO)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProiectPOO main.cpp common/HFiles/CellLocation.h spreadsheet/HFiles/Spreadsheet.h common/HFiles/Expression.h common/HFiles/Token.h spreadsheet/BinaryOp.cpp spreadsheet/HFiles/Number.h spreadsheet/HFiles/CellRef.h spreadsheet/Parser.cpp spreadsheet/Cell.cpp spreadsheet/HFiles/CycleDetector.h common/CellLocation.cpp common/Token.cpp spreadsheet/HFiles/BinaryOp.h spreadsheet/CellRef.cpp spreadsheet/Number.cpp spreadsheet/CycleDetector.cpp spreadsheet/Spreadsheet.cpp)