cmake_minimum_required(VERSION 3.21)
project (MOS_Lab3 C)

set (CMAKE_C_STANDARD 23)
add_compile_options(-O -Wall -Werror -pedantic)

link_libraries(pthread)

add_library(common STATIC common.c)

add_executable(seq_mem_access seq_mem_access.c)
add_executable(atomic_mem_access atomic_mem_access.c)
add_executable(rand_mem_access rand_mem_access.c)
add_executable(cache_miss cache_miss.c)
add_executable(volatile volatile.c)
add_executable(race_condition race_condition.c)
add_executable(volatile_mem_access volatile_mem_access.c)

target_link_libraries(seq_mem_access common)
target_link_libraries(rand_mem_access common)
target_link_libraries(atomic_mem_access common)
target_link_libraries(cache_miss common)
target_link_libraries(volatile common)
target_link_libraries(race_condition common)
target_link_libraries(volatile_mem_access common)