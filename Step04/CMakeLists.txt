cmake_minimum_required(VERSION 3.13)
project(Step01)

set(CMAKE_CXX_STANDARD 17)

add_executable(Step01 main.cpp "utils/file manager/FileManager.cpp" "utils/file manager/FileManager.h" utils/structures/Details.h utils/structures/Matrix.cpp utils/structures/Matrix.h algorithms/DynamicProgramming.cpp algorithms/DynamicProgramming.h algorithms/BruteForce.cpp algorithms/BruteForce.h algorithms/SimulatedAnnealing.cpp algorithms/SimulatedAnnealing.h algorithms/AntColony.cpp algorithms/AntColony.h)