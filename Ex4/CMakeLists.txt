cmake_minimum_required(VERSION 3.8)
project(AsFem)

set(CMAKE_CXX_STANDARD 14)


set(mpi "/home/by/Programs/mpich/3.3.2")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
##############################################
### For debug mode                         ###
##############################################
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O2 -Wall -Wextra -Werror")

##############################################
### For release mode                       ###
##############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -O3 -Wall -Wextra -Werror -march=native -DNDEBUG")


link_libraries("${mpi}/lib/libmpi.so")
include_directories("${mpi}/include")


set(src main.cpp)




##########################################
add_executable(asfem ${src})

