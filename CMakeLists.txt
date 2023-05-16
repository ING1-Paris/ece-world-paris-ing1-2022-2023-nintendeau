cmake_minimum_required(VERSION 3.10)
project(PROJET C)

set(CMAKE_C_STANDARD 23)

add_executable(ece-world-paris-ing1-2022-2023-nintendeau
main.c
attractions/source/tag.c attractions/header/tag.h
attractions/source/geometry_dash.c attractions/header/geometry_dash.h
attractions/source/guitar_hero.c attractions/header/guitar_hero.h

)
target_link_libraries(ece-world-paris-ing1-2022-2023-nintendeau -lmingw32 -lalleg44)
