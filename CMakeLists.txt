cmake_minimum_required(VERSION 3.17)
project(ProiectPOO)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProiectPOO main.cpp common/api/CellLocation.cpp common/api/EvaluationContext.cpp common/api/Expression.cpp common/api/BasicSpreadsheet.cpp common/lexer/Token.cpp spreadsheet/BinaryOp.cpp spreadsheet/Number.cpp spreadsheet/CellRef.cpp spreadsheet/Parser.cpp spreadsheet/Cell.cpp spreadsheet/Spreadsheet.cpp spreadsheet/CycleDetector.cpp)