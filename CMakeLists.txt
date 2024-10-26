cmake_minimum_required(VERSION 3.21)
project (MOS_Lab3 C)

set (CMAKE_C_STANDARD 23)
add_compile_options(-O0 -Wall -Werror -pedantic)

link_libraries(pthread)

add_library(common STATIC common.c)

add_executable(seq_access seq.c)
add_executable(atomic_access atomic.c)
add_executable(rand_access rand.c)

target_link_libraries(seq_access common)
target_link_libraries(rand_access common)
target_link_libraries(atomic_access common)