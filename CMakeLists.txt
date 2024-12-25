cmake_minimum_required(VERSION 3.10)
project(bruteforce)

find_package(Furi REQUIRED)

add_executable(bruteforce_app application.c)

target_link_libraries(bruteforce_app Furi::Furi)
